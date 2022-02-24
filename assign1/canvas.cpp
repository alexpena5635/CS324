/* canvas.cpp
 * Starter code from lecture notes
 */
 
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "graphics.h"
#include "matrix.h"

Canvas::Canvas( std::size_t w, std::size_t h, color bg )
    : width(w), height(h), 
      pixels(width * height, {bg}),
      background(bg) { }


void Canvas::SetColor( std::size_t x, std::size_t y, color c ) {
    if ( x >= 0 && x < width && y >= 0 && y < height ) {
        pixels[y * width + x] = {c};
    }
}

pixel Canvas::GetPixel( std::size_t x, std::size_t y ) const {
    return pixels[y * width + x];
}

void Canvas::SetPixel( std::size_t x, std::size_t y, pixel p ) {

    if( x >= 0 && x < width && y >= 0 && y < height ) {
		pixels[y * width + x] = p;
    }
}

void Canvas::Clear() {
    for( auto& pixel : pixels ) {
        pixel = {background};
    }
}


void Line( Canvas& c, int x1, int y1, int x2, int y2, color color )
{
    int xTmp, yTmp;

    if( y1 == y2 ) {          // Horizontal
        if( x1 > x2 ) {  // order for loop to work
	    	xTmp = x1;
	    	x1 = x2;
	    	x2 = xTmp;
		}
	    
        for( auto i = x1 ; i <= x2 ; ++i ) {
            c.SetColor( i, y1, color );
        }
        return;
    } else if ( x1 == x2 ) {   // Vertical
        if( y1 > y2 ) {  // order for loop to work
	    	yTmp = y1;
	    	y1 = y2;
	    	y2 = yTmp;
		}
	    
        for( auto j = y1 ; j <= y2 ; ++j ) {
            c.SetColor( x1, j, color );
        }
        return;
   }

    double a = 1.0 * (y1 - y2) / (x1 - x2);
    double b = y1 - a * x1;
    for( double i = std::min(x1, x2) ; i < std::max(x1, x2) ; i += 1.0 ) {
        for( double j = std::min(y1, y2) ; j < std::max(y1, y2) ; j += 1.0 ) {
            double x1_intercept = a * (i - 0.5) + b;
            double x2_intercept = a * (i + 0.5) + b;
            double y1_intercept = (j - b - 0.5) / a;
            double y2_intercept = (j - b + 0.5) / a;
            
            if (x1_intercept >= j - 0.5 && x1_intercept <= j + 0.5) {
                c.SetColor(i, j, color);
            } else if (x2_intercept >= j - 0.5 && x2_intercept <= j + 0.5) {
                c.SetColor(i, j, color);
            } else if (y1_intercept >= i - 0.5 && y1_intercept <= i + 0.5) {
                c.SetColor(i, j, color);
            } else if (y2_intercept >= i - 0.5 && y2_intercept <= i + 0.5) {
                c.SetColor(i, j, color);
            }
        }
    }
}

void SaveCanvasToFile( Canvas const& canvas, std::string const& fileName )
{
    std::fstream file(fileName, std::ios::out);
    // Check!
    
    file << "P6 " << canvas.Width() << " " << canvas.Height() << " 255\n";
    for( auto y = 0 ; y < canvas.Height() ; ++y ) {
        for( auto x = 0 ; x < canvas.Width() ; ++x ) {
            auto const pixel = canvas.GetPixel(x, y);
            file << pixel.c.red << pixel.c.green << pixel.c.blue;
        }
    }	
}

// The corner points of the window and viewport
static point2D w_min, w_max;
static point2D v_min, v_max;

// Current position from "move" is set here"
static point2D currentPos;

// Scaling factor for x and y
static double sx;
static double sy;

// InitGraphics()
// - sets the window, viewport, and cavas up
// - return the canvas
std::shared_ptr<Canvas> InitGraphics(const int size, const point2D w_min, const point2D w_max, const point2D v_min, const point2D v_max)
{
	SetWindow(w_min.x, w_min.y, w_max.x, w_max.y);
	SetViewport(v_min.x, v_min.y, v_max.x, v_max.y);

	// sx = (v_max.x-v_min.x) / (v_max.x-w_min.x); // Scaling factor should be diff of viewport poitns over diff of window points?
	sx = (v_max.x - v_min.x) / (w_max.x - w_min.x);
	sy = (v_max.y - v_min.y) / (w_max.y - w_min.y);
	
	std::shared_ptr<Canvas> pixmap (new Canvas(size, size, colors::WHITE));
	return pixmap;	
}

// Set the viewport corner coords
void SetViewport(double x1, double y1, double x2, double y2)
{
	v_min.set(x1, y1, 1);
	v_max.set(x2, y2, 1);
}

// Set the window corner coords
void SetWindow(double x1, double y1, double x2, double y2)
{
	w_min.set(x1, y1, 1);
    v_max.set(x2, y2, 1);
}

// Convert from window to viewport coords
// - Need to multiply all of the transformation matricies together first, then multiply against point
void WindowToViewport(const point2D& in_vector, point2D& out_vector)
{
	// vx -> xvmin + (xw-xwmin) * Sx
	// vy -> yvmin + (yw-ywmin) * Sy	

	// Multiply 2D point vector by 3D translation matrix of the min viewport point
	Matrix t1(DIM, translation, v_min.x, v_min.y);
	Matrix s(DIM, scaling, 0, 0, sx, sy);
	Matrix t2(DIM, translation, -w_min.x, -w_min.y);

	Matrix result = t1*s*t2;

	out_vector = result * in_vector;

	// The point is now translated into viewport
	t1.deallocate();
	t2.deallocate();
	s.deallocate();
}

// Convert from the viewport to the pixmap
void ViewportToPixmap(double canvas_size, const point2D& in_vector, point2D& out_vector)
{
	double scaleX = canvas_size / (v_max.x-v_min.x);
    double scaleY = canvas_size / (v_max.y-v_min.y);

	// Multiply 2D point vector by 3D translation matrix of the min viewport point
	Matrix t1(DIM, translation, 0, 0); //smallest spot on cavas is always 0,0	
	Matrix s(DIM, scaling, 0, 0, scaleX, scaleY);
	Matrix t2(DIM, translation, -v_min.x, -v_min.y);

	Matrix result = t1*s*t2;

	out_vector = result * in_vector;

	// The point is now translated into canvas coords
	t1.deallocate();
	t2.deallocate();
	s.deallocate();

	// Filp the y-axis 
	out_vector.y = canvas_size - out_vector.y;
}


// Move to a 2D world coordinate, store it for later
void MoveTo2D(double x, double y)
{
	// Setting some global that retains the world position we have "moved to"
	currentPos.set(x,y,1);
}

// Draw a line on the canvas
void DrawTo2D(Canvas &c, color color, double x, double y)
{
	// - Translate world coord to viewport (WindowToViewport)
	// - Translate viewport coords to canvas/pixmap coordinates	
	point2D window_curr(currentPos.x, currentPos.y, currentPos.h), window_goal(x, y, 1);
	point2D new_curr, new_goal;

	std::cout << "##### Window points #####\n" << window_curr << window_goal;

	// Translate the start and end coodinates from world space to viewport
	WindowToViewport(window_curr, new_curr); 
	WindowToViewport(window_goal, new_goal); 

	std::cout << "##### Viewport points #####\n" << new_curr << new_goal;

	// Viewport to canvas space/coords
	ViewportToPixmap(c.Width(), new_curr, new_curr); 
	ViewportToPixmap(c.Width(), new_goal, new_goal);

	std::cout << "##### Pixmap points #####\n" << new_curr << new_goal;
	
	// Scales to match vp and window, like a fullscreen drawing
	Line(c, new_curr.x, new_curr.y, new_goal.x, new_goal.y, color);	
}

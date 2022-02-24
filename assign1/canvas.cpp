/* canvas.cpp
 * Starter code from lecture notes
 */
 
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "graphics.h"

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
void WindowToViewport(point2D& in_vector, point2D& out_vector)
{
	// vx -> xvmin + (xw-xwmin) * Sx
	// vy -> yvmin + (yw-ywmin) * Sy	
	std::cout << "####### Window to Viewport Start ########" << std::endl;
	// Multiply 2D point vector by 3D translation matrix of the min viewport point
	translatePoint(in_vector, out_vector, v_min.x, v_min.y);

	std::cout << "After 1st translation\n" << out_vector << std::endl;

	// Multiply 2D point vector by 3D scaling matrix with the scaling factors
	scalePoint(out_vector, out_vector, sx, sy);
	
	std::cout << "After scaling\n" << out_vector << std::endl;
	std::cout << "sx: " << sx << " sy: " << sy << std::endl;
	
	// Multiply 2D point vector by 3D translation matrix of the min window point
	translatePoint(out_vector, out_vector, -w_min.x, -w_min.y);

	std::cout << "After 2nd translation\n" << out_vector << std::endl;
	
	std::cout << "####### END ########" << std::endl;
	// The point is now translated into viewport
}

// Convert from the viewport to the pixmap
void ViewportToPixmap(double canvas_size, point2D& in_vector, point2D& out_vector)
{
	double scaleX = canvas_size / (v_max.x-v_min.x);
    double scaleY = canvas_size / (v_max.y-v_min.y);

	// Translate from viewport to pixmap
	// Using same logic as WindowToViewport()
	translatePoint(in_vector, out_vector, 0, 0); //smallest spot on cavas is always 0,0	
	scalePoint(out_vector, out_vector, scaleX, scaleY);
	translatePoint(out_vector, out_vector, -v_min.x, -v_min.y);

	// Filp the y-axis 
	out_vector.y = canvas_size - out_vector.y;
}


// Translate any given 2-D vector in homogenougs coords according to the translation matrix
void translatePoint(point2D& in_vector, point2D& out_vector, double x_tran, double y_tran)
{
	// Intilaize tranlsation matirx
	double tMatrix[DIM][DIM] = {};

	for(int i=0; i<DIM; i++) // setting diagonal 1s
	{
		tMatrix[i][i] = 1;
	}

	// Setting x and y translations
	tMatrix[0][DIM-1] = x_tran;
	//tMatrix[0][DIM-1] = yTran; // THIS WAS BREAKING STUFF 
	tMatrix[1][DIM-1] = y_tran; 
	
	double newPoint[DIM] = {};
	double in_point[DIM] = {in_vector.x, in_vector.y, in_vector.h};

	// Multiply point vector (world) by translation matrix
	// BUG FIXED!
	// - Was multipying the vector by the matrix, should do the column vector on the right
	std::cout << "Translation matrix" << std::endl;
	// Each row in the matrix
	for(int i=0; i<DIM; i++) 
	{
		// Each column for that row
		for(int j=0; j<DIM; j++)
		{
			//pointV[i] += tMatrix[i][j] * pointW[j]; // This was causing us to multiply across matrix rows, and not cols
			//newPoint[i] += tMatrix[j][i] * in_point[j]; Also causing issues bc of order of vector mult?
			// For the new value at [x y h] (i), add up the corresponding row multiplyied against the old [x y h], for each row
			newPoint[i] += tMatrix[i][j] * in_point[j]; 
			std::cout << tMatrix[i][j] << "\t";
		}
		std::cout << std::endl;			
	}
	
	// for(int i=0; i<DIM; i++)
	// 	pointV[i] = newPoint[i];
	out_vector.set(newPoint[0], newPoint[1], newPoint[2]);				
}	

// Multiply any given 2-D homog coord by a scaling matrix, given the scale
void scalePoint(point2D& in_vector, point2D& out_vector, double x_scale, double y_scale)
{
	// Initialize scaling matrix
	double sMatrix[DIM][DIM] = {};
	
	// Setting x and y scale factors
	sMatrix[0][0] = x_scale;
	sMatrix[1][1] = y_scale;

	// setting the final 1 in the bottom right
	sMatrix[DIM-1][DIM-1] = 1;

	double newPoint[DIM] = {};
	double in_point[DIM] = {in_vector.x, in_vector.y, in_vector.h};

	// Multiply point vector by scaling matrix
	std::cout << "Scaling matrix" << std::endl;
	for(int i=0; i<DIM; i++)
    {
        for(int j=0; j<DIM; j++)
        {
			// newPoint[i] += sMatrix[i][j] * in_point[j]; // this is something i fixed in translaate, here to?
            newPoint[i] += sMatrix[j][i] * in_point[j];
			std::cout << sMatrix[i][j] << "\t";
		}
		std::cout << std::endl;			
    }

	// for(int i=0; i<DIM; i++)
	// 	pointV[i] = newPoint[i];
	out_vector.set(newPoint[0], newPoint[1], newPoint[2]);	
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

	// Translate the start and end coodinates from world space to viewport
	WindowToViewport(window_curr, new_curr); 
	WindowToViewport(window_goal, new_goal); 

	// std::cout << "vp start: x=" << startPoint[0] << " y=" << startPoint[1] << std::endl;
	// std::cout << "vp end: x=" << endPoint[0] << " y=" << endPoint[1] << std::endl;
	
	// Viewport to canvas space/coords?	
	ViewportToPixmap(c.Width(), new_curr, new_curr); 
	ViewportToPixmap(c.Width(), new_goal, new_goal);

	// std::cout << "bp start: x=" << startPoint[0] << " y=" << startPoint[1] << std::endl;
	// std::cout << "bp end: x=" << endPoint[0] << " y=" << endPoint[1] << std::endl;
	
	// Scales to match vp and window, like a fullscreen drawing
	Line(c, new_curr.x, new_curr.y, new_goal.x, new_goal.y, color);	
}

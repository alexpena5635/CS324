/* canvas.cpp
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

////////////// New funcs

//const int DIM;
// The corner points of the window and viewport
double minViewport[DIM], maxViewport[DIM];
double minWindow[DIM], maxWindow[DIM];

// Scaling factor for x and y
double sx = (maxViewport[0]-minViewport[0]) / (maxWindow[0]-minWindow[0]);
double sy = (maxViewport[1]-minViewport[1]) / (maxWindow[1]-minWindow[1]);

std::shared_ptr<Canvas> InitGraphics(const int size, const double wMin[], const double wMax[], const double vMin[], const double vMax[])
{
	SetWindow(wMin[0], wMin[1], wMax[0], wMax[1]);
	SetViewport(vMin[0], vMin[1], vMax[0], vMax[1]);
	//pixmap size? maybe this intializes the canvas as well?	
	std::shared_ptr<Canvas> pixmap (new Canvas(size, size, colors::WHITE));
	
	return pixmap;	
}

void SetViewport(double x1, double y1, double x2, double y2)
{
	minViewport[0] = x1;
	minViewport[1] = y1;

	maxViewport[0] = x2;
	maxViewport[1] = y2;
}

void SetWindow(double x1, double y1, double x2, double y2)
{
    minWindow[0] = x1;
    minWindow[1] = y1;

    maxWindow[0] = x2;
    maxWindow[1] = y2;
}

void WindowToViewport(double pointW[DIM], double pointV[DIM]) // possibly take in a x, y (and later z?)
{
	
	// some point in world space (2,2)
	// We know the widow is defined to go from (-1,-1) to (4,4)			
	// Viewport is (-1,-1) to (1,1)
	// - need to map point from window space to viewport	
	
	// vx -> xvmin + (xw-xwmin) * Sx
	// vy -> yvmin + (yw-ywmin) * Sy	
	//double pointV[DIM] = {};	
	
	translatePoint(pointW, pointV, -minWindow[0], -minWindow[1]);	
	scalePoint(pointV, pointV, sx, sy);
	translatePoint(pointV, pointV, minViewport[0], minViewport[1]);
}

void translatePoint(double pointW[DIM], double pointV[DIM], double xTran, double yTran)
{
	// Intilaize tranlsation matirx
	double tMatrix[DIM+1][DIM+1] = {};

	for(int i=0; i<DIM+1; i++) // setting diagonal 1s
	{
		tMatrix[i][i] = 1;
	}

	// Setting x and y translations
	tMatrix[0][DIM] = xTran;
	tMatrix[0][DIM] = yTran;

	// Multiply point vector (world) by translation matrix
	for(int i=0; i<DIM; i++)
	{
		for(int j=0; j<DIM+1; j++)
		{
			pointV[i] += tMatrix[i][j] * pointW[j]; 
		}			
	}				
}	

void scalePoint(double pointW[DIM], double pointV[DIM], double xScale, double yScale)
{
	// Initialize scaling matrix
	double sMatrix[DIM+1][DIM+1] = {};
	
	// Setting x and y scale factors
	sMatrix[0][0] = xScale;
	sMatrix[1][1] = yScale;

	// setting the final 1 in the bottom right
	sMatrix[DIM][DIM] = 1;

	// Multiply point vector by scaling matrix
	for(int i=0; i<DIM; i++)
    {
        for(int j=0; j<DIM+1; j++)
        {
            pointV[i] += sMatrix[i][j] * pointW[j];
        }
    }
}

void MoveTo2D(double x, double y)
{

}

void DrawTo2D(Canvas &c, color color, double x, double y)
{

}

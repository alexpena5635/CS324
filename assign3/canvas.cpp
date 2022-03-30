/* 
 * canvas.cpp - Starter code from lecture notes.
 * Defines methods for a canvas (vector of pixels) for graphics usage.
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */
 
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "canvas.h"

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

void SaveCanvasToPBM( Canvas const& canvas, std::string const& fileName )
{
    std::fstream file(fileName, std::ios::out);
    
    if(!file.is_open()) {
        std::cout << "File: " << fileName << " does not exsist. Exiting." << std::endl;
        return;
    }
    
    /* 
     * First line of a '.pbm' file
     * P6  ; defines format of .pbm
     * 255 ; max rgba value
     * 
     * More info: http://netpbm.sourceforge.net/doc/pbm.html 
     */
    file << "P6 " << canvas.Width() << " " << canvas.Height() << " 255\n";
    for( auto y = 0 ; y < canvas.Height() ; ++y ) {
        for( auto x = 0 ; x < canvas.Width() ; ++x ) {
            auto const pixel = canvas.GetPixel(x, y);
            file << pixel.c.red << pixel.c.green << pixel.c.blue;
        }
    }	
}
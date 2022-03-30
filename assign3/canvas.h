/* 
 * canvas.h - Starter code from lecture notes.
 * Delcares a canvas(vector of pixels) class and methods for graphics usage.
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */

#ifndef CANVAS_H_
#define CANVAS_H_

#include <vector>

#include "colors.h"

struct pixel {
    color c;
};

// A canvas represents the pixels in a pixmap (ex: '.pbm' file)
class Canvas {
	public:
    	Canvas::Canvas( std::size_t w, std::size_t h, color bg )
			: width(w), height(h), 
			pixels(width * height, {bg}),
			background(bg) { }

    	void SetColor( std::size_t x, std::size_t y, color c ) {
			if ( x >= 0 && x < width && y >= 0 && y < height ) {
				pixels[y * width + x] = {c};
			}
		}
    
    	pixel GetPixel( std::size_t x, std::size_t y ) const {
			return pixels[y * width + x];
		}
		
   		void SetPixel(  std::size_t x, std::size_t y, pixel p ) {
			if( x >= 0 && x < width && y >= 0 && y < height ) {
				pixels[y * width + x] = p;
    		}
		}
    
    	void Clear() {
			// Sets every pixel's color to color::background
			for( auto& pixel : pixels ) {
				pixel = {background};
			}
		}

    	std::size_t Width()  const { return width; }
    	std::size_t Height() const { return height; }

	private:
    	std::size_t width, height;
    	std::vector<pixel> pixels;
    	color background;
};


void Line( Canvas& c, int x1, int y1, int x2, int y2, color color );
void SaveCanvasToPBM( Canvas const& canvas, std::string const& fileName );

#endif
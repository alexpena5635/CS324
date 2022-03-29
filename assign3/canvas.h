#ifndef CANVAS_H_
#define CANVAS_H_

#include "colors.h"

#include <vector>

struct pixel {
    color c;
};

// This just represents the device or the pix/bit map
class Canvas {
	public:
    	Canvas( std::size_t w, std::size_t h, color background = colors::WHITE );

    	void SetColor( std::size_t x, std::size_t y, color c );
    
    	pixel GetPixel( std::size_t x, std::size_t y ) const;
   		void SetPixel(  std::size_t x, std::size_t y, pixel c );
    
    	void Clear();

    	std::size_t Width()  const { return width; }
    	std::size_t Height() const { return height; }

	private:
    	std::size_t width, height;
    	std::vector<pixel> pixels;
    	color background;
};


void Line( Canvas& c, int x1, int y1, int x2, int y2, color color );
void SaveCanvasToFile( Canvas const& canvas, std::string const& fileName );



#endif
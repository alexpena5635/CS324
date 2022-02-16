/* graphics.h
 */
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <vector>
#include <memory>

struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

namespace colors {
	constexpr color BLACK{   0,   0,   0 };
	constexpr color WHITE{ 255, 255, 255 };
	constexpr color RED{   255,   0,   0 };
	constexpr color GREEN{   0, 255,   0 };
	constexpr color BLUE{    0,   0, 255 };
}

struct pixel {
    color c;
};

struct point {
	double x;
	double y;
	void set(double setx, double sety) { x = setx; y = sety; } 
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

// New functions

std::shared_ptr<Canvas> InitGraphics(const int size, const point wMin, const point wMax, const point vMin, const point vMax);

void SetViewport(double x1, double y1, double x2, double y2); // set the viewport "corner" coords (global)
void SetWindow(double x1, double y1, double x2, double y2);  // set the window "corner" coords (global)
void WindowToViewport(); // Map a random point from the window to the viewport, based on how they were set

void MoveTo2D(double x, double y); // On the canvas space, where the "pen" is movedto
void DrawTo2D(Canvas &c, color color, double x, double y); // Go from the current spot to (x,y) an draw line

#endif

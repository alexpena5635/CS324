/* graphics.h
 */
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <vector>
#include <memory>
#include <iostream>

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

const int DIM = 3; // 2 for coords, 1 for homog

// 2D Point struct, with constructor, set function, and print
struct point2D {
    double x;
	double y;
	double h; // homog
	point2D() { x=0.0; y=0.0; h=0.0;}
	point2D(double x1, double y1, double h1=1) {x=x1; y=y1; h=h1;}
	void set(double x1, double y1, double h1=1) {x=x1; y=y1; h=h1;}

	friend std::ostream& operator<<(std::ostream& os, const point2D& p){
		return os << "Point\n - x: " << p.x << "\n - y: " << p.y << "\n - z: " << p.h << std::endl;
	}
};



std::shared_ptr<Canvas> InitGraphics(const int size, const point2D w_min, const point2D w_max, const point2D v_min, const point2D v_max);

void SetViewport(double x1, double y1, double x2, double y2); // set the viewport "corner" coords (global)
void SetWindow(double x1, double y1, double x2, double y2);  // set the window "corner" coords (global)

void WindowToViewport(const point2D &in_vector, point2D& out_vector); 
void ViewportToPixmap(double canvas_size, const point2D& in_vector, point2D& out_vector);

void translatePoint(point2D &in_vector, point2D& out_vector, double x_tran, double y_tran);
void scalePoint(point2D &in_vector, point2D& out_vector, double x_scale, double y_scale);

void MoveTo2D(double x, double y); // On the canvas space, where the "pen" is moved to
void DrawTo2D(Canvas &c, color color, double x, double y); // Go from the current spot to (x,y) an draw line


#endif




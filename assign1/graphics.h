/* graphics.h
 */
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <vector>

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

class Canvas 
{
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

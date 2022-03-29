#ifndef _COLORS_H_
#define _COLORS_H_

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

#endif
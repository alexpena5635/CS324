/*
*   color.h
*
*   Alex Pena
*   Modified from : Ray Tracing In One Weekend
*/

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>

#include "vec3.h"

void write_color(std::ostream &out, Color pixel_color) {
    // Write the translated [0,255] value of each componenet
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif
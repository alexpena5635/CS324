/*
* main.cpp
* 
* Alex Pena
* 24th March 2022
* 
* Inspired from: https://raytracing.github.io/books/RayTracingInOneWeekend.html
*
*/ 

#include <iostream>
#include <fstream>

#include "vec3.h"
#include "color.h"
#include "ray.h"

Color ray_color(const Ray& r) {
    Vec3 unit_dir = unit_vector(r.direction());
    auto t = 0.5*(unit_dir.y() + 1.0);

    return (1.0-t)*Color(1.0,1.0,1.0) + t*Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image size
    const int IMAGE_WIDTH  = 500;
    const int IMAGE_HEIGHT = 500;

    std::fstream savefile("image.ppm", std::fstream::out);

    savefile << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int j = IMAGE_HEIGHT-1; j>=0; --j)
    {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i)
        {
            // auto r = double(i)/(IMAGE_WIDTH-1);
            // auto g = double(j)/(IMAGE_HEIGHT-1);
            // auto b = 0.25;

            // int ir = static_cast<int>(255.999 * r);
            // int ig = static_cast<int>(255.999 * g);
            // int ib = static_cast<int>(255.999 * b);

            // savefile << ir << ' ' << ig << ' ' << ib << '\n';
            Color pixel_color(double(i)/(IMAGE_WIDTH-1), double(j)/(IMAGE_HEIGHT-1), 0.25);
            write_color(savefile, pixel_color);
        }
    }

    std::cout << "\nDone.\n";

    savefile.close();
}
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

bool hit_sphere(const Point3& center, double radius, const Ray& r) {
    Vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

Color ray_color(const Ray& r) {
    if (hit_sphere(Point3(0,0,-1), 0.5, r))
        return Color(1, 0, 0);
    Vec3 unit_dir = unit_vector(r.direction());
    auto t = 0.5*(unit_dir.y() + 1.0);

    return (1.0-t)*Color(1.0,1.0,1.0) + t*Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image size
    const auto ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 600;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = ASPECT_RATIO * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

    // Render

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
            // Color pixel_color(double(i)/(IMAGE_WIDTH-1), double(j)/(IMAGE_HEIGHT-1), 0.25);
            auto u = double(i) / (IMAGE_WIDTH-1);
            auto v = double(j) / (IMAGE_HEIGHT-1);
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            Color pixel_color = ray_color(r);
            write_color(savefile, pixel_color);
        }
    }

    std::cout << "\nDone.\n";

    savefile.close();
}
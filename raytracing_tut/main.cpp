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

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

Color ray_color(const Ray& r, const Hittable& world, int depth) {
    hit_record rec;

    if (depth <= 0)
        return Color(0,0,0);

    if(world.hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        Color attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        
        return Color(0,0,0);
    }

    Vec3 unit_dir = unit_vector(r.direction());
    auto t = 0.5*(unit_dir.y() + 1.0);
    return (1.0-t)*Color(1.0,1.0,1.0) + t*Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const auto ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 400;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    Hittable_List world;

    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.5);
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),  -0.4, material_left));
    world.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));

    // Camera
    Camera cam;

    // Render

    std::fstream savefile("image.ppm", std::fstream::out);

    savefile << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int j = IMAGE_HEIGHT-1; j>=0; --j)
    {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i)
        {
            Color pixel_color(0,0,0);
            for(int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (IMAGE_WIDTH-1);
                auto v = (j + random_double()) / (IMAGE_HEIGHT-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(savefile, pixel_color, samples_per_pixel);
        }
    }

    std::cout << "\nDone.\n";

    savefile.close();
}
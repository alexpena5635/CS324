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

#include "scenes.h"

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
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 600;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 250;
    const int max_depth = 50;

    // World

    // auto world = final_scene();
    auto world = my_scene();

    Point3 lookfrom (13, 200,3);
    Point3 lookat   (0,  0, 200);
    Vec3 vup        (0,  1, 0);
    auto dist_to_focus  = 200.0;
    auto aperature      = 0.01;

    // Camera
    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperature, dist_to_focus);

    // Render

    std::fstream savefile("myimage.ppm", std::fstream::out);

    savefile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j>=0; --j)
    {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            Color pixel_color(0,0,0);
            
            // Parrallel processing!!!
            #pragma omp parallel for
            for(int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(savefile, pixel_color, samples_per_pixel);
        }
    }

    std::cout << "\nDone.\n";

    savefile.close();
}

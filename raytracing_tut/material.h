#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "rtweekend.h"

struct hit_record;

class Material {
    public:
        virtual bool scatter(
            const Ray& r_in, const hit_record& rec, Color& attenutation, Ray& scatterted
        ) const = 0;
};

class Lambertian : public Material {
    private:
        Color albedo;
    public:
        Lambertian(const Color& a) : albedo(a) {}

        virtual bool scatter(
            const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered
        ) const override {
            auto scatter_dir = rec.normal + random_unit_vector();

            // Catch degenerate scatter direction
            if (scatter_dir.near_zero())
                scatter_dir = rec.normal;
            
            scattered = Ray(rec.p, scatter_dir);
            attenuation = albedo;
            return true;
        }
};

class Metal : public Material {
    private:
        Color albedo;
        double fuzz;
    public:
        Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1){}

        virtual bool scatter(
            const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered
        ) const override {
            Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
};

#endif
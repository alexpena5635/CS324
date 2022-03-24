/*
*   ray.h
*
*   Alex Pena
*   Modified from : Ray Tracing In One Weekend
*/

#ifndef RAY_H_
#define RAYH_

#include "vec3.h"

class Ray {
    private: 
        Point3 orig;
        Vec3 dir;
    
    public:
        Ray() {}
        Ray(const Point3& origin, const Vec3& direction)
            : orig(origin), dir(direction)
        {}

        Point3 origin() const { return orig; }
        Vec3 direction() const { return dir; }

        Point3 at(double t) const {
            return orig + t*dir;
        }
};

#endif
/*
*   vec3.h
*
*   Alex Pena
*   Modified from : Ray Tracing In One Weekend
*/

#ifndef VEC3_H_
#define VEC3_H_

#include <cmath>
#include <iostream>

class Vec3 {
    private:
        double e[3];
        
    public:
        // Constructors
        Vec3() : e{0,0,0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        // Gettter fucntions for x,y,z
        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        // Operator overloads
        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]);}
        double operator[](int i) const { return e[i]; } // Constant, only to see what it is
        double& operator[](int i) { return e[i]; } // reference to the element
        
        Vec3& operator+=(const Vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        inline static Vec3 random() {
            return Vec3(random_double(), random_double(), random_double());
        }

        inline static Vec3 random(double min, double max) {
            return Vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }
};

// Type aliases
using Point3 = Vec3; // 3D point
using Color = Vec3; // RGB color

// Vector 3 utility functions
inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3( t * v.x(), t * v.y(), t * v.z());
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t*v;
}

inline Vec3 operator/(const Vec3 &v, double t) {
    return (1/t)*v;
}

inline double dot(const Vec3 &u, const Vec3 &v) {
    return  u.x() * v.x()
        +   u.y() * v.y()
        +   u.z() * v.z();
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x()
            );
}

inline Vec3 unit_vector(Vec3 v){
    return v / v.length();
}

inline Vec3 random_in_unit_sphere() {
    while(true) {
        auto p = Vec3::random(-1,1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

inline Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_in_hemisphere(const Vec3& normal) {
    Vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

#endif
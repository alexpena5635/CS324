/* 
 * vec3.h (Modified from code in: Ray Tracing in One Weekend)
 * Defines a 3D vector class, and operations on that vector
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */

#ifndef VEC3_H_
#define VEC3_H_

#include <iostream>

// Originally I had Vec3 inherit from Vec2, caused too many issues with different storage and such. 
// - Using the same wouldve wasted memoyry for the smaller. Maybe consolidate later?
class Vec3 { /* : public vec2 */ 
    private:
        double v[4]; // 4 length array. 3D points x,y,z + 1 for homogenous
        bool homogenous;
    
    public:
        /* Constructors */
        Vec3()  : v{0.0, 0.0, 0.0, 1.0}   { homogenous = true; }
        Vec3(double v0, double v1, double v2, double h=1, bool homog=true) 
                : v{v0, v1, v2, h}      { homogenous = homog; }

        /*  Getters  */
        double x()          const { return v[0]; }
        double y()          const { return v[1]; }
        double z()          const { return v[2]; }
        double h()          const { return v[3]; }

        /* Operator overloads */
        Vec3 operator-() const {
            // Only negate 'h' if homogenous
            return (
                homogenous ? Vec3(-v[0], -v[1], -v[2], -v[3]) 
                    : Vec3(-v[0], -v[1], -v[2], v[3])
            );
        }
        
        double  operator[](int i) const { return v[i]; } // Return constant of value 
        double& operator[](int i)       { return v[i]; } // Return reference to value
        
        Vec3& operator+=(const Vec3 &vec) {
            v[0] += vec.v[0];
            v[1] += vec.v[1];
            v[2] += vec.v[2];
            v[3] += (homogenous ? vec.v[3] : 0);            // Add 'h' if homog
            return *this;
        }

        Vec3& operator*=(const double t) {
            v[0] *= t;
            v[1] *= t;
            v[2] *= t;
            v[3] *= (homogenous ? t : 1);                   // Subtract 'h' if homog
            return *this;
        }

        Vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        /* Utility member functions/methods */
        void set(double x, double y, double z, double h=1, bool homog=true) {
            v[0] = x;
            v[1] = y;
            v[2] = z;
            v[3] = h;
            homogenous = homog;
        }

        double magnitude() const { // Calcuate the magnitude of the vector
            return sqrt(lengthSquared());
        }

        double lengthSquared() const { // Square each component of the vector
            return v[0]*v[0] 
                + v[1]*v[1] 
                + v[2]*v[2] 
                + (homogenous ? v[3]*v[3] : 0);  // Square 'h', add, if homog.
        }

        
        bool Homog() const      { return homogenous; }
        void setHomog(bool set) { homogenous = set;  }
};

/* Type alias */
typedef Vec3 Point3;

/* Vector2 utility functions */
inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << "x: " << v.x() << " y: " << v.y() << " z: " << v.z() << " h: " << v.h();
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
        +   u.z() * v.z()
        +   (u.Homog() ? u.h() * v.h() : 0);        // Only dot 'h' if homog.
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {   // 3D cross product.
    return Vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x()
            );
}

inline Vec3 unitVector(Vec3 v){
    return v / v.magnitude();
}
#endif
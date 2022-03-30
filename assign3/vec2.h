/* 
 * vec2.h (Modified from code in: Ray Tracing in One Weekend)
 * Defines a 2D vector class, and operations on that vector
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */

#ifndef VEC2_H_
#define VEC2_H_

#include <cmath>
#include <iostream>

class Vec2 {
    private:
        double v[3];     // 3 length array. 2D points x,y + 1 for homogenous
        bool homogenous; // True when treating Vec2 as a homogenous vector

    public:
        /* Constructors */
        Vec2()  : v{0.0, 0.0, 1.0}  { homogenous = true; }
        Vec2(double v0, double v1, double h=1, bool homog=true) 
                : v{v0, v1, h}      { homogenous = homog; }

        /*  Getters  */
        double x()          const { return v[0]; }
        double y()          const { return v[1]; }
        double h()          const { return v[2]; }

        /* Operator overloads */
        Vec2 operator-() const {
            // Only negate 'h' if homogenous
            return (
                homogenous ? Vec2(-v[0], -v[1], -v[2]) : Vec2(-v[0], -v[1], v[2])
            );
        } 

        double  operator[](int i) const { return v[i]; } // Return constant of value 
        double& operator[](int i)       { return v[i]; } // Return reference to value
        
        Vec2& operator+=(const Vec2 &vec) {
            v[0] += vec.v[0];
            v[1] += vec.v[1];
            v[2] += (homogenous ? vec.v[2] : 0);        // Add 'h' if homog.
            return *this;
        }

        Vec2& operator*=(const double t) {
            v[0] *= t;
            v[1] *= t;
            v[2] *= (homogenous ? t : 1);               // Subtract 'h' if homog
            return *this;
        }

        Vec2& operator/=(const double t) {
            return *this *= 1/t;
        }

        /* Utility member functions/methods */
        void set(double x, double y, double h=1, bool homog=true) {
            v[0] = x;
            v[1] = y;
            v[2] = h;
            homogenous = homog;
        }

        double magnitude() const {
            return std::sqrt(lengthSquared());
        }

        double lengthSquared() const { // Square each component of the vector
            return v[0]*v[0] 
                + v[1]*v[1] 
                + (homogenous ? v[2]*v[2] : 0); // Square 'h', add, if homog.
        }

        bool Homog() const      { return homogenous; }
        void setHomog(bool set) { homogenous = set;  }
};

/* Type alias */
typedef Vec2 Point2;

/* Vector2 utility functions */
inline std::ostream& operator<<(std::ostream &out, const Vec2 &v) {
    return out << "x: " << v.x() << " y: " << v.y() << " h: " << v.h();
}

inline Vec2 operator+(const Vec2 &u, const Vec2 &v) {
    return Vec2(u.x() + v.x(), u.y() + v.y(), u.h() + v.h());
}

inline Vec2 operator-(const Vec2 &u, const Vec2 &v) {
    return Vec2(u.x() - v.x(), u.y() - v.y(), u.h() - v.h());
}

inline Vec2 operator*(const Vec2 &u, const Vec2 &v) {
    return Vec2(u.x() * v.x(), u.y() * v.y(), u.h() * v.h());
}

inline Vec2 operator*(double t, const Vec2 &v) {
    return Vec2( t * v.x(), t * v.y(), t * v.h());
}

inline Vec2 operator*(const Vec2 &v, double t) {
    return t*v;
}

inline Vec2 operator/(const Vec2 &v, double t) {
    return (1/t)*v;
}

inline double dot(const Vec2 &u, const Vec2 &v) {
    return  u.x() * v.x()
        +   u.y() * v.y()
        +   (u.Homog() ? u.h() * v.h() : 0);        // Only dot 'h' if homog.
}

inline double cross(const Vec2 &u, const Vec2 &v) { // 2D cross product is just a scalar.
    return u.x() * v.y() - u.y() * v.x();
}

inline Vec2 unitVector(Vec2 v){
    return v / v.magnitude();
}
#endif
/* 
 * matrix.h
 * Declares a matrix class, related methods
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */

#ifndef _MATRIX_H
#define _MATRIX_H

#include <vector>

#include "graphics.h"

using std::vector;

/* Matrix transformation types */
enum matrixtype {empty, identity, translation, rotation, scaling};

// Only square matricies for now!
class Matrix{
    public:
        Matrix(int dimension, matrixtype type = empty, 
            double transform_x=0, double transform_y=0, 
            double scale_x=0, double scale_y=0
        );

        int size() const { return m.size(); }

        // matrix(i,j) == matrix.m[i][j]
        double  operator()(int x, int y) const 
            { return m.at(x).at(y); } // Return constant of value 

        double& operator()(int x, int y)       
            { return m.at(x).at(y); } // Return reference to value

        /* Internal operator overloads */
        Matrix& operator-();
        Matrix& operator*=(const double t);
        Matrix& operator+=(const Matrix &matrix);
        Matrix& operator*=(const Matrix &matrix);

    private:
        int dim; // What graphics-related dimension it supports 
        vector<vector<double>> m;

        void setTranslationMatrix2D(double tx, double ty);
        void setScalingMatrix2D(double sx, double sy);
        void setIdentityMatrix();
};

std::ostream& operator<<(std::ostream &out, const Matrix &matrix);
Matrix operator*(double t, const Matrix &matrix);

Matrix operator+(const Matrix &u, const Matrix &v);
Matrix operator-(const Matrix &u, const Matrix &v);
Matrix operator*(const Matrix &u, const Matrix &v);

Point2 operator*(const Matrix& m1, const Point2& p);
Point3 operator*(const Matrix& m1, const Point3& p);

#endif
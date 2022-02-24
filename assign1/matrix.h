//matrix.h

#ifndef _MATRIX_H
#define _MATRIX_H

#include "graphics.h"

enum matrixtype {custom, translation, rotation, scaling};

// Only square matricies for now
class Matrix{
    public:
        Matrix(int ndim, matrixtype type = custom, double tx=0, double ty=0, double sx=0, double sy=0);
        ~Matrix();
        void print();


        double **m;
    private:
        int dim; // What graphics-related dimension it supports 


        void setTranslationMatrix2D(double tx, double ty);
        void setScalingMatrix2D(double sx, double sy);
        void setIdentityMatrix();
        void resetMatrix();
};

Matrix& operator*(const Matrix& m1, const Matrix& m2);
point2D& operator*(const Matrix& m1, point2D& p);

#endif
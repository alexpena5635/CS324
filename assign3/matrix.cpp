/* 
 * matrix.cpp
 * Defines a matrix class, related methods
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */

#include <iostream>

#include "graphics.h"
#include "matrix.h"

Matrix::Matrix(int dimension, matrixtype type/* = empty*/, 
            double transform_x, double transform_y, 
            double scale_x, double scale_y
        )
        : dim(dimension)
{
    m.resize(dim, vector<double>(dim, 0.0));
    
    switch(type)
    {
        case empty:
            break;
        case identity:
            setIdentityMatrix();
            break;
        case translation:
            setTranslationMatrix2D(transform_x, transform_y);
            break;
        case rotation:
            break;
        case scaling:
            setScalingMatrix2D(scale_x, scale_y);
            break;
        default:
            std::cout << "ERROR: Unrecognized \"matrixtype\" type in constructor of matrix" << std::endl;
            break;
    };
}

void Matrix::setTranslationMatrix2D(double tx, double ty)
{
    // Setting identity matrix
    setIdentityMatrix();

	// Setting x and y translations
    m.at(0).at(2) = tx;
    m.at(1).at(2) = ty;// tx; // This caused me lots of issues. I am big dumb.
}

void Matrix::setScalingMatrix2D(double sx, double sy)
{
    // Setting identity matrix
    setIdentityMatrix();

	// Setting x and y scale factors
    m.at(0).at(0) = sx;
    m.at(1).at(1) = sy;
}

void Matrix::setIdentityMatrix()
{
    // Setting identity matrix
    for(int i=0; i<m.size(); i++) 
	{
		m.at(i).at(i) = 1;
	}
}

/****** 
 * 
 * Internal operator overloads 
 * 
 * ******/

Matrix& Matrix::operator-() {
    Matrix res(3);
    for(int i = 0; i < size(); i++)
    {
        for (int j = 0; j < size(); j++)
        {
            m.at(i).at(j) *= -1;
            double tmp = m.at(i).at(j);
            res(i, j) = tmp;
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const double t){
    for (auto &row : m) {
        for (auto &col_val : row) {
            col_val *= t;
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix &matrix){
    if(size() != matrix.size()) {
        std::cout << "[ERROR] Operator '*=': matricies have different sizes" << std::endl;
        exit(-1);
    }

    for(int i = 0; i < size(); i++)
    {
        for (int j = 0; j < size(); j++)
        {
            m.at(i).at(j) += matrix(i, j);
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix &matrix){
    if(size() != matrix.size()) {
        std::cout << "[ERROR] Operator '*=': matricies have different sizes" << std::endl;
        exit(-1);
    }

    Matrix res(size());

    for(int i = 0; i < size(); i++)
    {
        for (int j = 0; j < size(); j++)
        {
            for(int k = 0; k < size(); k++)
            {
                 res(i, j) += m.at(i).at(k) * matrix(k, j);
            }
        }
    }
    m = res.m;
    return *this;
}

/****** 
 * 
 * External operator overloads 
 * 
 * ******/
std::ostream& operator<<(std::ostream &out, const Matrix &matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            out << matrix(i, j) << '\t';
        }
        out << '\n';
    }
    return out;
}

Matrix operator*(double t, const Matrix &matrix){
    Matrix tmp(matrix.size());

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            tmp(i, j) = t*matrix(i, j);
        }
    }
    return tmp;
};

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    if(m1.size() != m2.size()) {
        std::cout << "[ERROR] Operator '*': matricies have different sizes" << std::endl;
        exit(-1);
    }
        
    Matrix res(m1.size());

    for(int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res.size(); j++)
        {
            res(i, j) = m1(i, j) + m2(i, j);
        }
    }

    return res;
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    if(m1.size() != m2.size()) {
        std::cout << "[ERROR] Operator '*': matricies have different sizes" << std::endl;
        exit(-1);
    }
        
    Matrix res(m1.size());

    for(int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res.size(); j++)
        {
            res(i, j) = m1(i, j) - m2(i, j);
        }
    }

    return res;
}

/* Operator '*' overload for two matricies
 * - We assume both are square and of dim*dim size
 * Reference to double check my matrix multiplication
 * - https://www.programiz.com/cpp-programming/examples/matrix-multiplication 
 */
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    if(m1.size() != m2.size()) {
        std::cout << "[ERROR] Operator '*': matricies have different sizes" << std::endl;
        exit(-1);
    }
        
    Matrix res(m1.size());

    for(int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res.size(); j++)
        {
            for(int k = 0; k < res.size(); k++)
            {
                 res(i, j) += m1(i, k) * m2(k, j);
            }
           
        }
    }

    return res;
}

// Operator * overload for a matrix and a point (2d matrix against a 2d point, and so on)
Point2 operator*(const Matrix& m1, const Point2& p)
{
    if(m1.size() != 3) {
        std::cout << "[ERROR] Operator '*': matrix and vector do not match" << std::endl;
        exit(-1);
    }

    // In my old system, I set the 'h' component to be 0, but now its 1!!!
    // Must account for this by forcing h to be 0
    Point2 p2(0,0,0); 

    for(int i = 0; i < m1.size(); i++)
    {
        for (int j = 0; j < m1.size(); j++)
        {
            p2[i] += m1(i, j) * p[j];
            // std::cout << "newPoint[" << j << "] " << newPoint[j] << std::endl;
        }
    }
    return p2;
}

// Operator * overload for a matrix and a point (3d matrix against a 3d point, and so on)
Point3 operator*(const Matrix& m1, const Point3& p)
{
    if(m1.size() != 4) {
        std::cout << "[ERROR] Operator '*': matrix and vector do not match" << std::endl;
        exit(-1);
    }

    // In my old system, I set the 'h' component to be 0, but now its 1!!!
    // Must account for this by forcing h to be 0
    Point3 p3(0,0,0,0);

    for(int i = 0; i < m1.size(); i++)
    {
        for (int j = 0; j < m1.size(); j++)
        {
            p3[i] += m1(i, j) * p[j];
            // std::cout << "newPoint[" << j << "] " << newPoint[j] << std::endl;
        }
    }
    return p3;
}


// // Testing matrix mult
// int main()
// {
//     // Matrix tm(3, translation, -1, -1);
//     // Matrix sm(3, scaling, 0, 0, .2, .2);
//     // Matrix tm2(3, translation, 10, 10);

//     // Point2 p(-5, -5);

//     // std::cout << tm << std::endl
//     //     << sm   << std::endl
//     //     << tm2  << std::endl 
//     //     << p    << std::endl;
    

//     // Matrix resM = tm * sm;// * tm2;
//     // std::cout << '\n' << resM << std::endl;


//     // // resM = tm * sm * tm2;
//     // resM *= tm2;
//     // std::cout << '\n' << resM << std::endl;


//     // std::cout << "Viewport point: " << resM * p << std::endl;

//     Matrix id(4, identity);
//     Point3 p3(1, 1, 1, 1);

//     std::cout << "p3: " << p3 << "\nid: \n" << id << "\n\nid * p3: " << id*p3 << std::endl;

//     return 0;
// }


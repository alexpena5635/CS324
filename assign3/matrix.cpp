// matrix.cpp
#include <iostream>

#include "graphics.h"
#include "matrix.h"

Matrix::Matrix(int ndim, matrixtype type/*=custom*/, double tx, double ty, double sx, double sy)
{
    dim = ndim;
    m = new double*[dim]; // allocate space for the rows
    for(int i = 0; i < dim; i++)
    {
        m[i] = new double[dim]; // allocate space for the columns
    }

    switch(type)
    {
        case custom:
            resetMatrix();
            break;
        case identity:
            setIdentityMatrix();
            break;
        case translation:
            setTranslationMatrix2D(tx, ty);
            break;
        case rotation:
            resetMatrix();
            break;
        case scaling:
            setScalingMatrix2D(sx, sy);
            break;
        default:
            std::cout << "ERROR: Unrecognized \"matrixtype\" type in constructor of matrix" << std::endl;
            break;
    };
}

// Issues using the destructor bc since it is dynamically allocated it never goes out of scope or gets called
// Matrix::~Matrix() 
// {
//     // Deallocate the array representing the matrix
//     for (int i = 0; i < dim; ++i) {
//         delete[] m[i];
//     }
//     delete[] m;
// }
void Matrix::deallocate()
{
    // Deallocate the array representing the matrix
    for (int i = 0; i < dim; ++i) {
        delete[] m[i];
        m[i] = NULL;
    }
    delete[] m;
    m = NULL;
}


void Matrix::print()
{
    for(int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout << m[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


void Matrix::setTranslationMatrix2D(double tx, double ty)
{
    // Setting identity matrix
    setIdentityMatrix();

	// Setting x and y translations
	m[0][dim-1] = tx;
	m[1][dim-1] = ty; 
}

void Matrix::setScalingMatrix2D(double sx, double sy)
{
    // Setting identity matrix
    setIdentityMatrix();

	// Setting x and y scale factors
	m[0][0] = sx;
	m[1][1] = sy;
}

void Matrix::setIdentityMatrix()
{
    resetMatrix(); // needed to do this as we were not intialzing the values!
    // Setting identity matrix
    for(int i=0; i<dim; i++) 
	{
		m[i][i] = 1;
	}
}

void Matrix::resetMatrix()
{
    for(int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            m[i][j] = 0;
        }
    }
}

// Operator * overload for two matricies
// - We assume both are square and of dim*dim size
// Reference to double check my matrix multiplication
// - https://www.programiz.com/cpp-programming/examples/matrix-multiplication 
Matrix& operator*(const Matrix& m1, const Matrix& m2)
{
    int dim = 3;
    Matrix* res = new Matrix(dim);

    for(int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            for(int k = 0; k < dim; k++)
            {
                 (*res).m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
           
        }
    }

    return *res;
}

// Operator * overload for a matrix and a point (2d matrix against a 2d point, and so on)
// - We assume matrix has same amount of cols as vector does rows
Point2& operator*(const Matrix& m1, const Point2& p)
{
    const int dim = 3;

    double newPoint[dim] = {};
	double inPoint[dim] = {p.x(), p.y(), p.h()};

    for(int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            newPoint[i] += m1.m[i][j] * inPoint[j];
            // std::cout << "newPoint[" << j << "] " << newPoint[j] << std::endl;
        }
    }

    Point2 *p2 = new Point2;
    p2->set(newPoint[0], newPoint[1], newPoint[2], true);
    return *p2;
}

// Operator * overload for a matrix and a point (3d matrix against a 3d point, and so on)
// - We assume matrix has same amount of cols as vector does rows
Point3& operator*(const Matrix& m1, const Point3& p)
{
    const int dim = 4;

    double newPoint[dim] = {};
	double inPoint[dim] = {p.x(), p.y(), p.z(), p.h()};

    for(int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            newPoint[i] += m1.m[i][j] * inPoint[j];
            // std::cout << "newPoint[" << j << "] " << newPoint[j] << std::endl;
        }
    }

    Point3 *p2 = new Point3;
    p2->set(newPoint[0], newPoint[1], newPoint[2], newPoint[3]);
    return *p2;
}

/*
// Testing matrix mult
int main()
{
    Matrix tm(3, translation, -1, -1);
    Matrix sm(3, scaling, 0, 0, .2, .2);
    Matrix tm2(3, translation, 10, 10);

    Point2 p(-5, -5);

    tm.print();
    std::cout << std::endl;
    sm.print();
    std::cout << std::endl;
    tm2.print();
    std::cout << std::endl << p << std::endl;
    

    Matrix resM = tm * sm * tm2;
    std::cout << std::endl;
    resM.print();

    std::cout << "Viewport point: " << resM * p << std::endl;
}
*/
#include <iostream>
#include <cmath>

#include "graphics.h"
#include "matrix.h"

enum transformCode {X_TRANS, Y_TRANS, Z_TRANS, X_ROT, Y_ROT, Z_ROT, PERSPECTIVE};

/* (fx, fy, fz) - Focal point; (theta, phi, alpha) - Orientation; (r) - Distance eye to origin */
void DefineCameraTransform(double fx, double fy, double fz, double theta, double phi, double alpha, double r);

/* Pass in a matrix to intialize, the type of transform, and the value */
void DefineElementaryTransform(Matrix m, transformCode tfCode, double tfValue);

/* Pass in a matrix to premultiply, the type of transform, and the value */
void BuildElementaryTransform(Matrix tfM, transformCode tfCode, double tfValue);

void MoveTo3D(double x, double y, double z);
void Draw3D(double x, double y, double z);

/* Pass in a matrix to premultiply, the type of transform, and the value */
void ApplyTransform(double x, double y, double z, Matrix& tfm, point3D& outVector);


// Asuming we have global canvas
// In my actual code this will look different, but this is assumptions for this proof of concept
Canvas c;
Matrix aT(4, identity);
Matrix CAMERA(4);

void DrawUnitCube()
{
    /*
        fX, fY, fZ,
        theta, phi, alpha,
        r
    */
    DefineCameraTransform(
                            0.0, 1.0, 0.0,
                            45, 30, 0,
                            25 
                        );
    

    /* Drawing the front side of the cube */
    MoveTo3D(0, 0, 0);
    Draw3D(0, 1, 0);
    Draw3D(0, 0, 1);
    MoveTo3D(0, 1, 1);
    Draw3D(0, 0, 1);
    Draw3D(0, 1, 0);

    /* Drawing the back side of the cube */
    MoveTo3D(1, 1, 0);
    Draw3D(1, 0, 0);
    Draw3D(1, 1, 1);
    MoveTo3D(1, 0, 1);
    Draw3D(1, 1, 1);
    Draw3D(1, 0, 0);

    /* Drawing the left side of the cube */
    MoveTo3D(1, 0,0);
    Draw3D(0, 0, 0);
    Draw3D(1, 0, 1);
    MoveTo3D(0, 0, 1);
    Draw3D(1, 0, 1);
    Draw3D(0, 0, 0);

    /* Drawing the right side of the cube */
    MoveTo3D(0, 1,0);
    Draw3D(1, 1, 0);
    Draw3D(0, 1, 1);
    MoveTo3D(1, 1, 1);
    Draw3D(0, 1, 1);
    Draw3D(1, 1, 0);

    /* Drawing the bottom side of the cube */
    MoveTo3D(1, 0,0);
    Draw3D(1, 1, 0);
    Draw3D(0, 0, 0);
    MoveTo3D(0, 1, 0);
    Draw3D(0, 0, 0);
    Draw3D(1, 1, 0);

    /* Drawing the top side of the cube */
    MoveTo3D(0, 0, 1);
    Draw3D(0, 1, 1);
    Draw3D(1, 0, 1);
    MoveTo3D(1, 1, 1);
    Draw3D(1, 0, 1);
    Draw3D(0, 1, 1);
}

void DefineCameraTransform(double fx, double fy, double fz, double theta, double phi, double alpha, double r)
{
    DefineElementaryTransform(CAMERA, X_TRANS, -fx);
    BuildElementaryTransform(CAMERA, Y_TRANS, -fy);
    BuildElementaryTransform(CAMERA, Z_TRANS, -fz);


    BuildElementaryTransform(CAMERA, Y_ROT, -theta);
    BuildElementaryTransform(CAMERA, X_ROT, phi);
    BuildElementaryTransform(CAMERA, Z_ROT, -alpha);


    BuildElementaryTransform(CAMERA, PERSPECTIVE, r);
}

void DefineElementaryTransform(Matrix m, transformCode tfCode, double tfValue)
{
    m.setIdentityMatrix();

    switch(tfCode)
    {
        case X_TRANS:
            m.m[3][0] = tfValue;
            break;
        case Y_TRANS:
            m.m[3][1] = tfValue;
            break;
        case Z_TRANS:
            m.m[3][2] = tfValue;
            break;
        case X_ROT:
            m.m[1][1] = cos(tfValue);
            m.m[1][2] = sin(tfValue);
            m.m[2][1] = -sin(tfValue);
            m.m[2][2] = cos(tfValue);
            break;
        case Y_ROT:
            m.m[0][0] = cos(tfValue);
            m.m[0][2] = sin(tfValue);  // -sin(tfValue);
            m.m[2][0] = -sin(tfValue); // sin(tfValue);
            m.m[2][2] = cos(tfValue);
            break;
        case Z_ROT:
            m.m[0][0] = cos(tfValue);
            m.m[0][1] = sin(tfValue);
            m.m[1][0] = -sin(tfValue);
            m.m[1][1] = cos(tfValue);
            break;
        case PERSPECTIVE:
            m.m[2][3] = -(1/tfValue);
            break;
        default:
            break;
    };
}

void BuildElementaryTransform(Matrix tfM, transformCode tfCode, double tfValue)
{
    Matrix m(4), m2(4);

    DefineElementaryTransform(m, tfCode, tfValue);

    tfM =  tfM * m;
}

void MoveTo3D(double x, double y, double z)
{
    point3D curr;
    ApplyTransform(x, y, z, aT, curr);
    ApplyTransform(curr.x, curr.y, curr.z, CAMERA, curr);

    //point2D curr2d(curr3d.x, curr3d.y);
    //point2D newPoint;
    //WindowToViewport(p2d, newPoint);

    MoveTo2D(curr.x, curr.y);
}

void Draw3D(double x, double y, double z)
{
    point3D goal;
    ApplyTransform(x, y, z, aT, goal);
    ApplyTransform(goal.x, goal.y, goal.z, CAMERA, goal);

    /* DrawTo2D converts the 2d window coords to viewport and then to pixmap */
    DrawTo2D(c, colors::BLACK, goal.x, goal.y); //asuming glboal canvas c
}

void ApplyTransform(double x, double y, double z, const Matrix& tfm, point3D& outVector)
{
    point3D p(x, y, z);

    outVector = tfm * p;
}


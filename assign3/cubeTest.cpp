/* 
 * cubeTest.cpp
 * Test file for 3d
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */

#include <iostream>
#include <cmath>

#include "graphics.h"
#include "matrix.h"

void DrawUnitCube();

int main()
{
    DrawUnitCube();
    return 0;
}

void DrawUnitCube()
{
    GraphicsSystem gs;
    /*
        fX, fY, fZ,
        theta, phi, alpha,
        r
    */

    gs.initGraphics(1000, 1000);

    gs.defineCameraTransform
    (
        0.0, 1.0, 0.0,
        45, 30, 0,
        25 
    );

    const int side_length = 5;
    

    /* Drawing the front side of the cube */
    gs.moveTo3D(0, 0, 0);
    gs.draw3D(0, side_length, 0);
    gs.draw3D(0, 0, side_length);
    gs.moveTo3D(0, side_length, side_length);
    gs.draw3D(0, 0, side_length);
    gs.draw3D(0, side_length, 0);

    /* Drawing the back side of the cube */
    gs.moveTo3D(side_length, side_length, 0);
    gs.draw3D(side_length, 0, 0);
    gs.draw3D(side_length, side_length, side_length);
    gs.moveTo3D(side_length, 0, side_length);
    gs.draw3D(side_length, side_length, side_length);
    gs.draw3D(side_length, 0, 0);

    /* Drawing the left side of the cube */
    gs.moveTo3D(side_length, 0,0);
    gs.draw3D(0, 0, 0);
    gs.draw3D(side_length, 0, side_length);
    gs.moveTo3D(0, 0, side_length);
    gs.draw3D(side_length, 0, side_length);
    gs.draw3D(0, 0, 0);

    /* Drawing the right side of the cube */
    gs.moveTo3D(0, side_length,0);
    gs.draw3D(side_length, side_length, 0);
    gs.draw3D(0, side_length, side_length);
    gs.moveTo3D(side_length, side_length, side_length);
    gs.draw3D(0, side_length, side_length);
    gs.draw3D(side_length, side_length, 0);

    /* Drawing the bottom side of the cube */
    gs.moveTo3D(side_length, 0,0);
    gs.draw3D(side_length, side_length, 0);
    gs.draw3D(0, 0, 0);
    gs.moveTo3D(0, side_length, 0);
    gs.draw3D(0, 0, 0);
    gs.draw3D(side_length, side_length, 0);

    /* Drawing the top side of the cube */
    gs.moveTo3D(0, 0, side_length);
    gs.draw3D(0, side_length, side_length);
    gs.draw3D(side_length, 0, side_length);
    gs.moveTo3D(side_length, side_length, side_length);
    gs.draw3D(side_length, 0, side_length);
    gs.draw3D(0, side_length, side_length);

    gs.saveCanvas("cube.pbm");
}
/* 
 * modeling3d.cpp
 * Assignment 3 implementation file
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

#define _USE_MATH_DEFINES

void drawCube(GraphicsSystem &gs, const int side_length, const Point3 &from_point);
void drawUnitCube(GraphicsSystem &gs) {
    drawCube(gs, 1, Point3(0,0,0));
}

double eq(double x, double y, double r);

void drawAxis(GraphicsSystem &gs, color draw_color, Point3 origin, 
    double x_min, double x_max, 
    double y_min, double y_max,
    double z_min, double z_max);

void plotEq(GraphicsSystem &gs, Point3 origin);

int main()
{
    GraphicsSystem gs;
    // drawCube(gs, 5, Point3(0,0,0));  // y+ horizontal right, z+ vertical down
    // drawUnitCube(gs);
    // plotEq(gs, Point3(0,0,0));
    return 0;
}

void drawCube(GraphicsSystem &gs, const int side_length, const Point3 &from_point)
{
    //GraphicsSystem gs;
    /*
        fX, fY, fZ,
        theta, phi, alpha,
        r
    */

    gs.initGraphics(1000, 1000, -5, -5, 5, 5);

    gs.defineCameraTransform
    (
        0.0, 1.0, 0.0,
        45, 30, 0,
        25 
    );

    double x = from_point.x();
    double y = from_point.y();
    double z = from_point.z();

    /* Drawing the front side of the cube */
    gs.moveTo3D (x,                 y,                  z);
    gs.drawTo3D   (x,                 y+side_length,      z);
    gs.drawTo3D   (x,                 y,                  z+side_length);
    gs.moveTo3D (x,                 y+side_length,      z+side_length);
    gs.drawTo3D   (x,                 y,                  z+side_length);
    gs.drawTo3D   (x,                 y+side_length,      z);

    /* Drawing the back side of the cube */
    gs.moveTo3D (x+side_length,     y+side_length,      z);
    gs.drawTo3D   (x+side_length,     y,                  z);
    gs.drawTo3D   (x+side_length,     y+side_length,      z+side_length);
    gs.moveTo3D (x+side_length,     y,                  z+side_length);
    gs.drawTo3D   (x+side_length,     y+side_length,      z+side_length);
    gs.drawTo3D   (x+side_length,     y,                  z);

    /* Drawing the left side of the cube */
    gs.moveTo3D (x+side_length,     y,                  z);
    gs.drawTo3D   (x,                 y,                  z);
    gs.drawTo3D   (x+side_length,     y,                  z+side_length);
    gs.moveTo3D (x,                 y,                  z+side_length);
    gs.drawTo3D   (x+side_length,     y,                  z+side_length);
    gs.drawTo3D   (x,                 y,                  z);

    /* Drawing the right side of the cube */
    gs.moveTo3D (x,                 y+side_length,      z);
    gs.drawTo3D   (x+side_length,     y+side_length,      z);
    gs.drawTo3D   (x,                 y+side_length,      z+side_length);
    gs.moveTo3D (x+side_length,     y+side_length,      z+side_length);
    gs.drawTo3D   (x,                 y+side_length,      z+side_length);
    gs.drawTo3D   (x+side_length,     y+side_length,      z);

    /* Drawing the bottom side of the cube */
    gs.moveTo3D (x+side_length,     y,                  z);
    gs.drawTo3D   (x+side_length,     y+side_length,      z);
    gs.drawTo3D   (x,                 y,                  z);
    gs.moveTo3D (x,                 y+side_length,      z);
    gs.drawTo3D   (x,                 y,                  z);
    gs.drawTo3D   (x+side_length,     y+side_length,      z);

    /* Drawing the top side of the cube */
    gs.moveTo3D (x,                 y,                  z+side_length);
    gs.drawTo3D   (x,                 y+side_length,      z+side_length);
    gs.drawTo3D   (x+side_length,     y,                  z+side_length);
    gs.moveTo3D (x+side_length,     y+side_length,      z+side_length);
    gs.drawTo3D   (x+side_length,     y,                  z+side_length);
    gs.drawTo3D   (x,                 y+side_length,      z+side_length);

    gs.saveCanvas(SAVEPATH3D + "cube.pbm");
    gs.clearCanvas();
}

double eq(double x, double y, double r) {
    double numer = (sin(r)/r);
    double denom = 9*cos(x/(y+0.02));
    double res = numer/denom;
    return res;
}

void drawAxis(GraphicsSystem &gs, color draw_color, Point3 origin, 
    double x_min, double x_max, 
    double y_min, double y_max,
    double z_min, double z_max)
{
    gs.moveTo3D(x_min, origin.y(), origin.z());
    gs.drawTo3D(x_max, origin.y(), origin.z(), draw_color);//colors::BLACK);

    gs.moveTo3D(origin.x(), y_min, origin.z());
    gs.drawTo3D(origin.x(), y_max, origin.z(), draw_color);//colors::BLUE);

    gs.moveTo3D(origin.x(), origin.y(), z_min);
    gs.drawTo3D(origin.x(), origin.y(), z_max, colors::BLUE);//colors::GREEN);
}

void plotEq(GraphicsSystem &gs, Point3 origin)
{
    gs.initGraphics(1000, 1000);//, -15, -15, 15, 15);

    gs.defineCameraTransform
    (
        0.0, 0.0, 0.0,
        15, 30, 0,
        25
    );

    double x_min, x_max;
    double y_min, y_max;
    double z_min, z_max;
    
    x_min = y_min = -2*M_PI;
    x_max = y_max = 2*M_PI;


    drawAxis(gs, colors::BLACK, origin, 
        -10, 10, -10, 10, -15, 15);

    double x = x_min;
    double y = y_min;
    double inc = (M_PI/180);

    double z = eq(x, y, (x*x) + (y*y));

    for (x = x_min; x <= x_max; x+=inc) {
        // std::cout << "\r[X] Lines remaining: " << trunc(x_max-x) << std::flush;
        for (y = y_min; y <= y_max; y+=inc) {

            std::cout << "\r[X] Lines remaining: " 
                << trunc(x_max-x) << "\t[Y] Lines remaining: " 
                << trunc(y_max-y) << std::flush;

            gs.moveTo3D(x, y, z);

            z = eq(x, y, (x*x) + (y*y));

            gs.drawTo3D(x, y, z, colors::GREEN);
            gs.moveTo3D(x, y, z);

            // std::cout << "looping\nx: " << x << "\ny: " << y << "\nz: " << z << '\n' << std::endl;
        }
    }

    std::cout << '\n';

    gs.saveCanvas(SAVEPATH3D + "plot_final.pbm");
    gs.clearCanvas();
}
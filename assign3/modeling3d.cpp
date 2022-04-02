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

enum face {front, back, left, right, bottom, top};
color default_colors[6] = {colors::BLACK};

void drawFace(GraphicsSystem &gs, const int len, const Point3 p, color c, face f=front);

void drawCube(GraphicsSystem &gs, const int len, const Point3 p, bool init=true, color colors[6]=default_colors);

void drawUnitCube(GraphicsSystem &gs) {
    drawCube(gs, 1, Point3(0,0,0));
}

double eq(const double x, const double y, const double r);

void drawAxis(GraphicsSystem &gs, const Point3 origin, 
    double x_min, double x_max, 
    double y_min, double y_max,
    double z_min, double z_max);

void plotEq(GraphicsSystem &gs, const Point3 origin);

void drawRubiksCube(GraphicsSystem &gs, const Point3 p, bool gap=false);


int main()
{
    GraphicsSystem gs;
    // color colors[6] = {colors::GREEN, colors::GREEN, colors::BLUE, colors::BLUE, colors::RED, colors::RED};
    // drawCube(gs, 2, Point3(0,0,0), true, colors);  // y+ horizontal right, z+ vertical down
    // drawUnitCube(gs);
    // plotEq(gs, Point3(0,0,0));
    // drawRubiksCube(gs, Point3(0,0,0), true);
    return 0;
}

void drawFace(GraphicsSystem &gs, const int len, const Point3 p, color c, face f)
{
    double x = p.x();
    double y = p.y();
    double z = p.z();

    switch(f) {
        case front:
            /* Drawing the front side of the cube */
            gs.moveTo3D (x,                 y,                  z);
            gs.drawTo3D   (x,                 y+len,      z, c);
            gs.drawTo3D   (x,                 y,                  z+len, c);
            gs.moveTo3D (x,                 y+len,      z+len);
            gs.drawTo3D   (x,                 y,                  z+len, c);
            gs.drawTo3D   (x,                 y+len,      z, c);
            break;

        case back:
            /* Drawing the back side of the cube */
            gs.moveTo3D (x+len,     y+len,      z);
            gs.drawTo3D   (x+len,     y,                  z, c);
            gs.drawTo3D   (x+len,     y+len,      z+len, c);
            gs.moveTo3D (x+len,     y,                  z+len);
            gs.drawTo3D   (x+len,     y+len,      z+len, c);
            gs.drawTo3D   (x+len,     y,                  z, c);
            break;

        case left: 
            /* Drawing the left side of the cube */
            gs.moveTo3D (x+len,     y,                  z);
            gs.drawTo3D   (x,                 y,                  z, c);
            gs.drawTo3D   (x+len,     y,                  z+len, c);
            gs.moveTo3D (x,                 y,                  z+len);
            gs.drawTo3D   (x+len,     y,                  z+len, c);
            gs.drawTo3D   (x,                 y,                  z, c);
            break;

        case right:
            /* Drawing the right side of the cube */
            gs.moveTo3D (x,                 y+len,      z);
            gs.drawTo3D   (x+len,     y+len,      z, c);
            gs.drawTo3D   (x,                 y+len,      z+len, c);
            gs.moveTo3D (x+len,     y+len,      z+len);
            gs.drawTo3D   (x,                 y+len,      z+len, c);
            gs.drawTo3D   (x+len,     y+len,      z, c);
            break;

        case bottom:
            /* Drawing the bottom side of the cube */
            gs.moveTo3D (x+len,     y,                  z);
            gs.drawTo3D   (x+len,     y+len,      z, c);
            gs.drawTo3D   (x,                 y,                  z, c);
            gs.moveTo3D (x,                 y+len,      z);
            gs.drawTo3D   (x,                 y,                  z, c);
            gs.drawTo3D   (x+len,     y+len,      z, c);
            break;

        case top:
            /* Drawing the top side of the cube */
            gs.moveTo3D (x,                 y,                  z+len);
            gs.drawTo3D   (x,                 y+len,      z+len, c);
            gs.drawTo3D   (x+len,     y,                  z+len, c);
            gs.moveTo3D (x+len,     y+len,      z+len);
            gs.drawTo3D   (x+len,     y,                  z+len, c);
            gs.drawTo3D   (x,                 y+len,      z+len, c);
            break;
        default:
            std::cout << "ERROR: Unknown face case\n";
            break;
    };

}

void drawCube(GraphicsSystem &gs, const int len, const Point3 p, bool init, color colors[6])
{
    //GraphicsSystem gs;
    /*
        fX, fY, fZ,
        theta, phi, alpha,
        r
    */

    if (init) {
        gs.initGraphics(1000, 1000, -5, -5, 5, 5);

        gs.defineCameraTransform
        (
            0.0, 1.0, 0.0,
            45, 30, 0,
            25 
        );
    }

    drawFace(gs, len, p, colors[0], front);
    drawFace(gs, len, p, colors[1], left);
    drawFace(gs, len, p, colors[2], bottom);

    drawFace(gs, len, p, colors[3], right);
    drawFace(gs, len, p, colors[4], top);
    drawFace(gs, len, p, colors[5], back);


    if(init) {
        gs.saveCanvas(SAVEPATH3D + "cube.pbm");
        gs.clearCanvas();
    }
}

double eq(double x, double y, double r) {
    double numer = (sin(r)/r);
    double denom = 9*cos(x/(y+0.02));
    double res = numer/denom;
    return res;
}

void drawAxis(GraphicsSystem &gs, Point3 origin, 
    double x_min, double x_max, 
    double y_min, double y_max,
    double z_min, double z_max)
{
    gs.moveTo3D(x_min, origin.y(), origin.z());
    gs.drawTo3D(x_max, origin.y(), origin.z(), colors::BLACK);

    gs.moveTo3D(origin.x(), y_min, origin.z());
    gs.drawTo3D(origin.x(), y_max, origin.z(), colors::BLUE);

    gs.moveTo3D(origin.x(), origin.y(), z_min);
    gs.drawTo3D(origin.x(), origin.y(), z_max, colors::GREEN);
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


    drawAxis(gs, origin, 
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

void drawRubiksCube(GraphicsSystem &gs, Point3 p, bool gap/*=false*/)
{
    gs.initGraphics(1000, 1000);

    gs.defineCameraTransform
    (
        0.0, 0.0, 0.0,  // phi is definitely vertical on z 
        32, 12, 0,
        25
    );

    int len = 2;

    int l = len;
    if(gap)
        l = len * 1/2;


    for(int i = 0;  i < 3; i++) {
        for(int j = 0;  j < 3; j++) {
            for(int k = 0;  k < 3; k++) {
                // std::cout << "\rLines completed: " 
                //     << trunc(j) << std::flush;
                Point3 tmp(p.x() + len*i, p.y() + len*j, p.z() + len*k);


                color cs[6] = {colors::ORANGE, colors::CYAN, colors::GREEN, colors::BLUE, colors::BLACK, colors::RED};

                drawCube(gs, l, tmp, false, cs);

                // color c;
                // c = colors::BLACK;
          
                // if (k == 2) {
                //     c = colors::GREEN;
                //     // drawFace(gs, len, tmp, colors::CYAN, front);
                //     // drawFace(gs, len, tmp, c, back);
                //     drawFace(gs, len, tmp, colors::ORANGE, left);
                //     // drawFace(gs, len, tmp, c, right);
                //     drawFace(gs, len, tmp, colors::BLACK, bottom);

                //     drawFace(gs, len, tmp, c, top); // This is the correct color
                // }
                // if (j == 2) {
                //     c = colors::BLUE;
                //     // drawFace(gs, len, tmp, colors::CYAN, left);

                //     drawFace(gs, len, tmp, c, right); // Correct color
                // }
                // if (i == 2) {
                //     c = colors::RED;
                //     // drawFace(gs, len, tmp, colors::CYAN, left);

                //     drawFace(gs, len, tmp, c, back); // correct color
                // }
               
            }
        }
    }

    std::cout << '\n';

    gs.saveCanvas(SAVEPATH3D + "rubix.pbm");
    gs.clearCanvas();
}

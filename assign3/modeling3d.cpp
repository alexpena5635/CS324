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

color default_colors[6] = {colors::BLACK};
double eq(const double x, const double y, const double r);
void drawAxis(GraphicsSystem &gs, const Point3 origin, 
    double x_min, double x_max, 
    double y_min, double y_max,
    double z_min, double z_max);

void drawSquare(GraphicsSystem &gs, const color c);
void drawCube(GraphicsSystem &gs, const Point3 p, const double spacing=0, 
    bool init=true, color colors[6]=default_colors);
void drawUnitCube(GraphicsSystem &gs) {
    drawCube(gs, Point3(0,0,0));
}

void plotEq(GraphicsSystem &gs, const Point3 origin);

void drawRubiksCube(GraphicsSystem &gs, const Point3 p, bool gap=false, bool init=true);
void drawRubiksGrid(GraphicsSystem &gs, const Point3 p);

int main()
{
    GraphicsSystem gs;
    // drawUnitCube(gs);
    // drawCube(gs, Point3(0,0,0), 0.075);
    // plotEq(gs, Point3(0,0,0));
    // drawRubiksCube(gs, Point3(0,0,0), true, true);
    // drawRubiksGrid(gs, Point3(0,0,0));
    return 0;
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
        30, 65, 0,
        25
    );

    gs.resetActiveTransform();

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

    gs.saveCanvas(SAVEPATH3D + "plot.pbm");
    gs.clearCanvas();
}


void drawSquare(GraphicsSystem &gs, const color c)
{
    Point3 vs[4] = {
        {-1,    -1, 1},
        {-1,    1,  1},
        {1,     1,  1},
        {1,     -1, 1}
    };

    for(int i = 0; i < 3; i++) {
        gs.moveTo3D(vs[i].x(), vs[i].y(), vs[i].z());
        gs.drawTo3D(vs[i+1].x(), vs[i+1].y(), vs[i+1].z(), c);
        gs.moveTo3D(vs[i+1].x(), vs[i+1].y(), vs[i+1].z());
    }
    gs.drawTo3D(vs[0].x(), vs[0].y(), vs[0].z(), c);
}

void drawCube(GraphicsSystem &gs, const Point3 p, const double spacing, bool init, color colors[6])
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

    // drawAxis(gs, p, 0, 3, 1, 3, 0, 3);
    const double b = spacing;

    // front
    gs.buildActiveTransform(X_TRANS, p.x());
    gs.buildActiveTransform(Y_TRANS, p.y());
    gs.buildActiveTransform(Z_TRANS, p.z());
    drawSquare(gs, colors[0]);

    // back
    gs.buildActiveTransform(Z_TRANS, -2);
    
    gs.buildActiveTransform(Z_TRANS, -b); // spacing out each face
    drawSquare(gs, colors::RED);
    gs.buildActiveTransform(Z_TRANS, b); // spacing out each face

    // left
    gs.buildActiveTransform(Z_TRANS, 2); // undo
    gs.buildActiveTransform(Y_ROT, -90);

    gs.buildActiveTransform(Z_TRANS, b); // spacing out each face
    drawSquare(gs, colors::BLUE);
    gs.buildActiveTransform(Z_TRANS, -b); // spacing out each face

    // right
    gs.buildActiveTransform(Y_ROT, 90); // undo
    gs.buildActiveTransform(Y_ROT, 90); 

    gs.buildActiveTransform(Z_TRANS, b); // spacing out each face
    drawSquare(gs, colors::CYAN);
    gs.buildActiveTransform(Z_TRANS, -b); // spacing out each face

    // top
    gs.buildActiveTransform(Y_ROT, -90); // undo
    gs.buildActiveTransform(X_ROT, -90);

    gs.buildActiveTransform(Z_TRANS, b); // spacing out each face
    drawSquare(gs, colors::ORANGE);
    gs.buildActiveTransform(Z_TRANS, -b); // spacing out each face

    // bottom
    gs.buildActiveTransform(X_ROT, 90);
    gs.buildActiveTransform(X_ROT, 90);

    gs.buildActiveTransform(Z_TRANS, b); // spacing out each face
    drawSquare(gs, colors::GREEN);
    gs.buildActiveTransform(Z_TRANS, -b); // spacing out each face

    gs.resetActiveTransform();

    // THIS IS WORKING CORRRECLTY< JUST HARD TO SEE!!!

    if(init) {
        gs.saveCanvas(SAVEPATH3D + "cube.pbm");
        gs.clearCanvas();
    }
}

void drawRubiksCube(GraphicsSystem &gs, Point3 p, bool gap/*=false*/, bool init)
{
    if(init) {
        gs.initGraphics(1000, 1000);

        gs.defineCameraTransform
        (
            0.0, 0.0, 0.0,  // phi is definitely vertical on z 
            32, 12, 0,
            25
        );
    }

    for(int i = 0;  i < 3; i++) {
        for(int j = 0;  j < 3; j++) {
            for(int k = 0;  k < 3; k++) {
                // std::cout << "\rLines completed: " 
                //     << trunc(j) << std::flush;
                // Point3 tmp(p.x() + len*i, p.y() + len*j, p.z() + len*k);
                Point3 tmp(p.x() + i, p.y() + j, p.z() + k);

                color cs[6] = {colors::BLUE, colors::RED, colors::GREEN, colors::ORANGE, colors::BLACK, colors::CYAN};

                if(gap) {
                    gs.buildActiveTransform(X_SCALE, 0.5);
                    gs.buildActiveTransform(Y_SCALE, 0.5);
                    gs.buildActiveTransform(Z_SCALE, 0.5);
                }

                drawCube(gs, tmp, 0, false, cs);
                gs.resetActiveTransform();
            }
        }
    }


    if(init) {
        std::cout << '\n';
        gs.saveCanvas(SAVEPATH3D + "rubix.pbm");
        gs.clearCanvas();
    }
}

void drawRubiksGrid(GraphicsSystem &gs, const Point3 p)
{
    gs.initGraphics(1000, 1000, -75, -75, 75, 75);

    gs.defineCameraTransform
    (
        0.0, 0.0, 0.0,  // phi is definitely vertical on z 
        32, 12, 0,
        25
    );

    int len = 4; // for each rubiks cube 2*3 == 6
    // int len = 6;

    int l = len/4;

    for(int i = 0;  i < 10; i++) {
        for(int j = 0;  j < 10; j++) {
            for(int k = 0;  k < 10; k++) {
                std::cout << "\rLines completed: " 
                    << i << ' ' << j << ' ' << k << std::flush;
                Point3 tmp(p.x() + len*i, p.y() + len*j, p.z() + len*k);

                // drawRubiksCube(gs, tmp, l, false, false);
                drawRubiksCube(gs, tmp, false, false);
            }
        }
    }


    std::cout << '\n';
    gs.saveCanvas(SAVEPATH3D + "rubix_grid.pbm");
    gs.clearCanvas();
}
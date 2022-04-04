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

void drawFace(GraphicsSystem &gs, const std::vector<Point3> &points, const double depth=0.0);
void drawShape(GraphicsSystem &gs, const std::vector<Point3> &points);
void drawRecognizer(GraphicsSystem &gs);
void drawBlockLetters(GraphicsSystem &gs);

int main()
{
    GraphicsSystem gs;
    // drawUnitCube(gs);
    // drawCube(gs, Point3(0,0,0), 0.075);
    // plotEq(gs, Point3(0,0,0));
    // drawRubiksCube(gs, Point3(0,0,0), true, true);
    // drawRubiksGrid(gs, Point3(0,0,0));
    // drawRecognizer(gs);
    drawBlockLetters(gs);
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

void drawFace(GraphicsSystem &gs, const std::vector<Point3> &points, const double depth/*=0.0*/)
{
    // Move to the first point
    gs.moveTo3D(points.front().x(), points.front().y(), points.front().z() + depth);

    // Draw lines between each subsequent point
    for(const auto& point : points) {
        gs.drawTo3D(point.x(), point.y(), point.z() + depth);
        gs.moveTo3D(point.x(), point.y(), point.z() + depth);
    }

    // Draw line back to the first point
    gs.drawTo3D(points.front().x(), points.front().y(), points.front().z() + depth);
}

void drawShape(GraphicsSystem &gs, const std::vector<Point3> &points)
{
    const double depth = 20;

    drawFace(gs, points, 0);
    drawFace(gs, points, depth);

    for(const auto& point : points) {
        gs.moveTo3D(point.x(), point.y(), point.z());
        gs.drawTo3D(point.x(), point.y(), point.z() + depth);
    }
}

void drawRecognizer(GraphicsSystem &gs)
{
    gs.initGraphics(1000, 1000, -200, -200, 200, 200);

    gs.defineCameraTransform
    (
        0.0, 0.0, 0.0,  // phi is definitely vertical on z 
        10, 5, 0,
        25
    );

    // Draw this once for front of left lag
    // - again at z = depth for back
    // Repeat with flipped x for right leg
    std::vector<Point3> left_leg{{
        {-75, 0, 0},
        {-25, 0, 0},
        {-45, 10, 0}, 
        {-45, 100, 0},
        {-75, 100, 0}
    }};

    std::vector<Point3> right_leg{{
        {75, 0, 0},
        {25, 0, 0},
        {45, 10, 0}, 
        {45, 100, 0},
        {75, 100, 0}
    }};

    std::vector<Point3> middle_bar_left {{
        {-75, 105, 0},
        {0, 105, 0},
        {0, 110, 0},
        {-75, 110, 0}
    }};

    std::vector<Point3> middle_bar_right {{
        {75, 105, 0},
        {0, 105, 0},
        {0, 110, 0},
        {75, 110, 0}
    }};

    std::vector<Point3> middle_low_left {{
        {-12, 104, 0},
        {0, 104, 0},
        {0, 99, 0},
        {-8, 99, 0}
    }};

    std::vector<Point3> middle_low_right {{
        {12, 104, 0},
        {0, 104, 0},
        {0, 99, 0},
        {8, 99, 0}
    }};

    std::vector<Point3> middle_high_left {{
        {-12, 114, 0},
        {0, 114, 0},
        {0, 117, 0},
        {-12, 117, 0}
    }};

    std::vector<Point3> middle_high_right {{
        {12, 114, 0},
        {0, 114, 0},
        {0, 117, 0},
        {12, 117, 0}
    }};

    std::vector<Point3> left_cube {{
        {-75, 117, 0},
        {-45, 117, 0},
        {-45, 137, 0},
        {-75, 137, 0}
    }};

    std::vector<Point3> right_cube {{
        {75, 117, 0},
        {45, 117, 0},
        {45, 137, 0},
        {75, 137, 0}
    }};

    std::vector<Point3> left_small_rect {{
        {-42, 124, 0},
        {-32, 124, 0},
        {-32, 128, 0},
        {-42, 128, 0}
    }};

    std::vector<Point3> right_small_rect {{
        {42, 124, 0},
        {32, 124, 0},
        {32, 128, 0},
        {42, 128, 0}
    }};

    std::vector<Point3> left_bracket {{
        {-80, 142, 0},
        {-42, 142, 0},
        {-20, 120, 0},
        {-3, 120, 0},
        {-3, 125, 0},
        {-10, 125, 0},
        {-25, 142, 0},
        {-3, 142, 0},
        {-3, 147, 0},
        {-80, 147, 0}
    }};

    std::vector<Point3> right_bracket {{
        {80, 142, 0},
        {42, 142, 0},
        {20, 120, 0},
        {3, 120, 0},
        {3, 125, 0},
        {10, 125, 0},
        {25, 142, 0},
        {3, 142, 0},
        {3, 147, 0},
        {80, 147, 0}
    }};

    std::vector<Point3> left_middle_rect {{
        {-7, 128, 0},
        {0, 128, 0},
        {0, 139, 0},
        {-20, 139, 0}
    }};

    std::vector<Point3> right_middle_rect {{
        {7, 128, 0},
        {0, 128, 0},
        {0, 139, 0},
        {20, 139, 0}
    }};

    std::vector<Point3> left_tri_top {{
        {-40, 152, 0},
        {0, 152, 0},
        {0, 155, 0},
        {-10, 155, 0},
        {-8, 170, 0}
    }};

    std::vector<Point3> right_tri_top {{
        {40, 152, 0},
        {0, 152, 0},
        {0, 155, 0},
        {10, 155, 0},
        {8, 170, 0}
    }};

    std::vector<Point3> left_head {{
        {-8, 158, 0},
        {0, 158, 0},
        {0, 175, 0},
        {-8, 175, 0},
        {-6, 170, 0}
    }};
    
    std::vector<Point3> right_head {{
        {8, 158, 0},
        {0, 158, 0},
        {0, 175, 0},
        {8, 175, 0},
        {6, 170, 0}
    }};
    
    std::vector<vector<Point3>> shapes{
        left_leg, right_leg, 
        middle_bar_left, middle_bar_right,
        middle_low_left, middle_low_right,
        middle_high_left, middle_high_right,
        left_cube, right_cube,
        left_small_rect, right_small_rect,
        left_bracket, right_bracket,
        left_middle_rect, right_middle_rect,
        left_tri_top, right_tri_top,
        left_head, right_head
    };

    for(const auto &shape : shapes) {
        drawShape(gs, shape);
    }

    gs.saveCanvas(SAVEPATH3D + "recognizer.pbm");
    gs.clearCanvas();
}

void drawBlockLetters(GraphicsSystem &gs)
{
    gs.initGraphics(1000, 1000, -200, -200, 200, 200);

    gs.defineCameraTransform
    (
        0.0, 0.0, 0.0,  
        10, 10, 0,
        25
    );

    std::vector<Point3> a{{
        {-75, 0, 0},
        {-70, 0, 0},
        {-66, 10, 0}, 
        {-62, 10, 0},
        {-58, 0, 0},
        {-53, 0, 0},
        {-60, 30, 0},
        {-70, 30, 0},
    }};

    std::vector<Point3> a_mid{{
        {-66, 12, 0},
        {-62, 12, 0},
        {-64, 26, 0},
    }};

    std::vector<Point3> l{{
        {-45, 0, 0},
        {-30, 0, 0},
        {-30, 5, 0},
        {-40, 5, 0},
        {-40, 30, 0},
        {-45, 30, 0},
    }};

    std::vector<Point3> e{{
        {-22, 0, 0},
        {-7, 0, 0},
        {-7, 6, 0},
        {-17, 6, 0},
        {-17, 12, 0},
        {-7, 12, 0},
        {-7, 18, 0},
        {-17, 18, 0},
        {-17, 24, 0},
        {-7, 24, 0},
        {-7, 30, 0},
        {-22, 30, 0},
    }};

    std::vector<Point3> x{{
        {1, 0, 0},
        {6, 0, 0},
        {8, 14, 0},
        {10, 0, 0},
        {15, 0, 0},
        {12, 15, 0},
        {15, 30, 0},
        {10, 30, 0},
        {7, 16, 0},
        {6, 30, 0},
        {1, 30, 0},
        {3, 15, 0}
    }};



    std::vector<vector<Point3>> letters{
        a, a_mid, l, e, x
    };

    for(const auto &letter : letters) {
        drawShape(gs, letter);
    }

    gs.saveCanvas(SAVEPATH3D + "letters.pbm");
    gs.clearCanvas();
}
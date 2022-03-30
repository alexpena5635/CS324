/* 
 * plotGraphics.h
 * Defines a plotting class on top of the graphics system
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */
#ifndef PLOT_GRAPHICS_H_
#define PLOT_GRAPHICS_H_

#include "graphics.h"

class PlotGS : public GraphicsSystem {
    public:
        void drawAxis(color color, Point2 origin, Point2 min,  Point2 max);
        void plotTest(Point2 origin);
        void plotEq1 (Point2 origin); // equation 1
        void plotEq2 (Point2 origin); // equation 2
        void plotEq3 (Point2 origin); // equation 3
};

#endif
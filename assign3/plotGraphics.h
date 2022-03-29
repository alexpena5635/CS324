#ifndef PLOT_GRAPHICS_H_
#define PLOT_GRAPHICS_H_

#include "graphics.h"

class PlotGS : public GraphicsSystem {
    public:
        void drawAxis(color color, Point2 origin, Point2 min,  Point2 max);
        void plotTest(Point2 origin);
        void plotEq1 (Point2 origin); // equation 1
        void plotEq2 (Point2 origin); // equation 2
        void plotEq3 (Point2 origin); // equation 2
};

#endif
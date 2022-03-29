#ifndef PLOT_GRAPHICS_H_
#define PLOT_GRAPHICS_H_

#include "graphics.h"

class PlotGS : public GraphicsSystem {
    void drawAxis(color color, Point2 origin, Point2 min,  Point2 max);
    void plotTest(Point2 origin);
    void plotEq1 (Point2 origin); // equation 1
    void plotEq2 (Point2 origin); // equation 2
    void plotEq3 (Point2 origin); // equation 2
};

double eq1(double x) { return (3.0 * exp(x * -0.33) * sin(x*3)); }
double eq2(double x)
{
	double num = 3*(x*x) - 12*x - 15;
	double den = (x*x) - 3*x -10;
	return num/den;
}
double eq3(double x, double mult, double b)
{
	double expre = (x*x)*( (b*x) + 0.5 );
	return mult * pow(expre, 0.5);
}

#endif
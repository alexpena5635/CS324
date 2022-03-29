


#define _USE_MATH_DEFINES

#include <cmath>

#include "plotGraphics.h"

// Draw an x and y axis
void PlotGS::drawAxis(color draw_color, Point2 origin, Point2 min,  Point2 max) {
	moveTo2D(min.x(), origin.y());
	drawTo2D(draw_color, max.x(), origin.y());
	moveTo2D(origin.x(), min.y());
    drawTo2D(draw_color, origin.x(), max.y());
}

// Test the code from sample plot
void PlotGS::plotTest(Point2 origin)
{
	Point2 min(origin.x() - 2.5, origin.y());
	Point2 max(origin.x() + 2.5, origin.y() + 7.5);

	drawAxis(colors::BLACK, origin, min, max);

	double x = -2.0;
	double xInc = 4.0 / 100.0;
	moveTo2D(x, exp(-x) + origin.y());
	for(int i = 0; i <= 100; i++)
	{
		x += xInc;
		drawTo2D(colors::BLUE, x, exp(-x) + origin.y());
		moveTo2D(x, exp(-x) + origin.y());
	}
	
}

// Draw the first equation
void PlotGS::plotEq1(Point2 origin)
{
	Point2 min(0, -3 + origin.y());
	Point2 max(10, 3 + origin.y());

	drawAxis(colors::BLACK, origin, min, max);

	double x = min.x();
	double xInc = (M_PI/180);
	double y = eq1(x);
	moveTo2D(x, y + origin.y()); // y = 3.0e^(-0.33(x))sin(3x)    0 <= x <= 3pi
	for(x = 0; x <= 3*(M_PI); x += xInc)
	{
		drawTo2D(colors::BLUE, x, eq1(x) + origin.y());
		moveTo2D(x, eq1(x) + origin.y());
	}
}

// Draw the second equation
void PlotGS::plotEq2(Point2 origin)
{
	Point2 min(-10, -30);
	Point2 max(10, 30);

	drawAxis(colors::BLACK, origin, min, max);

	double x = -6;
	double xInc = 1.0 / 1000.0;
	double y = eq2(x);
	moveTo2D(x, y);
	for(x = -6.0; x <= 6.0; x += xInc)
	{
		if(fabs(fabs(x) - 2.0) < 0.000001)
		{
			x += 0.05;
			moveTo2D(x, eq2(x));
		}
		drawTo2D(colors::BLUE, x, eq2(x));
		moveTo2D(x, eq2(x));
	}
	
}

// Draw the third equation
void PlotGS::plotEq3(Point2 origin)
{
	Point2 min(-10, -10);
	Point2 max(10, 10);

	drawAxis(colors::BLACK, origin, min, max);

	double x;
	double xInc = 1.0 / 1000.0;

	// const double b = 0.5;
	// x = -1;

	// const double b = 1;
	// x = -0.5;

	const double b = 2;
	x = -0.25;

	double y = eq3(x, 1, b);
	moveTo2D(x, y);
	for(x; x <= 50.0; x += xInc)
	{
		drawTo2D(colors::BLUE, x, eq3(x, 1, b));
		moveTo2D(x, eq3(x, 1, b));
	}

	x = -0.25;
	y = eq3(x, -1, b);
	moveTo2D(x, y);
	for(x; x < 50.0; x += xInc)
	{
		drawTo2D(colors::BLUE, x, eq3(x, -1, b));
		moveTo2D(x, eq3(x, -1, b));
	}
	
	
}
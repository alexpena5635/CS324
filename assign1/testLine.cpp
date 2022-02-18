/* testLine.cpp

CS Linux
g++ -std=c++1y testLine.cpp canvas.cpp 

https://stackoverflow.com/questions/31965413/compile-c14-code-with-g

macOS:
c++ -std=c++14 testLine.cpp canvas.cpp 


 */


/*
	- Functions to draw equation 1 and 2 are defined here
	- It got hectic towards the end so this file is a mess in terms of what it's calling currently
*/

#include <iostream>
#include <cmath>

#include "graphics.h"

double eq1(double x) { return (3.0 * exp(x * -0.33) * sin(x*3)); }
double eq2(double x)
{
	double num = 3*(x*x) - 12*x - 15;
	double den = (x*x) - 3*x -10;
	return num/den;
}

void drawAxis(Canvas& pixmap, color color, point2D origin, point2D min,  point2D max);
void plotTest(Canvas& pixmap, point2D origin, point2D min, point2D max);
void plotEq1(Canvas& pixmap, point2D origin); // equation 1
void plotEq2(Canvas& pixmap, point2D origin); // equation 2

int main()
{	
	// double windowMin[DIM] = {-10.0, -1.0} , windowMax[DIM] = {10.0, 8.0};
	// double viewMin[DIM] = {-1.0, -1.0} , viewMax[DIM] = {1.0, 1.0};
	point2D w_min(-10.0, -1.0) , w_max(10.0, 8.0);
	point2D v_min(-1.0, -1.0) , v_max(1.0, 1.0);

	const int pixmapSize = 1000;
	
	std::shared_ptr<Canvas> pixmap = InitGraphics(pixmapSize, w_min, w_max, v_min, v_max);
	

	// point2D w_point(-5.0, 6.0, 1.0);
	// point2D v_point(0.0, 0.0, 1.0);
	// std::cout << "Before:\n" << w_point << std::endl;

	// WindowToViewport(w_point, v_point);

	// std::cout << "After:\n" << v_point << std::endl;
	// return 0;


	point2D origin( 
		((w_max.x+w_min.x)/2.0),   // I have messed up these formulas multiple times
		((w_max.y+w_min.y)/2.0) 
	);
	// double min[DIM] = {-3.5, 1.0};
	// double max[DIM] = {3.5, 7.5};

	// plotTest(*pixmap, origin, min, max);
	//plotEq1(*pixmap, origin);
	//plotEq2(*pixmap, origin);

	// v_min.set(-5.0, -5.0);
	// v_max.set(5.0, 5.0);

	std::cout << "Origin: \n" << origin << std::endl;

	MoveTo2D(w_min.x, origin.y);
	DrawTo2D(*pixmap, colors::BLACK, w_max.x, origin.y);
	MoveTo2D(origin.x, w_min.y);
    DrawTo2D(*pixmap, colors::BLACK, origin.x, w_max.y);
	

	std::string filename2( "mytest.pbm" );
	SaveCanvasToFile( *pixmap, filename2 );
    return 0;
}

// Draw an x and y axis
void drawAxis(Canvas& pixmap, color color, point2D origin, point2D min,  point2D max)
{
	MoveTo2D(min.x, origin.y);
	DrawTo2D(pixmap, color, max.x, origin.y);
	MoveTo2D(origin.x, min.y);
    DrawTo2D(pixmap, color, origin.x, max.y);
}

// Test the code from sample plot
void plotTest(Canvas& pixmap, point2D origin, point2D min,  point2D max)
{
	drawAxis(pixmap, colors::BLACK, origin, min, max);

	double x = min.x;
	double xInc = 4.0 / 100.0;
	MoveTo2D(x, exp(-x) + origin.y);
	for(int i = 0; i <= 200; i++)
	{
		x += xInc;
		DrawTo2D(pixmap, colors::BLUE, x, exp(-x) + origin.y);
		MoveTo2D(x, exp(-x) + origin.y);
	}
	
}

// Draw the first equation
void plotEq1(Canvas& pixmap, point2D origin)
{
	point2D min(0, -3 + origin.y);
	point2D max(10, 3 + origin.y);

	drawAxis(pixmap, colors::BLACK, origin, min, max);

	double x = min.x;
	double xInc = (M_PI/180);
	double y = eq1(x);
	MoveTo2D(x, y + origin.y); // y = 3.0e^(-0.33(x))sin(3x)    0 <= x <= 3pi
	for(x = 0; x <= 3*(M_PI); x += xInc)
	{
		DrawTo2D(pixmap, colors::BLUE, x, eq1(x) + origin.y);
		MoveTo2D(x, eq1(x) + origin.y);
	}
}

// Draw the second equation
void plotEq2(Canvas& pixmap, point2D origin)
{
	point2D min(-15, -15);
	point2D max(15, 15);

	drawAxis(pixmap, colors::BLACK, origin, min, max);

	double x = -6;
	double xInc = 1.0 / 1000.0;
	double y = eq2(x);
	MoveTo2D(x, y);
	for(x = -6.0; x <= 6.0; x += xInc)
	{
		if(fabs(fabs(x) - 2.0) < 0.5)
		{
			x += 0.05;
			MoveTo2D(x, eq2(x));
		}
		DrawTo2D(pixmap, colors::BLUE, x, eq2(x));
		MoveTo2D(x, eq2(x));
	}
	
}
/* 
 * plot2d.cpp 
 * 
 * (Derived from starter code from lecture notes)
 * Tests and uses the graphics system for plotting
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 * 
 * CS Linux
 * g++ -std=c++1y testLine.cpp canvas.cpp 
 * https://stackoverflow.com/questions/31965413/compile-c14-code-with-g
 */

#include <iostream>
#include <cmath>

#include "plotGraphics.h"

int main()
{	
	PlotGS gs;
	gs.initGraphics(1000, 1000);
	Point2 origin(0, 0);

	gs.changeViewport(-1, -1, 0, 0);
	gs.plotTest(origin);
	gs.saveCanvas("plotTest.pbm");
	gs.clearCanvas();

	gs.changeWindow(-2, -4, 12, 6);
	gs.changeViewport(-1, -1, 1, 1);
	gs.plotEq1(origin);
	gs.saveCanvas("plot1.pbm");
	gs.clearCanvas();

	gs.changeWindow(-6, -30, 6, 30);
	gs.changeViewport(-1, -1, 1, 1);
	gs.plotEq2(origin);
	gs.saveCanvas("plot2.pbm");
	gs.clearCanvas();

	gs.changeWindow(-5, -10, 10, 10);
	gs.changeViewport(-1, -1, 1, 1);
	gs.plotEq3(origin);
	gs.saveCanvas("plot3.pbm");

    return 0;
}

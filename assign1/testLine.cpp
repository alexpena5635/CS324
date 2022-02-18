/* testLine.cpp

CS Linux
g++ -std=c++1y testLine.cpp canvas.cpp 

https://stackoverflow.com/questions/31965413/compile-c14-code-with-g

macOS:
c++ -std=c++14 testLine.cpp canvas.cpp 


 */

#include <iostream>
#include <cmath>

#include "graphics.h"

void drawAxis(Canvas& pixmap, color color, double origin[DIM], double min[DIM], double max[DIM]);
void plotTest(Canvas& pixmap, color color, double origin[DIM], double min[DIM], double max[DIM]);

int main()
{	
	double windowMin[] = {-13.0, -1.0} , windowMax[] = {13.0, 8.0};
	double viewMin[] = {-1.0, -1.0} , viewMax[] = {1.0, 1.0}; //works!

	int pixmapSize = 1000;
	
	std::shared_ptr<Canvas> pixmap = InitGraphics(pixmapSize, windowMin, windowMax, viewMin, viewMax);
	
	double origin[DIM] = {0.0, 2.0};
	double min[DIM] = {-3.5, 1.0};
	double max[DIM] = {3.5, 7.5};

	//plotTest(*pixmap, colors::BLACK, origin, min, max);
	

	std::string filename2( "mytest.pbm" );
	SaveCanvasToFile( *pixmap, filename2 );
    return 0;
}

void drawAxis(Canvas& pixmap, color color, double origin[DIM], double min[DIM], double max[DIM])
{
	MoveTo2D(min[0], origin[1]);
	DrawTo2D(pixmap, color, max[0], origin[1]);
	MoveTo2D(origin[0], min[1]);
    DrawTo2D(pixmap, color, origin[0], max[1]);
}

void plotTest(Canvas& pixmap, color color, double origin[DIM], double min[DIM], double max[DIM])
{
	drawAxis(pixmap, colors::BLACK, origin, min, max);

	double x = min[0];
	double xInc = 4.0 / 100.0;
	MoveTo2D(x, exp(-x) + origin[1]);
	for(int i = 0; i <= 200; i++)
	{
		x += xInc;
		DrawTo2D(pixmap, colors::BLUE, x, exp(-x) + origin[1]);
		MoveTo2D(x, exp(-x) + origin[1]);
	}
	
}

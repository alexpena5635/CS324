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


int main()
{	
	double windowMin[] = {-13.0, -1.0} , windowMax[] = {13.0, 8.0};
	double viewMin[] = {-1.0, -1.0} , viewMax[] = {1.0, 1.0}; //works!

	int pixmapSize = 1000;
	
	std::shared_ptr<Canvas> pixmap = InitGraphics(pixmapSize, windowMin, windowMax, viewMin, viewMax);
	
	MoveTo2D(-3.5, 1.0);
	DrawTo2D(*pixmap, colors::BLACK, 3.5, 1.0);
	MoveTo2D(0.0, -1.0);
    DrawTo2D(*pixmap, colors::BLACK, 0.0, 7.5);
	
	
	double x = -2.0;
	double xInc = 4.0 / 100.0;
	MoveTo2D(x, exp(-x));
	for(int i = 0; i <= 100; i++)
	{
		x += xInc;
		DrawTo2D(*pixmap, colors::BLUE, x, exp(-x));
		MoveTo2D(x, exp(-x));
	}
	

	std::string filename2( "mytest.pbm" );
	SaveCanvasToFile( *pixmap, filename2 );
    return 0;
}

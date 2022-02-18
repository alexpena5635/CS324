/* testLine.cpp

CS Linux
g++ -std=c++1y testLine.cpp canvas.cpp 

https://stackoverflow.com/questions/31965413/compile-c14-code-with-g

macOS:
c++ -std=c++14 testLine.cpp canvas.cpp 


 */

#include <iostream>

#include "graphics.h"


int main()
{
	//double windowMin[] = {0.0, 0.0} , windowMax[] = {8.0, 8.0}; //works!
	//double viewMin[] = {-1.0, -1.0} , viewMax[] = {1.0, 1.0}; //works!

	// having the coords closer together causes canvas nums to be smaller?
	double windowMin[] = {-1.0, -1.0} , windowMax[] = {8.0, 8.0};
	// moving the viewport around allows us to see more of the picture kidna
	double viewMin[] = {-10.0, -1.0} , viewMax[] = {1.0, 1.0}; //works!
	

	int pixmapSize = 1000;
	
	std::shared_ptr<Canvas> pixmap = InitGraphics(pixmapSize, windowMin, windowMax, viewMin, viewMax);
	
	//Works!
	MoveTo2D(-0.5, -0.5);
	DrawTo2D(*pixmap, colors::BLUE, 6.5, 2.5);
	MoveTo2D(4.5, 0.5);
	DrawTo2D(*pixmap, colors::BLUE, 4.5, 4.5);	

	std::string filename2( "mytest.pbm" );
	SaveCanvasToFile( *pixmap, filename2 );
    return 0;
}


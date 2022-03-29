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
	GraphicsSystem gs;
	gs.initGraphics(1000, 1000);
	gs.changeWindow(-10, -10, 10, 10);
	gs.changeViewport(-1, -1, 1, 1);

	Point2 origin(0, 0);
	gs.moveTo2D(5, 5);
	gs.drawTo2D(colors::BLUE, -10, -10);

	gs.saveCanvas("test.pbm");

	// filename = "plotTest.pbm";
	// ChangeViewport(-1, -1, 0, 0);
	// plotTest(*pixmap, origin);
	// SaveCanvasToFile( *pixmap, filename);
	// pixmap->Clear();

	// filename = "plot1.pbm";
	// ChangeWindow(-2, -4, 12, 6);
	// ChangeViewport(-1, -1, 1, 1);
	// plotEq1(*pixmap, origin);
	// SaveCanvasToFile( *pixmap, filename);
	// pixmap->Clear();

	// filename = "plot2.pbm";
	// ChangeWindow(-6, -30, 6, 30);
	// ChangeViewport(-1, -1, 1, 1);
	// plotEq2(*pixmap, origin);
	// SaveCanvasToFile( *pixmap, filename);
	// pixmap->Clear();

	// filename = "plot3.pbm";
	// ChangeWindow(-5, -10, 10, 10);
	// ChangeViewport(-1, -1, 1, 1);
	// plotEq3(*pixmap, origin);
	// SaveCanvasToFile( *pixmap, filename);

	// std::string filename( "mytest.pbm" );
	// SaveCanvasToFile( *pixmap, filename);
    return 0;
}

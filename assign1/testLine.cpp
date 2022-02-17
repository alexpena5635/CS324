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
    constexpr auto size = 1000;
    
    Canvas gc( size, size, colors::WHITE );  // Graphics canvas
    //Canvas gc( size, size, colors::BLACK );  // Graphics canvas
    //Canvas gc( size, size, colors::BLUE );  // Graphics canvas
	
    for( auto y = 0 ; y < size ; y += size/8 ) {
        for( auto x = 0 ; x < size ; x += size/8 )
        {
            Line( gc, x, y, x+40, y+40, colors::RED );

            Line( gc, x, y+33, x, y, colors::BLUE );
            
            //std::cout << "x: " << x << "  ";
            //std::cout << "y: " << y << std::endl;
        }
    }
    
    std::string fileName( "testLine.pbm" );
    SaveCanvasToFile( gc, fileName );

	double windowMin[] = {-3.0, -1.0} , windowMax[] = {3.0, 8.0};
	double viewMin[] = {-1.0, -1.0} , viewMax[] = {1.0, 1.0};
	int pixmapSize = 1000;
	
	std::shared_ptr<Canvas> pixmap = InitGraphics(pixmapSize, windowMin, windowMax, viewMin, viewMax);
	
	MoveTo2D(-2.5, 0.0);
	DrawTo2D(*pixmap, colors::BLUE, 2.5, 0.0);
	MoveTo2D(0.0, -0.5);
	DrawTo2D(*pixmap, colors::BLUE, 0.0, 7.5);	
		


	std::string filename2( "mytest.pbm" );
	SaveCanvasToFile( *pixmap, filename2 );
    return 0;
}


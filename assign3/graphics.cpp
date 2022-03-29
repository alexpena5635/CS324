/*
*   graphics.cpp
*
*   Alex Peña
*   CS324 Assignment 3
*
*/


#include "graphics.h"
#include "canvas.h"
#include "matrix.h"


// InitGraphics()
// - sets the window, viewport, and cavas up
// - return the canvas
// std::shared_ptr<Canvas> InitGraphics(const int w, const int h, const point2D w_min_l, const point2D w_max_l, const point2D v_min_l, const point2D v_max_l)
void GraphicsSystem::initGraphics(	
										const int w, const int h, 
										const double wxmin, const double wymin, const double wxmax, const double wymax, 
										const double vxmin, const double vymin, const double vxmax, const double vymax 
									)
{
	changeWindow(wxmin, wymin, wxmax, wymax);
	changeViewport(vxmin, vymin, vxmax, vymax);

	pixmap = std::make_shared<Canvas>(w, h, colors::WHITE);
}


void GraphicsSystem::changeViewport(double xmin, double ymin, double xmax, double ymax)
{
	setViewport(xmin, ymin, xmax, ymax);

	scale_x = (xmax - xmin) / (w_max.x() - w_min.x());
	scale_y = (ymax - ymin) / (w_max.y() - w_min.y());
}


void GraphicsSystem::changeWindow(double xmin, double ymin, double xmax, double ymax)
{
	setWindow(xmin, ymin, xmax, ymax);

	scale_x = (v_max.x() - v_min.x()) / (xmax - xmin);
	scale_y	= (v_max.y() - v_min.y()) / (ymax - ymin);
}

// Convert from window to viewport coords
// - Need to multiply all of the transformation matricies together first, then multiply against point
void GraphicsSystem::windowToViewport(const Point2& in_v, Point2& out_v)
{
	// vx -> xvmin + (xw-xwmin) * Sx
	// vy -> yvmin + (yw-ywmin) * Sy

	// Multiply 2D point vector by 3D translation matrix of the min viewport point
	Matrix t1(3, translation, v_min.x(), v_min.y());
	Matrix s(3, scaling, 0, 0, scale_x, scale_y);
	Matrix t2(3, translation, -w_min.x(), -w_min.y());

	// std::cout << "Transform 1: \n";
	// t1.print();
	// std::cout << "Scaling: \n";
	// s.print();
	// std::cout << "Transform 2: \n";
	// t2.print();

	Matrix res1 = t1*s;
	// std::cout << "PreRes: \n";
	// res1.print();

	Matrix result = t1*s*t2;

	// std::cout << "Result: \n";
	// result.print(); 

	out_v = result * in_v;

	// std::cout << "Window Point: " << in_v << std::endl;
	// std::cout << "Viewport Point: " << out_v << std::endl;

	// The point is now translated into viewport
	t1.deallocate();
	t2.deallocate();
	s.deallocate();
}

// Convert from the viewport to the pixmap
void GraphicsSystem::viewportToPixmap(const Point2& in_v, Point2& out_v)
{
	double canvasMinX = (pixmap->Width()/2) * (1 + v_min.x());
	double canvasMinY = (pixmap->Height()/2) * (1 + v_min.y());
	double canvasMaxX = (pixmap->Width()/2) * (1 + v_max.x());
	double canvasMaxY = (pixmap->Height()/2) * (1 + v_max.y());

	double scaleX = (canvasMaxX-canvasMinX) / (v_max.x()-v_min.x());
    double scaleY = (canvasMaxY-canvasMinY) / (v_max.y()-v_min.y());

	// Multiply 2D point vector by 3D translation matrix of the min viewport point
	Matrix t1(3, translation, canvasMinX, canvasMinY); //smallest spot on bitmap is bitmapMinX, bitmapMInY	
	Matrix s(3, scaling, 0, 0, scaleX, scaleY);
	Matrix t2(3, translation, -v_min.x(), -v_min.y());

	// std::cout << "************************ PIXMAP **************************" << std::endl;
	// std::cout << "Transform 1: \n";
	// t1.print();
	// std::cout << "Scaling: \n";
	// s.print();
	// std::cout << "Transform 2: \n";
	// t2.print();

	Matrix res1 = t1*s;
	// std::cout << "PreRes: \n";
	// res1.print();

	Matrix result = t1*s*t2;

	// std::cout << "Result: \n";
	// result.print(); 

	out_v = result*in_v;

	// The point is now translated into canvas coords
	t1.deallocate();
	t2.deallocate();
	s.deallocate();

	// Filp the y-axis 
	out_v.set(
		out_v.x(), 
		pixmap->Height() - out_v.y(), 
		out_v.h()
	);

	// std::cout << "Viewport Point: " << in_v << std::endl;
	// std::cout << "Pixmap Point: " << out_v << std::endl;
}

// Draw a line on the canvas
void GraphicsSystem::drawTo2D(color draw_color, double x, double y)
{
	// - Translate world coord to viewport (WindowToViewport)
	// - Translate viewport coords to canvas/pixmap coordinates	
	Point2 window_curr(current_pos.x(), current_pos.y(), current_pos.h()), window_goal(x, y, 1);
	Point2 new_curr, new_goal;

	// window_curr.setHomog(true);
	// window_goal.setHomog(true);
	// new_curr.setHomog(true);
	// new_goal.setHomog(true);

	//std::cout << "##### Window points #####\n" << window_curr << window_goal;

	// Translate the start and end coodinates from world space to viewport
	windowToViewport(window_curr, new_curr); 
	windowToViewport(window_goal, new_goal); 

	//std::cout << "##### Viewport points #####\n" << new_curr << new_goal;

	// Viewport to canvas space/coords
	viewportToPixmap(new_curr, new_curr); 
	viewportToPixmap(new_goal, new_goal);

	//std::cout << "##### Pixmap points #####\n" << new_curr << new_goal;

	// window_curr.setHomog(false);
	// window_goal.setHomog(false);
	// new_curr.setHomog(false);
	// new_goal.setHomog(false);
	
	// Scales to match vp and window, like a fullscreen drawing
	Line(*pixmap, new_curr.x(), new_curr.y(), new_goal.x(), new_goal.y(), draw_color);	
}

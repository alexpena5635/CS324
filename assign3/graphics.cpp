/* 
 * grahpics.cpp
 * Defines a graphics class, and related methods
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */


#include "graphics.h"
#include "canvas.h"
#include "matrix.h"


// Initializes the window, viewport, and canvas
void GraphicsSystem::initGraphics(	const int w, const int h, 
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
Point2 GraphicsSystem::windowToViewport(const Point2& in_v)
{
	// vx = xvmin + (xw-xwmin) * Sx
	// vy = yvmin + (yw-ywmin) * Sy

	/*
	 * t1
	 * - 2D translation matrix
	 * - Moves (x,y) to the relative point in viewport coords
	 * s
	 * - 2D scaling matrix
	 * - Scales (x,y) from world coords to viewport coords
	 * t2
	 * - 2D translation matrix
	 * - Moves (x,y) from world point to world origin
	 */

	Matrix t1(3, translation, v_min.x(), v_min.y());
	Matrix s(3, scaling, 0, 0, scale_x, scale_y);
	Matrix t2(3, translation, -w_min.x(), -w_min.y());

	// std::cout << "Transform 1: \n" << t1
	// 	<< "Scaling: \n" 		<< s
	// 	<< "Transform 2: \n" 	<< t2 << std::endl;
	
	Matrix res = t1*s;
	// std::cout << "PreRes: \n" << res << std::endl;
	res *= t2;
	// std::cout << "Result: " << res << std::endl;

	return res*in_v;
}

// Convert from viewport to the pixmap coords
Point2 GraphicsSystem::viewportToPixmap(const Point2& in_v)
{
	double canvasMinX = (pixmap->Width()/2) * (1 + v_min.x());
	double canvasMinY = (pixmap->Height()/2) * (1 + v_min.y());
	double canvasMaxX = (pixmap->Width()/2) * (1 + v_max.x());
	double canvasMaxY = (pixmap->Height()/2) * (1 + v_max.y());

	double scaleX = (canvasMaxX-canvasMinX) / (v_max.x()-v_min.x());
    double scaleY = (canvasMaxY-canvasMinY) / (v_max.y()-v_min.y());

	/*
	 * t1
	 * - 2D translation matrix
	 * - Moves (x,y) to the relative point in pixmap coords
	 * s
	 * - 2D scaling matrix
	 * - Scales (x,y) from viewport to pixmap coords
	 * t2
	 * - 2D translation matrix
	 * - Moves (x,y) from viewport point to viewport origin
	 */
	Matrix t1(3, translation, canvasMinX, canvasMinY);
	Matrix s(3, scaling, 0, 0, scaleX, scaleY);
	Matrix t2(3, translation, -v_min.x(), -v_min.y());

	//  std::cout << "**** PIXMAP ****" << std::endl
	// 	<< "Transform 1: \n" 	<< t1
	// 	<< "Scaling: \n" 		<< s
	// 	<< "Transform 2: \n" 	<< t2 << std::endl;
	

	Matrix res = t1*s;
	// std::cout << "PreRes: \n" << res << std::endl;
	res *= t2;
	// std::cout << "Result: \n" << res << std::endl;

	// flip y-axis (do we need to subtract 1 from this bc it's not indexed?)
	Point2 p = res*in_v;
	p[1] = pixmap->Height() - p.y(); 

	return p;
}

// Draw a line on the canvas
void GraphicsSystem::drawTo2D(color draw_color, double x, double y)
{
	// - Translate world coord to viewport (WindowToViewport)
	// - Translate viewport coords to canvas/pixmap coordinates	
	Point2 window_curr(current_pos.x(), current_pos.y(), current_pos.h());
	Point2 window_goal(x, y); // , 1); // Our new system sets h=1 automatically

	// std::cout << "##### Window points #####\n" 
	// 	<< window_curr << '\n' << window_goal << std::endl;

	// Translate the start and end coodinates from world space to viewport
	Point2 viewport_curr = windowToViewport(window_curr); 
	Point2 viewport_goal = windowToViewport(window_goal); 

	// std::cout << "##### Viewport points #####\n" 
	// 	<< viewport_curr << '\n' << viewport_goal << std::endl;

	// Viewport to canvas space/coords
	Point2 pixmap_curr = viewportToPixmap(viewport_curr); 
	Point2 pixmap_goal = viewportToPixmap(viewport_goal);

	// std::cout << "##### Pixmap points #####\n" \
	// 	<< pixmap_curr << '\n' << pixmap_goal << std::endl;

	Line( *pixmap, pixmap_curr.x(), pixmap_curr.y(), pixmap_goal.x(), 
		pixmap_goal.y(), draw_color);	
}

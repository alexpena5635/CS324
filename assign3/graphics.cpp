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

		
/****** 
 * 
 * 2D Related
 * 
 * ******/

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

	// std::cout << "##### Pixmap points #####\n"
	// 	<< pixmap_curr << '\n' << pixmap_goal << std::endl;


	double f = pixmap->Height();
	double e = 0.0000000001;
	if (
		range(pixmap_curr.x(), e, f)
		&& range(pixmap_curr.y(), e, f)
		&& range(pixmap_goal.x(), e, f)
		&& range(pixmap_goal.y(), e, f)
	)
	{
		Line( *pixmap, pixmap_curr.x(), pixmap_curr.y(), pixmap_goal.x(), 
			pixmap_goal.y(), draw_color);	
	}
}

/****** 
 * 
 * 3D Related
 * 
 * ******/

/*
 * (fx, fy, fz) - Focal point; 
 * (theta, phi, alpha) - Orientation; 
 * (r) - Distance eye to origin
 */
void GraphicsSystem::defineCameraTransform(double fx, double fy, double fz, 
	double theta, double phi, double alpha, double r)
{
    defineElementaryTransform(*camera, X_TRANS, -fx);
	// std::cout << "x trans\n" << *camera << std::endl;

    buildElementaryTransform(*camera, Y_TRANS, -fy);
	// std::cout << "y trans\n" << *camera << std::endl;

    buildElementaryTransform(*camera, Z_TRANS, -fz);
	// std::cout << "z trans\n" << *camera << std::endl;

    buildElementaryTransform(*camera, Y_ROT, -theta);
    // std::cout << "y rot\n" << *camera << std::endl;

	buildElementaryTransform(*camera, X_ROT, phi);
    // std::cout << "x rot\n" << *camera << std::endl;

	buildElementaryTransform(*camera, Z_ROT, -alpha);
	// std::cout << "z rot\n" << *camera << std::endl;

    buildElementaryTransform(*camera, PERSPECTIVE, r);
	// std::cout << "perspective\n" << *camera << std::endl;

	resetActiveTransform(); // intialize active transform
}

void GraphicsSystem::defineElementaryTransform(Matrix &m, transformCode tfCode, double tfValue)
{
    // m.setIdentityMatrix();
	double tfRadians = tfValue * (M_PI/180); // has to be input as radians!
    switch(tfCode)
    {
        case X_TRANS:
            m(3, 0) = tfValue;
            break;
        case Y_TRANS:
            m(3, 1) = tfValue;
            break;
        case Z_TRANS:
            m(3, 2) = tfValue;
            break;
        case X_ROT:
            m(1, 1) = cos(tfRadians);
            m(1, 2) = sin(tfRadians);
            m(2, 1) = -sin(tfRadians);
            m(2, 2) = cos(tfRadians);
            break;
        case Y_ROT:
			m(0, 0) = cos(tfRadians);
            m(0, 2) = sin(tfRadians);  // -sin(tfValue);
            m(2, 0) = -sin(tfRadians); // sin(tfValue);
            m(2, 2) = cos(tfRadians);
            break;
        case Z_ROT:
            m(0, 0) = cos(tfRadians);
            m(0, 1) = sin(tfRadians);
            m(1, 0) = -sin(tfRadians);
            m(1, 1) = cos(tfRadians);
            break;
        case PERSPECTIVE:
            m(2, 3) = -(1/tfValue);
            break;
		case X_SCALE:
			m(0,0) = tfValue;
			break;
		case Y_SCALE:
			m(1,1) = tfValue;
			break;
		case Z_SCALE:
			m(2,2) = tfValue;
			break;
        default:
            break;
    };
}

void GraphicsSystem::buildElementaryTransform(Matrix &tfM, transformCode tfCode, double tfValue)
{
    Matrix tmp(4, identity);
    defineElementaryTransform(tmp, tfCode, tfValue);

	/* 
	 * The BuildElementaryTransform routine creates a new transform 
	 * by premultiplying a transform by a new transform 
	 * (as specified by the arguments to the routine).
	 * 
	 * Pre multiply a transform (ex. A), by a new transform (ex.B)
	 * pre: BA
	 * 
	 * tfM -> A, tmp ->B
	 * 
	 * So we need: tfM = tmp * tfM!!!!!!!!!!!!!!!!!!!
	 */

    // tfM =  tfM * tmp; // This is post-multiplying
	tfM = tmp * tfM; // pre multiply!
	
}

void GraphicsSystem::moveTo3D(double x, double y, double z)
{
	// std::cout << "before move:\n" << x << ' ' << y << ' ' << z << ' ';
 	Point3 curr = applyTransform(x, y, z);
    moveTo2D(curr.x(), curr.y());
	// std::cout << "after move:\n" << curr;
}

void GraphicsSystem::drawTo3D(double x, double y, double z, color draw_color/*=colors::BLACK*/)
{
	// std::cout << "before draw:\n" << x << ' ' << y << ' ' << z << ' ';
	Point3 goal = applyTransform(x, y, z);
	// std::cout << "after apply transform\n";
	drawTo2D(draw_color, goal.x(), goal.y());
	// std::cout << "after draw:\n" << goal;
}

Point3 GraphicsSystem::applyTransform(double x, double y, double z)
{
    Point3 p(x, y, z, 1);
	return p * (*active_transform);
}

void GraphicsSystem::buildActiveTransform(transformCode tfCode, double tfValue)
{
	/*
	* Create a new matrix of type tfCode
	* new matrix 'B', active transform 'a'
	* do BA, store as new active_transform
	*/
	buildElementaryTransform(*active_transform, tfCode, tfValue);
}

void GraphicsSystem::resetActiveTransform()
{
	// Set active transform back to just the camera transform
	active_transform = std::make_shared<Matrix>(
		(Matrix(4, identity) * (*camera))
	);
}
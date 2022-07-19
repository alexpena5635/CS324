/* 
 * grahpics.h
 * Declares a graphics class, and related methods
 * 
 * Alex Peña
 * CS 324
 * Assignment 3 - 3D
 * 03/29/2022
 */

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <memory>
#include <string>

#include "canvas.h"
#include "vec2.h"
#include "vec3.h"
#include "matrix.h"

const std::string SAVEPATH3D = "./demo_output/3D/";
const std::string SAVEPATH2D = "./demo_output/2D/";

enum transformCode {
	X_TRANS, 	Y_TRANS, 	Z_TRANS, 
	X_ROT, 		Y_ROT, 		Z_ROT, 
	PERSPECTIVE,
	X_SCALE, 	Y_SCALE, 	Z_SCALE
	};

class GraphicsSystem {
	protected:
		std::shared_ptr<Canvas> pixmap;
		Point2 w_min, w_max, v_min, v_max;
		double scale_x, scale_y;
		Point2 current_pos;

		std::shared_ptr<Matrix> camera, active_transform;

		// Pass in a matrix to intialize, the type of transform, and the value 
		void defineElementaryTransform(Matrix &m, transformCode tfCode, double tfValue);

		// Pass in a matrix to premultiply, the type of transform, and the value 
		void buildElementaryTransform(Matrix &tfM, transformCode tfCode, double tfValue);

		// Applies active transform (psuedo-stack) against x,y,z point 
		Point3 applyTransform(double x, double y, double z);

	public:
		GraphicsSystem() {	// Modification for 3d
			camera	= std::make_shared<Matrix>(4, identity); // hardcoded for 3d, make (size()) if want a 2d camera too?
			// active_transform  = std::make_shared<Matrix>(4, identity);
		}
		GraphicsSystem(std::shared_ptr<Canvas> c) : pixmap(c) {}

		void saveCanvas(std::string filename) { SaveCanvasToPBM(*pixmap, filename); }
		void clearCanvas() {pixmap->Clear();}
		
		/****** 
		 * 
		 * 2D Related
		 * 
		 * ******/
		
		void initGraphics(	const int w, const int h, 
			const double wxmin = -10, const double wymin = -10, 
			const double wxmax = 10, const double wymax = 10, 
			const double vxmin = -1, const double vymin = -1, 
			const double vxmax = 1, const double vymax = 1
		);

		// set the viewport "corner" coords
		void setViewport(double x1, double y1, double x2, double y2) { 
			v_min.set(x1, y1);
			v_max.set(x2, y2);
		}

		// set the window "corner" coords
		void setWindow(double x1, double y1, double x2, double y2) { 
			w_min.set(x1, y1);
			w_max.set(x2, y2);
		}

		void changeViewport(double xmin, double ymin, double xmax, double ymax); 
		void changeWindow(double xmin, double ymin, double xmax, double ymax); 

		Point2 windowToViewport(const Point2& in_v); 
		Point2 viewportToPixmap(const Point2& in_v); 
		
		void printViewport() { 
			std::cout << v_min << ' ' << v_max; 
		} 

		void printWindow(){ 
			std::cout << w_min << ' ' << w_max; 
		} 

		void moveTo2D(double x, double y){ 
			current_pos.set(x,y);
		} 

		void drawTo2D(color color, double x, double y);

		/****** 
		 * 
		 * 3D Related
		 * 
		 * ******/

		/* (fx, fy, fz) - Focal point; (theta, phi, alpha) - Orientation; (r) - Distance eye to origin */
		void defineCameraTransform(double fx, double fy, double fz, 
			double theta, double phi, double alpha, double r);

		void moveTo3D(double x, double y, double z);
		void drawTo3D(double x, double y, double z, color draw_color=colors::BLACK);
		
		void buildActiveTransform(transformCode tfCode, double tfValue);
		void resetActiveTransform();
		void showActiveTransform() {
			std::cout << *active_transform;
		}
};

/* Utility/helper funcs */
inline double clampd(double val, double min, double max) // need in-line bc func def
{
	if(val < min)
		return min;
	else if(val > max)
		return max;
	
	return val;
}

inline double range(double val, double min, double max) // need in-line bc func def
{
	if(val >= min && val <= max)
		return true;
	
	return false;
}

#endif




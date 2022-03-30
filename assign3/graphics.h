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

enum transformCode {X_TRANS, Y_TRANS, Z_TRANS, X_ROT, Y_ROT, Z_ROT, PERSPECTIVE};

class GraphicsSystem {
	protected:
		std::shared_ptr<Canvas> pixmap;
		Point2 w_min, w_max, v_min, v_max;
		double scale_x, scale_y;
		Point2 current_pos;

		std::shared_ptr<Matrix> camera, active_transform;

	public:
		GraphicsSystem() {	// Modification for 3d
			camera	= std::make_shared<Matrix>(4, identity); // hardcoded for 3d, make (size()) if want a 2d camera too?
			active_transform  = std::make_shared<Matrix>(4, identity);
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

		/* Pass in a matrix to intialize, the type of transform, and the value */
		void defineElementaryTransform(Matrix &m, transformCode tfCode, double tfValue);

		/* Pass in a matrix to premultiply, the type of transform, and the value */
		void buildElementaryTransform(Matrix &tfM, transformCode tfCode, double tfValue);

		void moveTo3D(double x, double y, double z);
		void draw3D(double x, double y, double z);

		/* Pass in a matrix to premultiply, the type of transform, and the value */
		Point3 applyTransform(double x, double y, double z, const Matrix& tfm);


};

#endif




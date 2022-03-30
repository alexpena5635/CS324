/* graphics.h
 */
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <memory>
#include <string>

#include "canvas.h"
#include "vec2.h"
#include "vec3.h"

class GraphicsSystem {
	protected:
		std::shared_ptr<Canvas> pixmap;
		Point2 w_min, w_max, v_min, v_max;
		double scale_x, scale_y;
		Point2 current_pos;

	public:
		GraphicsSystem() {}
		GraphicsSystem(std::shared_ptr<Canvas> c) : pixmap(c) {}

		void saveCanvas(std::string filename) { SaveCanvasToPBM(*pixmap, filename); }
		void clearCanvas() {pixmap->Clear();}
		
		void initGraphics(	
			const int w, const int h, 
			const double wxmin = -10, const double wymin = -10, const double wxmax = 10, const double wymax = 10, 
			const double vxmin = -1, const double vymin = -1, const double vxmax = 1, const double vymax = 1
		);

		void setViewport(double x1, double y1, double x2, double y2) { // set the viewport "corner" coords (global)
			v_min.set(x1, y1);
			v_max.set(x2, y2);
		}

		void setWindow(double x1, double y1, double x2, double y2) { // set the window "corner" coords (global)
			w_min.set(x1, y1);
			w_max.set(x2, y2);
		}
		
		void printViewport() { 
			std::cout << v_min << ' ' << v_max; 
		} 

		void printWindow(){ 
			std::cout << w_min << ' ' << w_max; 
		} 

		void changeViewport(double xmin, double ymin, double xmax, double ymax); 
		void changeWindow(double xmin, double ymin, double xmax, double ymax); 

		void windowToViewport(const Point2& in_v, Point2& out_v); 
		void viewportToPixmap(const Point2& in_v, Point2& out_v); 

		void moveTo2D(double x, double y){ // Setting some global that retains the world position we have "moved to"
			current_pos.set(x,y);
		} // On the canvas space, where the "pen" is moved to


		void drawTo2D(color color, double x, double y); // Go from the current spot to (x,y) an draw line


};

#endif




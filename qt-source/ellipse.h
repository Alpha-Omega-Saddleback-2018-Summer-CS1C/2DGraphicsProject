/*
 *  2D Graphics Modeler
 *  July 2018
 *
 *  David Epstein <DavidE92@live.com>
 *  Greg Graffius <ggraffius0@saddleback.edu>
 *  Justis Ketcham Justis <justis.ketcham@gmail.com>
 *  Brett Saiki <bksaiki@gmail.com>
 *
 *  Descr:   Final project for CS1C at Saddleback College (Summer 2018)
 *  Teacher: John Kath
 *
 *  Draws shapes using QPainter. Shapes can be loaded from a file, added
 *  to a vector, manipulated and later saved. A login is required to access
 *  the program.
 *
 **/
/*
    File: ellipse.h
    Derived class that defines a ellipse [x, y, rx, ry]
*/

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QPaintDevice>
#include <QPoint>
#include "shape.h"
#include "custom_vector.h"

class Ellipse: public Shape
{
 	public:
        Ellipse(QPaintDevice* paintDevice = nullptr, int id = -1); //ID, Position X, Y, Radius
        ~Ellipse();
		
		double area() override; // Return the area of the ciricle
        void draw() override; // Draw the circle
		void move(const QPoint& offset) override; // Translates the circle by a given offset
		double perimeter() override; // return the circumference of the ciricle
        void setRadii(int rx, int ry); // set the radius of the ciricle
        void setPosition(int x, int y); // Set the position of the circle
		
	private:
		QPoint mPosition;
        int mRadiusX, mRadiusY;
};
#endif // ELLIPSE_H

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
    File: circle.h
    Derived class that defines a circle [x, y, radius]
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "math.h"
#include <QBrush>
#include <QPen>
#include <QPoint>
#include "shape.h"
#include "custom_vector.h"

// M_PI = pi 
// Use: radius * M_PI

class Circle: public Shape
{
 	public:
		Circle();
		Circle(int id, int x, int y, int r); //ID, Position X, Y, Radius 
		~Circle(){}
		
		double area() override; // Return the area of the ciricle
		void draw(QPainter* painter) override; // Draw the circle
		void move(const QPoint& offset) override; // Translates the circle by a given offset
		double perimeter() override; // return the circumference of the ciricle
		void setBrush(const QBrush& pen); // Sets the QBrush type to change hwo the shape is drawn
		void setRadius(int r); // set the radius of the ciricle
		void setPen(const QPen& pen); // Set the Qpen type ot change hwo the circle is drawn
		void setPosition(int x, int y) // Set the position of the circle
		
	private:
		QPoint mPosition;
		int radius;
		Qpen mPen;
		QBrush mBrush;	
};
#endif // CIRCLE_H

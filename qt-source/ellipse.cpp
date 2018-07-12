79 lines (65 sloc)  1.3 KB
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
    File: circle.cpp
    Derived class that defines a circle [x, y, radius]
*/

#include "ellipse.h"

Ellipse::Ellipse()
{
	mId = 6;
}

Ellipse::Ellipse(int id, ind x, int y, int ra, int rb)
{
	mID = id;
	mPosition = {x, y};
	radiusA = ra;
	radiusB = rb;
}

double Ellipse::area()
{
	return (double)(M_PI * radiusA * radiusB);
}

void Ellipse::draw(QPainter* painter)
{
	
}

void Ellipse::move(const QPoint& offset)
{
	mPosition += offset;
}

double Ellipse::perimeter()
{
	return(double)(MPI * ( 3 * (radiusA + radiusB) - sqrt( (3*radiusA+radiusB) * (radiusA + 3 * radiusB) ) ) )
}

void Ellipse::setBrush(const QBrush& brush)
{
	mBrush = brush;
}

void Ellipse::setRadius(int r)
{
	radius = r;
}

void Ellipse::setPen(const QPen& pen)
{
	mPen = pen;
}

void Ellipse::setPosition(int x, int y)
{
	mPosition = {x, y};
}

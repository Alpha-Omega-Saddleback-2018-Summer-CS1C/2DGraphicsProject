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
    File: ellipse.cpp
    Derived class that defines a ellipse [x, y, rx, ry]
*/

#include "ellipse.h"

Ellipse::Ellipse()
{
    mID = 0;
	mType = ELLIPSE;
}

Ellipse::Ellipse(int id, int x, int y, int rx, int ry)
{
	mID = id;
	mType = ELLIPSE;
	mPosition = {x, y};
    mRadiusX = rx;
    mRadiusY = ry;
}

double Ellipse::area()
{
    return (M_PI * mRadiusX * mRadiusY);
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
    return M_PI * (3 * (mRadiusX + mRadiusY) - sqrt((3 * mRadiusX + mRadiusY) * (mRadiusX + 3 * mRadiusY )));
}

void Ellipse::setBrush(const QBrush& brush)
{
	mBrush = brush;
}

void Ellipse::setRadii(int rx, int ry)
{
    mRadiusX = rx;
    mRadiusY = ry;
}

void Ellipse::setPen(const QPen& pen)
{
	mPen = pen;
}

void Ellipse::setPosition(int x, int y)
{
	mPosition = {x, y};
}

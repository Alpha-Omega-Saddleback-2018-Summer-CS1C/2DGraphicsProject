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
    File: square.cpp

    Derived class that defines a square [x, y, side]
*/

#include "square.h"

Square::Square()
{
    mID = 0;
	mType = SQUARE;
}

Square::Square(int id, int x, int y, int side)
{
    mID = id;
	mType = SQUARE;
    mPosition = { x, y };
    mSide = side;
}

double Square::area()
{
    return (double)(mSide * mSide);
}

void Square::draw(QPainter* painter)
{

}

void Square::move(const QPoint& offset)
{
    mPosition += offset;
}

double Square::perimeter()
{
    return 4 * mSide;
}

void Square::setBrush(const QBrush& brush)
{
    mBrush = brush;
}

void Square::setDimensions(int side)
{
    mSide = side;
}

void Square::setPen(const QPen& pen)
{
    mPen = pen;
}

void Square::setPosition(int x, int y)
{
    mPosition = { x, y };
}

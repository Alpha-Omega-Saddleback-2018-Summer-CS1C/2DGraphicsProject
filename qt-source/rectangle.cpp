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
    File: rectangle.cpp

    Derived class that defines a rectangle [x, y, length, width]
*/

#include "rectangle.h"

Rectangle::Rectangle(QPaintDevice* paintDevice, int id)
{
    mID = id;
	mType = RECTANGLE;

    if(paintDevice != nullptr)
        mPainter.begin(paintDevice);
}

Rectangle::~Rectangle()
{
    mPainter.end();
}

double Rectangle::area()
{
    return (double)(mWidth * mHeight);
}

void Rectangle::draw()
{

}

void Rectangle::move(const QPoint& offset)
{
    mPosition += offset;
}

double Rectangle::perimeter()
{
    return 2.0 * (mWidth + mHeight);
}

void Rectangle::setDimensions(int w, int h)
{
    mWidth = w;
    mHeight = h;
}

void Rectangle::setPosition(int x, int y)
{
    mPosition = { x, y };
}

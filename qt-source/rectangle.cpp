/*
 *  2D Graphics Modeler
 *  July 2018
 *
 *  David Epstein <DavidE92@live.com>
 *  Greg Graffius <ggraffius0@saddleback.edu>
 *  Justis Ketcham Justis <justis.ketcham@gmail.com>
 *  Brett Saiki <bsaiki0@saddleback.edu>
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

Rectangle::Rectangle()
{
    mID = -1;
	mType = RECTANGLE;
}

double Rectangle::area()
{
    return (double)(mWidth * mHeight);
}

Vector<QString> Rectangle::dimensionLabels()
{
    Vector<QString> ret;
    ret.push_back("Position:");
    ret.push_back("(" + QString::number(mPosition.x()) + ", " + QString::number(mPosition.y()) + ")");
    ret.push_back("Width:");
    ret.push_back(QString::number(mWidth));
    ret.push_back("Height:");
    ret.push_back(QString::number(mHeight));

    return ret;
}

void Rectangle::draw()
{
    mPainter.setPen(mPen);
    mPainter.setBrush(mBrush);
    mPainter.drawRect(mPosition.x(), mPosition.y(), mWidth, mHeight);
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

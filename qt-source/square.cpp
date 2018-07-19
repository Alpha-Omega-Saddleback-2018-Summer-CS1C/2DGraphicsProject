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
    File: square.cpp

    Derived class that defines a square [x, y, side]
*/

#include "square.h"

Square::Square(QPaintDevice* paintDevice, int id)
{
    mID = id;
	mType = SQUARE;

    if(paintDevice != nullptr)
        mPainter.begin(paintDevice);
}

Square::~Square()
{
    if(mPainter.device() != 0)
        mPainter.end();
}

double Square::area()
{
    return (double)(mSide * mSide);
}

Vector<QString> Square::dimensionLabels()
{
    Vector<QString> ret;
    ret.push_back("Position:");
    ret.push_back("(" + QString::number(mPosition.x()) + ", " + QString::number(mPosition.y()) + ")");
    ret.push_back("Side:");
    ret.push_back(QString::number(mSide));

    return ret;
}

void Square::draw()
{
    mPainter.setPen(mPen);
    mPainter.setBrush(mBrush);
    mPainter.drawRect(mPosition.x(), mPosition.y(), mSide, mSide);
}

void Square::move(const QPoint& offset)
{
    mPosition += offset;
}

double Square::perimeter()
{
    return 4 * mSide;
}

void Square::setDimensions(int side)
{
    mSide = side;
}

void Square::setPosition(int x, int y)
{
    mPosition = { x, y };
}

void Square::setSide(int side)
{
    mSide = side;
}

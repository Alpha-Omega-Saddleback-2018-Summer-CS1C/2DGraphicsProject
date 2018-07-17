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
    File: shape.cpp

    Base class of all renderable objects
*/

#include "shape.h"

bool Shape::operator==(const Shape& shape) const
{
    return mID == shape.mID;
}

bool Shape::operator>(const Shape& shape) const
{
    return mID > shape.mID;
}

bool Shape::operator<(const Shape& shape) const
{
    return mID < shape.mID;
}

int Shape::getID() const
{
    return mID;
}

void Shape::setBrush(const QBrush& brush)
{
    mBrush = brush;
}

void Shape::setID(int id)
{
    mID = id;
}

void Shape::setPainter(QPaintDevice* paintDevice)
{
    if(paintDevice == nullptr)
        return;

    if(mPainter != nullptr)
        delete mPainter;

    mPainter = new QPainter(paintDevice);
}

void Shape::setPen(const QPen& pen)
{
    mPen = pen;
}

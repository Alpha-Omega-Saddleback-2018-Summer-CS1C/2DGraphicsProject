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

/* Returns the QBrush */
QBrush& Shape::getBrush()
{
    return mBrush;
}


int Shape::getID() const
{
    return mID;
}

QPainter& Shape::getPainter()
{
    return mPainter;
}

/* Returns the QPen */
QPen& Shape::getPen()
{
    return mPen;
}

ShapeType Shape::getType() const
{
    return mType;
}

QString Shape::getTypeAsQString() const
{
    if(mType == LINE)            return QString("Line");
    else if(mType == POLYLINE)   return QString("Polyline");
    else if(mType == POLYGON)    return QString("Polygon");
    else if(mType == RECTANGLE)  return QString("Rectangle");
    else if(mType == SQUARE)     return QString("Square");
    else if(mType == CIRCLE)     return QString("Circle");
    else if(mType == ELLIPSE)    return QString("Ellipse");
    else /* mType == TEXTBOX */  return QString("Textbox");
}

void Shape::setBrush(const QBrush& brush)
{
    mBrush = brush;
}

void Shape::setID(int id)
{
    mID = id;
}

void Shape::setPen(const QPen& pen)
{
    mPen = pen;
}

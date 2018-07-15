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
    File: polyline.cpp

    Derived class that defines a line with multiple points [x1, y1, x2, y2, ...]
*/

#include "polyline.h"

Polyline::Polyline()
{
    mID = 0;
}

Polyline::Polyline(int id, int* pointData, int pointCount)
{
    mID = id;
    for(int i = 0; i < pointCount; ++i)
        mPoints.push_back({ pointData[i * 2], pointData[i * 2 + 1]});
}

void Polyline::addPoint(const QPoint& point)
{
    mPoints.push_back(point);
}

double Polyline::area()
{
    return 0.0;
}

void Polyline::draw(QPainter* painter)
{

}

void Polyline::move(const QPoint& offset)
{
    for(Vector<QPoint>::iterator it = mPoints.begin(); it != mPoints.end(); ++it)
        *it += offset;
}

double Polyline::perimeter()
{
    return 0.0;
}

void Polyline::setPen(const QPen& pen)
{
    mPen = pen;
}

void Polyline::setPoint(int index, const QPoint& point)
{
    assert(index < mPoints.size());
    mPoints[index] = point;
}
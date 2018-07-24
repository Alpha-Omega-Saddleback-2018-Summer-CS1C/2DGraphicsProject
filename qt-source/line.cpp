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
    File: line.h

    Derived class that defines a line [x1, y1, x2, y2]
*/

#include "line.h"

using namespace shape;

Line::Line()
{
    mID = -1;
    mType = LINE;
}

double Line::area()
{
    return 0.0;
}

Vector<QString> Line::dimensionLabels()
{
    Vector<QString> ret;
    ret.push_back("Point 1:");
    ret.push_back("(" + QString::number(mPoint1.x()) + ", " + QString::number(mPoint1.y()) + ")");
    ret.push_back("Point 2:");
    ret.push_back("(" + QString::number(mPoint2.x()) + ", " + QString::number(mPoint2.y()) + ")");

    return ret;
}

void Line::draw()
{
    mPainter.setPen(mPen);
    mPainter.setBrush(mBrush);
    mPainter.drawLine(mPoint1, mPoint2);
}

void Line::move(const QPoint& offset)
{
    mPoint1 += offset;
    mPoint2 += offset;
}

double Line::perimeter()
{
    return 0.0;
}

void Line::setPoints(int x1, int y1, int x2, int y2)
{
    mPoint1 = { x1, y1 };
    mPoint2 = { x2, y2 };
}

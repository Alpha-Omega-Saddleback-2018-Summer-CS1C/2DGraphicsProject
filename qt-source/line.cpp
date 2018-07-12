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
    File: line.h

    Derived class that defines a line [x1, y1, x2, y2]
*/

#include "line.h"

Line::Line()
{
    mID = 0;
    mPoint1 = { 0, 0 };
    mPoint2 = { 0, 0 };
}

Line::Line(int id, int x1, int y1, int x2, int y2)
{
    mID =id;
    mPoint1 = { x1, y1 };
    mPoint2 = { x2, y2 };
}

double Line::area()
{
    return 0.0;
}

void Line::draw(QPainter* painter)
{

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

void Line::setPen(const QPen& pen)
{
    mPen = pen;
}

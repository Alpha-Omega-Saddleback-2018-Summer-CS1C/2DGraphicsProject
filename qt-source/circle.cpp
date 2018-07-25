/*
 *  2D Graphics Modeler
 *  July 2018
 *
 *  David Epstein <DavidE92@live.com>
 *  Greg Graffius <ggraffius0@saddleback.edu>
 *  Justis Ketcham <justis.ketcham@gmail.com>
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
    File: circle.cpp
    Derived class that defines a circle [x, y, radius]
*/

#include "circle.h"
#include "math.h"

using namespace shape;

Circle::Circle()
{
    mID = -1;
	mType = CIRCLE;
}

double Circle::area()
{
	return (double)(M_PI * radius * radius);
}

Vector<QString> Circle::dimensionLabels()
{
    Vector<QString> ret;
    ret.push_back("Center:");
    ret.push_back("(" + QString::number(mPosition.x()) + ", " + QString::number(mPosition.y()) + ")");
    ret.push_back("Radius:");
    ret.push_back(QString::number(radius));

    return ret;
}

void Circle::draw()
{
    mPainter.setPen(mPen);
    mPainter.setBrush(mBrush);
    mPainter.drawEllipse(mPosition, radius, radius);
    mPainter.drawText(mPosition.x(), mPosition.y(), 20, 20, Qt::AlignCenter, QString::number(mID));
    mPainter.drawText(mPosition.x(), mPosition.y() + 20, 50, 20, Qt::AlignCenter, "P: " + QString::number((int)perimeter()));
    mPainter.drawText(mPosition.x(), mPosition.y() + 40, 50, 20, Qt::AlignCenter, "A: " + QString::number((int)area()));
}

Vector<int> Circle::getDimensions()
{
    Vector<int> ret;
    ret.push_back(mPosition.x());
    ret.push_back(mPosition.y());
    ret.push_back(radius);

    return ret;
}

void Circle::move(const QPoint& offset)
{
	mPosition += offset;
}

double Circle::perimeter()
{
	return (2 * M_PI * radius);
}

void Circle::setRadius(int r)
{
	radius = r;
}

void Circle::setPosition(int x, int y)
{
	mPosition = {x, y};
}

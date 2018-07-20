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
    File: circle.cpp
    Derived class that defines a circle [x, y, radius]
*/

#include "circle.h"
#include "math.h"

Circle::Circle(QPaintDevice* paintDevice, int id)
{
	mID = id;
	mType = CIRCLE;

    if(paintDevice != nullptr)
        mPainter.begin(paintDevice);
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

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
    File: ellipse.cpp
    Derived class that defines a ellipse [x, y, rx, ry]
*/

#include "ellipse.h"
#include "math.h"

using namespace shape;

Ellipse::Ellipse()
{
    mID = -1;
	mType = ELLIPSE;
}

double Ellipse::area()
{
    return (M_PI * mRadiusX * mRadiusY);
}

void Ellipse::draw()
{
    mPainter.setPen(mPen);
    mPainter.setBrush(mBrush);
    mPainter.drawEllipse(mPosition, mRadiusX, mRadiusY);
}

Vector<QString> Ellipse::dimensionLabels()
{
    Vector<QString> ret;
    ret.push_back("Center:");
    ret.push_back("(" + QString::number(mPosition.x()) + ", " + QString::number(mPosition.y()) + ")");
    ret.push_back("RadiusX:");
    ret.push_back(QString::number(mRadiusX));
    ret.push_back("RadiusY:");
    ret.push_back(QString::number(mRadiusY));

    return ret;
}

void Ellipse::move(const QPoint& offset)
{
	mPosition += offset;
}

double Ellipse::perimeter()
{
    return M_PI * (3 * (mRadiusX + mRadiusY) - sqrt((3 * mRadiusX + mRadiusY) * (mRadiusX + 3 * mRadiusY )));
}

void Ellipse::setRadii(int rx, int ry)
{
    mRadiusX = rx;
    mRadiusY = ry;
}

void Ellipse::setPosition(int x, int y)
{
	mPosition = {x, y};
}

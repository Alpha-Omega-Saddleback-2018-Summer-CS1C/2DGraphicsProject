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
    File: ellipse.cpp
    Derived class that defines a ellipse [x, y, rx, ry]
*/

#include "ellipse.h"
#include "math.h"

Ellipse::Ellipse(QPaintDevice* paintDevice, int id)
{
	mID = id;
	mType = ELLIPSE;

    if(paintDevice != nullptr)
        mPainter.begin(paintDevice);
}

Ellipse::~Ellipse()
{
    mPainter.end();
}

double Ellipse::area()
{
    return (M_PI * mRadiusX * mRadiusY);
}

void Ellipse::draw()
{
	
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

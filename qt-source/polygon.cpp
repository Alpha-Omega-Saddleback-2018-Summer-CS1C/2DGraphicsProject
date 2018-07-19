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
    File: polygon.cpp

    Derived class that defines a polygon with multiple points [x1, y1, x2, y2, ...]
*/

#include "polygon.h"
#include "math.h"

Polygon::Polygon(QPaintDevice* paintDevice, int id)
{
    mID = id;
	mType = POLYGON;

    if(paintDevice != nullptr)
        mPainter.begin(paintDevice);
}

Polygon::~Polygon()
{
    if(mPainter.device() != 0)
        mPainter.end();
}

void Polygon::addPoint(const QPoint& point)
{
    mPoints.push_back(point);
}

double Polygon::area()
{
    double sum = 0.0;

    for(Vector<QPoint>::iterator it = mPoints.begin(); it != mPoints.end(); ++it)
    {
        Vector<QPoint>::iterator it2 = it + 1;

        if(it2 == mPoints.end())
            it2 = mPoints.begin();

        sum += (it->x() * it2->y() - it->y() * it2->x());
    }

    return sum / 2;
}

Vector<QString> Polygon::dimensionLabels()
{
    Vector<QString> ret;
    int pointCount = mPoints.size();

    if(pointCount > 5)
    {
        for(int i = 0; i < 3; ++i)
        {
            ret.push_back("Point " + QString::number(i + 1) + ":");
            ret.push_back("(" + QString::number(mPoints[i].x()) + ", " + QString::number(mPoints[i].y()) + ")");
        }

        ret.push_back("...");
        ret.push_back("...");
        ret.push_back("Point " + QString::number(pointCount) + ":");
        ret.push_back("(" + QString::number(mPoints[pointCount - 1].x()) + ", " + QString::number(mPoints[pointCount - 1].y()) + ")");
    }
    else
    {
        for(int i = 0; i < 5; ++i)
        {
            ret.push_back("Point " + QString::number(i + 1) + ":");
            ret.push_back("(" + QString::number(mPoints[i].x()) + ", " + QString::number(mPoints[i].y()) + ")");
        }
    }

    return ret;
}

void Polygon::draw()
{
    mPainter.setPen(mPen);
    mPainter.setBrush(mBrush);
    mPainter.drawPolygon(&mPoints[0], mPoints.size());
}

void Polygon::move(const QPoint& offset)
{
    for(Vector<QPoint>::iterator it = mPoints.begin(); it != mPoints.end(); ++it)
        *it += offset;
}

double Polygon::perimeter()
{
    double sum = 0.0;

    for(Vector<QPoint>::iterator it = mPoints.begin(); it != mPoints.end(); ++it)
    {
        Vector<QPoint>::iterator it2 = it + 1;

        if(it2 == mPoints.end())
            it2 = mPoints.begin();

        int x = it->x() - it2->x();
        int y = it->y() - it2->y();
        sum += sqrt((x * x) + (y * y));
    }

    return sum;
}

void Polygon::setPointData(int* pointData, int pointCount)
{
    for(int i = 0; i < pointCount; ++i)
        mPoints.push_back({ pointData[i * 2], pointData[i * 2 + 1]});
}

void Polygon::setPoint(int index, const QPoint& point)
{
    assert(index < mPoints.size());
    mPoints[index] = point;
}

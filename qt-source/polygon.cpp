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
    File: polygon.cpp

    Derived class that defines a polygon with multiple points [x1, y1, x2, y2, ...]
*/

#include "polygon.h"
#include "math.h"

using namespace shape;

Polygon::Polygon()
{
    mID = -1;
    mType = POLYGON;
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

void Polygon::clearPoints()
{
    mPoints.clear();
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
        for(int i = 0; i < pointCount; ++i)
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
    mPainter.drawText(mPoints[0].x(), mPoints[0].y(), 20, 20, Qt::AlignCenter, QString::number(mID));
    mPainter.drawText(mPoints[0].x(), mPoints[0].y() + 20, 50, 20, Qt::AlignCenter, "P: " + QString::number((int)perimeter()));
    mPainter.drawText(mPoints[0].x(), mPoints[0].y() + 40, 50, 20, Qt::AlignCenter, "A: " + QString::number((int)area()));
}

void Polygon::move(const QPoint& offset)
{
    for(Vector<QPoint>::iterator it = mPoints.begin(); it != mPoints.end(); ++it)
        *it += offset;
}

Vector<int> Polygon::getDimensions()
{
    Vector<int> ret;

    for(int i = 0; i < mPoints.size(); ++i)
    {
        ret.push_back(mPoints[i].x());
        ret.push_back(mPoints[i].y());
    }

    return ret;
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

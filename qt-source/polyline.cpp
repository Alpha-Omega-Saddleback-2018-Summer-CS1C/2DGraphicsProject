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
    File: polyline.cpp

    Derived class that defines a line with multiple points [x1, y1, x2, y2, ...]
*/

#include "polyline.h"

using namespace shape;

Polyline::Polyline()
{
    mID = -1;
    mType = POLYLINE;
}

void Polyline::addPoint(const QPoint& point)
{
    mPoints.push_back(point);
}

double Polyline::area()
{
    return 0.0;
}

void Polyline::clearPoints()
{
    mPoints.clear();
}

Vector<QString> Polyline::dimensionLabels()
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

void Polyline::draw()
{
    mPainter.setPen(mPen);
    mPainter.setBrush(mBrush);
    mPainter.drawPolyline(&mPoints[0], mPoints.size());
    mPainter.drawText(mPoints[0].x(), mPoints[0].y(), 20, 20, Qt::AlignCenter, QString::number(mID));
}

Vector<int> Polyline::getDimensions()
{
    Vector<int> ret;

    for(int i = 0; i < mPoints.size(); ++i)
    {
        ret.push_back(mPoints[i].x());
        ret.push_back(mPoints[i].y());
    }

    return ret;
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

void Polyline::setPointData(int* pointData, int pointCount)
{
    for(int i = 0; i < pointCount; ++i)
        mPoints.push_back({ pointData[i * 2], pointData[i * 2 + 1]});
}

void Polyline::setPoint(int index, const QPoint& point)
{
    assert(index < mPoints.size());
    mPoints[index] = point;
}

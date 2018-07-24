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
    File: polyline.h

    Derived class that defines a line with multiple points [x1, y1, x2, y2, ...]
*/

#ifndef POLYLINE_H
#define POLYLINE_H

#include <QPaintDevice>
#include <QPoint>
#include "custom_vector.h"
#include "shape.h"

class Polyline : public Shape
{
public:
    Polyline();
    ~Polyline() {}

    /* Adds a point to this shape */
    void addPoint(const QPoint& point);

    /* Returns the area of this shape */
    double area() override;

    /* Returns the dimensions of this shape for use in QLabels */
    Vector<QString> dimensionLabels() override;

    /* Draws this shape */
    void draw() override;

    /* Translates this shape by a given offset */
    void move(const QPoint& offset) override;

    /* Returns the perimeter of this this shape */
    double perimeter() override;

    /* Sets all the points of this shape */
    void setPointData(int* pointData, int pointCount);

    /* Sets a point of this shape */
    void setPoint(int index, const QPoint& point);

private:
    Vector<QPoint> mPoints;
};

#endif // POLYLINE_H

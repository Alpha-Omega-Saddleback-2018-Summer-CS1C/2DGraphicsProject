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
    File: polygon.h

    Derived class that defines a polygon with multiple points [x1, y1, x2, y2, ...]
*/

#ifndef POLYGON_H
#define POLYGON_H

#include "math.h"
#include <QBrush>
#include <QPen>
#include <QPoint>
#include "shape.h"
#include "custom_vector.h"

class Polygon : public Shape
{
public:
    Polygon();
    Polygon(int id, int* pointData, int pointCount);
    ~Polygon() {}

    /* Adds a point to this shape */
    void addPoint(const QPoint& point);

    /* Returns the area of this shape */
    double area() override;

    /* Draws this shape */
    void draw(QPainter* painter) override;

    /* Translates this shape by a given offset */
    void move(const QPoint& offset) override;

    /* Returns the perimeter of this this shape */
    double perimeter() override;

    /* Sets the QBrush type to change how the shape is drawn */
    void setBrush(const QBrush& pen);

    /* Sets the QPen type to change how the shape is drawn */
    void setPen(const QPen& pen);

    /* Sets a point of this shape */
    void setPoint(int index, const QPoint& point);

private:
    Vector<QPoint> mPoints;
    QPen mPen;
    QBrush mBrush;
};

#endif // POLYGON_H

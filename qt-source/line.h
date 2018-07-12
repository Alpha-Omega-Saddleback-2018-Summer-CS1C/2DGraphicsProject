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

#ifndef LINE_H
#define LINE_H

#include <QPen>
#include <QPoint>
#include "shape.h"

class Line : public Shape
{
public:
    Line();
    Line(int id, int x1, int y1, int x2, int y2);
    ~Line() {}

    /* Returns the area of this shape */
    double area() override;

    /* Draws this shape */
    void draw(QPainter* painter) override;

    /* Translates this shape by a given offset */
    void move(const QPoint& offset) override;

    /* Returns the perimeter of this this shape */
    double perimeter() override;

    /* Sets the QPen type to change how the shape is drawn */
    void setPen(const QPen& pen);

private:
    QPoint mPoint1;
    QPoint mPoint2;
    QPen mPen;
};

#endif // LINE_H

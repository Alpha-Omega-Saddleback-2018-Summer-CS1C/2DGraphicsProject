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
    File: rectangle.h

    Derived class that defines a rectangle [x, y, length, width]
*/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "math.h"
#include <QBrush>
#include <QPen>
#include <QPoint>
#include "shape.h"
#include "custom_vector.h"

class Rectangle : public Shape
{
public:
    Rectangle();
    Rectangle(int id, int x, int y, int w, int h);
    ~Rectangle() {}

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

    /* Sets the dimension of this shape */
    void setDimensions(int w, int h);

    /* Sets the QPen type to change how the shape is drawn */
    void setPen(const QPen& pen);

    /* Sets the position of this shape */
    void setPosition(int x, int y);

private:
    QPoint mPosition;
    int mWidth;
    int mHeight;
    QPen mPen;
    QBrush mBrush;
};

#endif // RECTANGLE_H

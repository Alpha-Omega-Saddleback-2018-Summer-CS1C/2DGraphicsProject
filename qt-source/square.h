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
    File: square.h

    Derived class that defines a square [x, y, side]
*/

#ifndef SQUARE_H
#define SQUARE_H

#include <QPaintDevice>
#include <QPoint>
#include "shape.h"
#include "custom_vector.h"

class Square : public Shape
{
public:
    Square(QPaintDevice* paintDevice = nullptr, int id = -1);
    ~Square();

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

    /* Sets the dimension of this shape */
    void setDimensions(int side);

    /* Sets the position of this shape */
    void setPosition(int x, int y);

    /* Sets the side length of this shape */
    void setSide(int side);

private:
    int mID;
    QPoint mPosition;
    int mSide;
};

#endif // SQUARE_H





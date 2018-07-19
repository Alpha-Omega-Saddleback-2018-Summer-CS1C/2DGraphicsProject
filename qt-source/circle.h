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
    File: circle.h
    Derived class that defines a circle [x, y, radius]
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPaintDevice>
#include <QPoint>
#include "shape.h"

class Circle: public Shape
{
public:
    Circle(QPaintDevice* paintDevice = nullptr, int id = -1); //ID, Position X, Y, Radius
    ~Circle();

    double area() override; // Return the area of the ciricle
    Vector<QString> dimensionLabels() override; // Returns the dimensions of this shape for use in QLabels
    void draw() override; // Draw the circle
    void move(const QPoint& offset) override; // Translates the circle by a given offset
    double perimeter() override; // return the circumference of the ciricle
    void setRadius(int r); // set the radius of the ciricle
    void setPosition(int x, int y); // Set the position of the circle

private:
    QPoint mPosition;
    int radius;
};
#endif // CIRCLE_H

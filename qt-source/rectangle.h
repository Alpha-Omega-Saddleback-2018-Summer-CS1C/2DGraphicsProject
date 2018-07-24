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
    File: rectangle.h

    Derived class that defines a rectangle [x, y, length, width]
*/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QPaintDevice>
#include <QPoint>
#include "custom_vector.h"
#include "shape.h"

namespace shape
{
    class Rectangle : public Shape
    {
    public:
        Rectangle();
        ~Rectangle() {}

        /* Returns the area of this shape */
        double area() override;

        /* Returns the dimensions of this shape for use in QLabels */
        Vector<QString> dimensionLabels() override;

        /* Draws this shape */
        void draw() override;

        /* Returns the dimensions of this shape as a vector */
        Vector<int> getDimensions() override;

        /* Translates this shape by a given offset */
        void move(const QPoint& offset) override;

        /* Returns the perimeter of this this shape */
        double perimeter() override;

        /* Sets the dimension of this shape */
        void setDimensions(int w, int h);

        /* Sets the position of this shape */
        void setPosition(int x, int y);

    private:
        QPoint mPosition;
        int mWidth;
        int mHeight;
    };
}

#endif // RECTANGLE_H

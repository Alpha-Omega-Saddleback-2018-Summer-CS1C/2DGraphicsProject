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
    File: shape.h

    Base class of all renderable objects
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QString>
#include "custom_vector.h"

namespace shape
{
    class Shape
    {
    public:

        enum ShapeType
        {
            LINE = 0,
            POLYLINE,
            POLYGON,
            RECTANGLE,
            SQUARE,
            CIRCLE,
            ELLIPSE,
            TEXTBOX
        };

        virtual ~Shape() {}

        /* Compares ID's */
        bool operator==(const Shape& shape) const;
        bool operator>(const Shape& shape) const;
        bool operator<(const Shape& shape) const;

        /* Returns the area of the shape */
        virtual double area() = 0;

        /* Draws this shape */
        virtual void draw() = 0;

        /* Returns the dimensions of this shape for use in QLabels */
        virtual Vector<QString> dimensionLabels() = 0;

        /* Returns the QBrush */
        QBrush& getBrush();

        /* Returns the Shape ID */
        int getID() const;

        /* Returns the QPainter */
        QPainter& getPainter();

        /* Returns the QPen */
        QPen& getPen();

        /* Returns the Shape type */
        ShapeType getType() const;

        /* Returns the Shape type as a QString */
        QString getTypeAsQString() const;

        /* Translates this shape by a given offset */
        virtual void move(const QPoint& offset) = 0;

        /* Returns the perimeter of the shape */
        virtual double perimeter() = 0;

        /* Sets the QBrush type */
        void setBrush(const QBrush& brush);

        /* Sets the Shape ID */
        void setID(int id);

        /* Sets the QPen type */
        void setPen(const QPen& pen);

    protected:
        int 		mID;
        ShapeType 	mType;

        QPainter    mPainter;
        QPen        mPen;
        QBrush      mBrush;
    };
}

#endif // SHAPE_H

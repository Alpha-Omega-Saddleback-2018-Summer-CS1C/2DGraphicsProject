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
    File: shape.h

    Base class of all renderable objects
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>

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

class Shape
{
public:
    virtual ~Shape() {}

    inline bool operator==(const Shape& shape) const
    {
        return mID == shape.mID;
    }

    inline bool operator>(const Shape& shape) const
    {
        return mID > shape.mID;
    }

    inline bool operator<(const Shape& shape) const
    {
        return mID < shape.mID;
    }

    /* Returns the Shape ID */
    inline int getID() const
    {
        return mID;
    }

    /* Sets the Shape ID */
    inline void setID(int id)
    {
        mID = id;
    }

    /* Returns the area of the shape */
    virtual double area() = 0;

    /* Draws this shape */
    virtual void draw(QPainter* painter) = 0;

    /* Translates this shape by a given offset */
    virtual void move(const QPoint& offset) = 0;

    virtual double perimeter() = 0;

protected:
    int 		mID;
	ShapeType 	mType;
};

#endif // SHAPE_H

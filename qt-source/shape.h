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

/** \namespace shape
 *	
 * 	All shapes are defined in this namespace to avoid name collision with the standard library,
 *  mainly "window.h".
 */
namespace shape
{
	/**	Defines a shape abstract base class. All shapes are derived from this class. */
    class Shape
    {
    public:

		/** Defines type of shape */
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

		/** Destructor. */
        virtual ~Shape() {}

		/** Equality operator. Compares IDs */
        bool operator==(const Shape& shape) const;
		
		/** Greater than operator. Compares IDs */
        bool operator>(const Shape& shape) const;
		
		/** Less than operator. Compares IDs */
        bool operator<(const Shape& shape) const;

        /** Returns the area of the shape. */
        virtual double area() = 0;

        /** Draws this shape. */
        virtual void draw() = 0;

        /** Returns a QString list detailing the dimensions of this shape. */
        virtual Vector<QString> dimensionLabels() = 0;

        /** Returns the QBrush. */
        QBrush& getBrush();

        /** Returns the dimensions of this shape as a vector. */
        virtual Vector<int> getDimensions() = 0;

        /** Returns the Shape ID. */
        int getID() const;

        /** Returns the QPainter. */
        QPainter& getPainter();

        /** Returns the QPen. */
        QPen& getPen();

        /** Returns the Shape type. */
        ShapeType getType() const;

        /** Returns the Shape type as a QString. */
        QString getTypeAsQString() const;

        /** Translates this shape by a given offset. */
        virtual void move(const QPoint& offset) = 0;

        /** Returns the perimeter of the shape. */
        virtual double perimeter() = 0;

        /** Sets the QBrush type. */
        void setBrush(const QBrush& brush);

        /** Sets the Shape ID. */
        void setID(int id);

        /** Sets the QPen type. */
        void setPen(const QPen& pen);

    protected:
	
		/** Unique identifier */
        int 		mID;	
		/** Shape type */
        ShapeType 	mType;		

		/** QPen object used to draw this shape */
        QPainter    mPainter;	
		/** QPen object used to set QPainter member */
        QPen        mPen;
		/** QBrush object used to set QPainter member */
        QBrush      mBrush;
    };

    /** Templated comparator. Returns true if the area of the first shape is larger than the area of the second */
    struct compare_shape_area
    {
        bool operator()(Shape* s1, Shape* s2)
        {
            return s1->area() < s2->area();
        }
    };

    /** Templated comparator. Returns true if the perimeter of the first shape is larger than the area of the perimeter */
    struct compare_shape_perimeter
    {
        bool operator()(Shape* s1, Shape* s2)
        {
            return s1->perimeter() < s2->perimeter();
        }
    };
}

/*
 *  Helper functions
 */

/** Returns brush style as a QString. */
QString getBrushStyleAsQString(Qt::BrushStyle style);

/** Returns brush style from a QString. */
Qt::BrushStyle getBrushStyleFromQString(const QString& style);

/** Returns font weight as a QString. */
QString getFontStyleAsQString(QFont::Style style);

/** Returns font weight from a  QString. */
QFont::Style getFontStyleFromQString(const QString& style);

/** Returns font style as a QString. */
QString getFontWeightAsQString(int weight);

/** Returns font style from a QString. */
int getFontWeightFromQString(const QString& weight);

/** Returns pen cap style as a QString. */
QString getPenCapStyleAsQString(Qt::PenCapStyle style);

/** Returns pen cap style from a QString. */
Qt::PenCapStyle getPenCapStyleFromQString(const QString& style);

/** Returns pen join style as a QString. */
QString getPenJoinStyleAsQString(Qt::PenJoinStyle style);

/** Returns pen join style from a QString. */
Qt::PenJoinStyle getPenJoinStyleFromQString(const QString& style);

/** Returns PenStyle as a QString. */
QString getPenStyleAsQString(Qt::PenStyle style);

/** Returns PenStyle from a QString. */
Qt::PenStyle getPenStyleFromQString(const QString& style);

/** Returns QColor as a QString. */
QString getQColorAsQString(QColor color);

/** Returns brush style as a QString. */
QString getTextAlignmentAsQString(Qt::AlignmentFlag alignment);

/** Returns brush style from a QString. */
Qt::AlignmentFlag getTextAlignmentFromQString(const QString& alignment);

/** Trims the QString if necessary. */
QString getTextStringTrimmed(const QString& str);

/** Returns true if the string is a number. */
bool isNumber(const QString& str);

#endif // SHAPE_H

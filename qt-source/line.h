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
    File: line.h

    Derived class that defines a line [x1, y1, x2, y2]
*/

#ifndef LINE_H
#define LINE_H

#include <QPaintDevice>
#include <QPen>
#include <QPoint>
#include "shape.h"

/** \namespace shape
 *	
 * 	All shapes are defined in this namespace to avoid name collision with the standard library,
 *  mainly "window.h".
 */
namespace shape
{
	
	/**	Implements a line [x1, y1, x2, y2] that inherits from shape. It will be rendered by the
     * 	RenderArea widget and can be saved in a text file.
	 */
    class Line : public Shape
    {
    public:	
		/**	Default constructor. Sets the shape ID to an invalid value. */
        Line();
		
		/** Destructor. It is explicitly defined because this class is a derived type. */
        ~Line() {}

        /** Returns the area of this shape. */
        double area() override;
		
		/** Returns a QString list detailing the dimensions of this shape.  */
        Vector<QString> dimensionLabels() override;
		
		/** Returns the dimensions of this shape as a vector. */
        Vector<int> getDimensions() override;
		
		/** Draw the shape. */
        void draw() override;
		
		/** Translates the shape by a given offset. */
        void move(const QPoint& offset) override;
		
		/** Returns the circumference of the shape. */
        double perimeter() override;

        /** Sets the points of this line. */
        void setPoints(int x1, int y1, int x2, int y2);

    private:
        QPoint mPoint1;
        QPoint mPoint2;
    };
}

#endif // LINE_H

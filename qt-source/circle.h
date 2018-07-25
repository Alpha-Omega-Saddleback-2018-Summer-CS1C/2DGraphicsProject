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
    File: circle.h
    Derived class that defines a circle [x, y, radius]
*/

#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPaintDevice>
#include <QPoint>
#include "shape.h"

 
/** \namespace shape
 *	
 * 	All shapes are defined in this namespace to avoid name collision with the standard library,
 *  mainly "window.h".
 */
namespace shape
{
	/**	Implements a circle [x, y, radius] that inherits from shape. It will be rendered by the
     * 	RenderArea widget and can be saved in a text file.
	 */
    class Circle: public Shape
    {
    public:
	
		/**	Default constructor. Sets the shape ID to an invalid value. */
        Circle();
		
		/** Destructor. It is explicitly defined because this class is a derived type. */
        ~Circle() {}

		/** Returns the area of this circle. */
        double area() override;
		
		/** Returns a QString list detailing the dimensions of this circle.  */
        Vector<QString> dimensionLabels() override;
		
		/** Returns the dimensions of this shape as a vector. */
        Vector<int> getDimensions() override;
		
		/** Draw the circle. */
        void draw() override;
		
		/** Translates the circle by a given offset. */
        void move(const QPoint& offset) override;
		
		/** Returns the circumference of the circle. */
        double perimeter() override;
		
		/** Sets the radius of the circle. */
        void setRadius(int r);
		
		/** Set the position of the circle. */
        void setPosition(int x, int y);

    private:
        QPoint mPosition;
        int radius;
    };
}

#endif // CIRCLE_H

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
    File: textbox.h

    Derived a text box [x, y, length, width]
*/

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QPaintDevice>
#include <QPoint>
#include <QString>
#include "shape.h"
#include "custom_vector.h"

/** \namespace shape
 *	
 * 	All shapes are defined in this namespace to avoid name collision with the standard library,
 *  mainly "window.h".
 */
namespace shape
{
	/**	Implements a rectangle [x1, y1, length, width] that inherits from shape. It will be rendered by the
     * 	RenderArea widget and can be saved in a text file.
	 */
    class TextBox : public Shape
    {
    public:
		/**	Default constructor. Sets the shape ID to an invalid value. */
        TextBox();
		
		/** Destructor. It is explicitly defined because this class is a derived type. */
        ~TextBox() {}

        /** Returns the area of this shape. */
        double area() override;

		/** Returns a QString list detailing the dimensions of this shape.  */
        Vector<QString> dimensionLabels() override;
		
		/** Returns the dimensions of this shape as a vector. */
        Vector<int> getDimensions() override;
		
		/** Draw the shape. */
        void draw() override;

        /** Returns the QFont of the text box. */
        QFont& getFont();

        /** Returns the alignment of the text box. */
        Qt::AlignmentFlag getAlignment() const;

        /** Returns the text string. */
        QString getText() const;

        /** Translates the shape by a given offset. */
        void move(const QPoint& offset) override;
		
		/** Returns the circumference of the shape. */
        double perimeter() override;

        /** Sets the alignment of the text. */
        void setAlignment(Qt::AlignmentFlag flags);

        /** Sets the dimension of this shape. */
        void setDimensions(int w, int h);

        /** Sets the QFont type to change how the shape is drawn. */
        void setFont(const QFont& font);

        /** Sets the position of this shape. */
        void setPosition(int x, int y);

        /** Sets the QPen type to change how the shape is drawn. */
        void setText(const QString& text);

    private:
        QPoint mPosition;
        int mWidth;
        int mHeight;

        QFont mFont;
        QString mText;
        Qt::AlignmentFlag mAlignmentFlags;
    };
}

#endif // TEXTBOX_H

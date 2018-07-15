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
    File: textbox.h

    Derived a text box [x, y, length, width]
*/

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QPen>
#include <QPoint>
#include <QString>
#include "shape.h"
#include "custom_vector.h"

class TextBox : public Shape
{
public:
    TextBox();
    TextBox(int id, int x, int y, int w, int h);
    ~TextBox() {}

    /* Returns the area of this shape */
    double area() override;

    /* Draws this shape */
    void draw(QPainter* painter) override;

    /* Translates this shape by a given offset */
    void move(const QPoint& offset) override;

    /* Returns the perimeter of this this shape */
    double perimeter() override;

    /* Sets the alignment of the text */
    void setAlignment(Qt::AlignmentFlag flags);

    /* Sets the dimension of this shape */
    void setDimensions(int w, int h);

    /* Sets the QFont type to change how the shape is drawn */
    void setFont(const QFont& font);

    /* Sets the QPen type to change how the shape is drawn */
    void setPen(const QPen& pen);

    /* Sets the position of this shape */
    void setPosition(int x, int y);

    /* Sets the QPen type to change how the shape is drawn */
    void setText(const QString& text);

private:
    QPoint mPosition;
    int mWidth;
    int mHeight;

    QPen mPen;
    QFont mFont;
    QString mText;
    Qt::AlignmentFlag mAlignmentFlags;
};

#endif // TEXTBOX_H
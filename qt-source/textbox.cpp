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
    File: textbox.cpp

    Derived a text box [x, y, length, width]
*/

#include "textbox.h"

TextBox::TextBox()
{
    mID = 0;
}

TextBox::TextBox(int id, int x, int y, int w, int h)
{
    mID = id;
    mPosition = { x, y };
    mWidth = w;
    mHeight = h;
}

double TextBox::area()
{
    return (double)(mWidth * mHeight);
}

void TextBox::draw(QPainter* painter)
{

}

void TextBox::move(const QPoint& offset)
{
    mPosition += offset;
}

double TextBox::perimeter()
{
    return 2.0 * (mWidth + mHeight);
}

void TextBox::setAlignment(int flags)
{
    mAlignmentFlags = flags;
}

void TextBox::setDimensions(int w, int h)
{
    mWidth = w;
    mHeight = h;
}

void TextBox::setFont(const QFont& font)
{
    mFont = font;
}

void TextBox::setPen(const QPen& pen)
{
    mPen = pen;
}

void TextBox::setPosition(int x, int y)
{
    mPosition = { x, y };
}

void TextBox::setText(const QString& text)
{
    mText = text;
}

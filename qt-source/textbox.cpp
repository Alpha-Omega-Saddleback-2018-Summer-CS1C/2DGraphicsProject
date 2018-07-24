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
    File: textbox.cpp

    Derived a text box [x, y, length, width]
*/

#include "textbox.h"

using namespace shape;

TextBox::TextBox()
{
    mID = -1;
	mType = TEXTBOX;
}

double TextBox::area()
{
    return (double)(mWidth * mHeight);
}

Vector<QString> TextBox::dimensionLabels()
{
    Vector<QString> ret;
    ret.push_back("Position:");
    ret.push_back("(" + QString::number(mPosition.x()) + ", " + QString::number(mPosition.y()) + ")");
    ret.push_back("Width:");
    ret.push_back(QString::number(mWidth));
    ret.push_back("Height:");
    ret.push_back(QString::number(mHeight));

    return ret;
}

void TextBox::draw()
{
    mPainter.setPen(mPen);
    mPainter.setFont(mFont);
    mPainter.drawText(mPosition.x(), mPosition.y(), mWidth, mHeight, mAlignmentFlags, mText);

    mPainter.setFont(QFont());
    mPainter.drawText(mPosition.x(), mPosition.y(), 20, 20, Qt::AlignCenter, QString::number(mID));
}

Vector<int> TextBox::getDimensions()
{
    Vector<int> ret;
    ret.push_back(mPosition.x());
    ret.push_back(mPosition.y());
    ret.push_back(mWidth);
    ret.push_back(mHeight);

    return ret;
}

QFont& TextBox::getFont()
{
    return mFont;
}

Qt::AlignmentFlag TextBox::getAlignment() const
{
    return mAlignmentFlags;
}

QString TextBox::getText() const
{
    return mText;
}

void TextBox::move(const QPoint& offset)
{
    mPosition += offset;
}

double TextBox::perimeter()
{
    return 2.0 * (mWidth + mHeight);
}

void TextBox::setAlignment(Qt::AlignmentFlag flags)
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

void TextBox::setPosition(int x, int y)
{
    mPosition = { x, y };
}

void TextBox::setText(const QString& text)
{
    mText = text;
}

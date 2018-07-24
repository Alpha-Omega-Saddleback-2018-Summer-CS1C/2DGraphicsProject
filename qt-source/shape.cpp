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
    File: shape.cpp

    Base class of all renderable objects
*/

#include "shape.h"

using namespace shape;

bool Shape::operator==(const Shape& shape) const
{
    return mID == shape.mID;
}

bool Shape::operator>(const Shape& shape) const
{
    return mID > shape.mID;
}

bool Shape::operator<(const Shape& shape) const
{
    return mID < shape.mID;
}

/* Returns the QBrush */
QBrush& Shape::getBrush()
{
    return mBrush;
}


int Shape::getID() const
{
    return mID;
}

QPainter& Shape::getPainter()
{
    return mPainter;
}

/* Returns the QPen */
QPen& Shape::getPen()
{
    return mPen;
}

Shape::ShapeType Shape::getType() const
{
    return mType;
}

QString Shape::getTypeAsQString() const
{
    if(mType == LINE)            return QString("Line");
    else if(mType == POLYLINE)   return QString("Polyline");
    else if(mType == POLYGON)    return QString("Polygon");
    else if(mType == RECTANGLE)  return QString("Rectangle");
    else if(mType == SQUARE)     return QString("Square");
    else if(mType == CIRCLE)     return QString("Circle");
    else if(mType == ELLIPSE)    return QString("Ellipse");
    else /* mType == TEXTBOX */  return QString("Textbox");
}

void Shape::setBrush(const QBrush& brush)
{
    mBrush = brush;
}

void Shape::setID(int id)
{
    mID = id;
}

void Shape::setPen(const QPen& pen)
{
    mPen = pen;
}

/*
 *  Helper functions
 */

QString getBrushStyleAsQString(Qt::BrushStyle style)
{
    if(style == Qt::NoBrush)            return QString("None");
    else if(style == Qt::SolidPattern)  return QString("Solid");
    else if(style == Qt::HorPattern)    return QString("Horizontal Lines");
    else if(style == Qt::VerPattern)    return QString("Vertical Lines");
    else                                return QString("--");
}

Qt::BrushStyle getBrushStyleFromQString(const QString& style)
{
    if(style == "None")                     return Qt::NoBrush;
    else if(style == "Solid")               return Qt::SolidPattern;
    else if(style == "Horizontal Lines")    return Qt::HorPattern;
    else /* Vertical Lines */               return Qt::VerPattern;
}

QString getFontStyleAsQString(QFont::Style style)
{
    if(style == QFont::StyleNormal)         return QString("Normal");
    else if(style == QFont::StyleItalic)    return QString("Italic");
    else if(style == QFont::StyleOblique)   return QString("Oblique");
    else                                    return QString("--");
}

QFont::Style getFontStyleFromQString(const QString& style)
{
    if(style == "Normal")       return QFont::StyleNormal;
    else if(style == "Italic")  return QFont::StyleItalic;
    else /* Oblique */          return QFont::StyleOblique;
}

QString getFontWeightAsQString(int weight)
{
    if(weight == QFont::Thin)           return QString("Thin");
    else if(weight == QFont::Light)     return QString("Light");
    else if(weight == QFont::Normal)    return QString("Normal");
    else if(weight == QFont::Bold)      return QString("Bold");
    else                                return QString("--");
}

int getFontWeightFromQString(const QString& weight)
{
    if(weight == "Thin")            return QFont::Thin;
    else if(weight == "Light")      return QFont::Light;
    else if(weight == "Normal")     return QFont::Normal;
    else /* Bold */                 return QFont::Bold;
}

QString getPenCapStyleAsQString(Qt::PenCapStyle style)
{
    if(style == Qt::SquareCap)          return QString("Square");
    else if(style == Qt::FlatCap)       return QString("Flat");
    else if(style == Qt::RoundCap)      return QString("Round");
    else                                return QString("--");
}

Qt::PenCapStyle getPenCapStyleFromQString(const QString& style)
{
    if(style == "Square")       return Qt::SquareCap;
    else if(style == "Flat")    return Qt::FlatCap;
    else /* Bold */             return Qt::RoundCap;
}

QString getPenJoinStyleAsQString(Qt::PenJoinStyle style)
{
    if(style == Qt::MiterJoin)          return QString("Miter");
    else if(style == Qt::BevelJoin)     return QString("Bevel");
    else if(style == Qt::RoundJoin)     return QString("Round");
    else                                return QString("--");
}

Qt::PenJoinStyle getPenJoinStyleFromQString(const QString& style)
{
    if(style == "Miter")        return Qt::MiterJoin;
    else if(style == "Bevel")   return Qt::BevelJoin;
    else /* Round */            return Qt::RoundJoin;
}

QString getPenStyleAsQString(Qt::PenStyle style)
{
    if(style == Qt::SolidLine)              return QString("Solid");
    else if(style == Qt::DashLine)          return QString("Dashed");
    else if(style == Qt::DotLine)           return QString("Dotted");
    else if(style == Qt::DashDotLine)       return QString("Dashed/Dotted");
    else if(style == Qt::DashDotDotLine)    return QString("Dashed/Dotted/Dotted");
    else                                    return QString("--");
}

Qt::PenStyle getPenStyleFromQString(const QString& style)
{
    if(style == "Solid")                return Qt::SolidLine;
    else if(style == "Dashed")          return Qt::DashLine;
    else if(style == "Dotted")          return Qt::DotLine;
    else if(style == "Dashed/Dotted")   return Qt::DashDotLine;
    else /* Dashed/Dotted/Dotted */     return Qt::DashDotDotLine;
}

QString getTextAlignmentAsQString(Qt::AlignmentFlag alignment)
{
    if(alignment == Qt::AlignLeft)          return QString("Left");
    else if(alignment == Qt::AlignRight)    return QString("Right");
    else if(alignment == Qt::AlignTop)      return QString("Top");
    else if(alignment == Qt::AlignBottom)   return QString("Bottom");
    else if(alignment == Qt::AlignCenter)   return QString("Center");
    else                                    return QString("--");
}

QString getQColorAsQString(QColor color)
{
    if(color == QColor("white"))            return QString("White");
    else if(color == QColor("black"))       return QString("Black");
    else if(color == QColor("red"))         return QString("Red");
    else if(color == QColor("green"))       return QString("Green");
    else if(color == QColor("blue"))        return QString("Blue");
    else if(color == QColor("cyan"))        return QString("Cyan");
    else if(color == QColor("magenta"))     return QString("Magenta");
    else if(color == QColor("yellow"))      return QString("Yellow");
    else if(color == QColor("gray"))        return QString("Gray");
    else                                    return QString("--");
}

Qt::AlignmentFlag getTextAlignmentFromQString(const QString& alignment)
{
    if(alignment == "Left")         return Qt::AlignLeft;
    else if(alignment == "Right")   return Qt::AlignRight;
    else if(alignment == "Top")     return Qt::AlignTop;
    else if(alignment == "Bottom")  return Qt::AlignBottom;
    else /* Center */               return Qt::AlignCenter;
}

QString getTextStringTrimmed(const QString& str)
{
    if(str.length() > 30)
    {
        std::string tmp = str.toUtf8().constData();
        tmp = tmp.substr(0, 27);
        tmp += "...";
        return QString(tmp.c_str());
    }

    return QString(str);
}

bool isNumber(const QString& str)
{
    if(str.isEmpty())
        return false;

    for(int i = 0; i < str.length(); ++i)
    {
        if(!str[i].isDigit())
            return false;
    }

    return true;
}

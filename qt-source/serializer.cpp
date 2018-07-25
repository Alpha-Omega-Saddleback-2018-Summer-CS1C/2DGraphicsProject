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
    File: serializer.cpp

    Saves the shape into a text file
 */

#include "serializer.h"
#include "textbox.h"

using namespace shape;

/*
 *  Helper functions
 */

std::string getBrushStyleAsStdString(Qt::BrushStyle style)
{
    if(style == Qt::NoBrush)             return "NoBrush";
    else if(style == Qt::SolidPattern)   return "SolidPattern";
    else if(style == Qt::HorPattern)     return "HorPattern";
    else /* Qt::VerPattern */            return "VerPattern";
}

std::string getFontStyleAsStdString(QFont::Style style)
{
    if(style == QFont::StyleNormal)         return "StyleNormal";
    else if(style == QFont::StyleItalic)    return "StyleItalic";
    else /* QFont::StyleOblique */          return "StyleOblique";
}

std::string getFontWeightAsStdString(int weight)
{
    if(weight == QFont::Thin)           return "Thin";
    else if(weight == QFont::Light)     return "Light";
    else if(weight == QFont::Normal)    return "Normal";
    else /* QFont::Bold */              return "Bold";
}

std::string getPenCapStyleAsStdString(Qt::PenCapStyle style)
{
    if(style == Qt::SquareCap)      return "SquareCap";
    else if(style == Qt::FlatCap)   return "FlatCap";
    else /* Qt::RoundCap */         return "RoundCap";
}

std::string getPenJoinStyleAsStdString(Qt::PenJoinStyle style)
{
    if(style == Qt::MiterJoin)          return "MiterJoin";
    else if(style == Qt::BevelJoin)     return "BevelJoin";
    else /* Qt::RoundJoin */            return "RoundJoin";
}

std::string getPenStyleAsStdString(Qt::PenStyle style)
{
    if(style == Qt::SolidLine)          return "SolidLine";
    else if(style == Qt::DashLine)      return "DashLine";
    else if(style == Qt::DotLine)       return "DotLine";
    else if(style == Qt::DashDotLine)   return "DashDotLine";
    else /* Qt::DashDotDotLine */       return "DashDotDotLine";
}

std::string getTextAlignmentAsStdString(Qt::AlignmentFlag style)
{
    if(style == Qt::AlignLeft)          return "AlignLeft";
    else if(style == Qt::AlignRight)    return "AlignRight";
    else if(style == Qt::AlignTop)      return "AlignTop";
    else if(style == Qt::AlignBottom)   return "AlignBottom";
    else /* Qt::AlignCenter */          return "AlignCenter";
}

std::string getQColorAsStdString(QColor color)
{
    if(color == QColor("white"))            return "white";
    else if(color == QColor("black"))       return "black";
    else if(color == QColor("red"))         return "red";
    else if(color == QColor("green"))       return "green";
    else if(color == QColor("blue"))        return "blue";
    else if(color == QColor("cyan"))        return "cyan";
    else if(color == QColor("magenta"))     return "magenta";
    else if(color == QColor("yellow"))      return "yellow";
    else /* QColor("gray") */               return "gray";
}

/*
 *  Class functions
 */

void Serializer::close()
{
    if(mOutputFile.is_open())
    {
        mOutputFile.close();
        mOutputFilePath.clear();
    }
}

bool Serializer::loadFile(const std::string& filePath)
{
    mOutputFile.open(filePath, std::ios_base::trunc);
    mOutputFilePath = filePath;

    return mOutputFile.is_open();
}

void Serializer::save(Vector<Shape*>& shapeVector)
{
    for(Vector<Shape*>::iterator it = shapeVector.begin(); it != shapeVector.end(); ++it)
    {
        Vector<int> dimensions = (*it)->getDimensions();

        mOutputFile << "ShapeId: " << (*it)->getID() << std::endl;
        mOutputFile << "ShapeType: " << (*it)->getTypeAsQString().toUtf8().data() << std::endl;
        mOutputFile << "ShapeDimensions: ";

        for(Vector<int>::iterator it2 = dimensions.begin(); it2 != (dimensions.end() - 1); ++it2)
            mOutputFile << *it2 << ", ";
        mOutputFile << dimensions[dimensions.size() - 1] << std::endl;

        if((*it)->getType() == Shape::TEXTBOX)
        {
            TextBox* text = dynamic_cast<TextBox*>(*it);

            mOutputFile << "TextString: " << text->getText().toUtf8().data() << std::endl;
            mOutputFile << "TextColor: " << getQColorAsStdString(text->getPen().color()) << std::endl;
            mOutputFile << "TextAlignment: " << getTextAlignmentAsStdString(text->getAlignment()) << std::endl;
            mOutputFile << "TextPointSize: " << text->getFont().pointSize() << std::endl;
            mOutputFile << "TextFontFamily: " << text->getFont().family().toUtf8().data() << std::endl;
            mOutputFile << "TextFontStyle: " << getFontStyleAsStdString(text->getFont().style()) << std::endl;
            mOutputFile << "TextFontWeight: " << getFontWeightAsStdString(text->getFont().weight()) << std::endl;
        }
        else
        {
            mOutputFile << "PenColor: " << getQColorAsStdString((*it)->getPen().color()) << std::endl;
            mOutputFile << "PenWidth: " << (*it)->getPen().width() << std::endl;
            mOutputFile << "PenStyle: " << getPenStyleAsStdString((*it)->getPen().style()) << std::endl;
            mOutputFile << "PenCapStyle: " << getPenCapStyleAsStdString((*it)->getPen().capStyle()) << std::endl;
            mOutputFile << "PenJoinStyle: " << getPenJoinStyleAsStdString((*it)->getPen().joinStyle()) << std::endl;

            if((*it)->getType() != Shape::LINE && (*it)->getType() != Shape::POLYLINE)
            {
                mOutputFile << "BrushColor: " << getQColorAsStdString((*it)->getBrush().color()) << std::endl;
                mOutputFile << "BrushStyle: " << getBrushStyleAsStdString((*it)->getBrush().style()) << std::endl;
            }
        }

        if(*it != shapeVector[shapeVector.size() - 1])
            mOutputFile << std::endl;
    }
}

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
    File: parser.cpp

    Reads input file and creates shapes
 */

#include "parser.h"

void Parser::close()
{
    if(mInputFile.is_open())
    {
        mInputFile.close();
        mInputFilePath.clear();
        mErrorList.clear();
    }
}

bool Parser::loadFile(const std::string& filePath)
{
    mInputFile.open(filePath);
    mInputFilePath = filePath;

    if(mInputFile.is_open())
        return true;
    else
        return false;
}

bool Parser::parse(Vector<Shape*>& shapeVector)
{
    if(!mInputFile.is_open())
        return false;

    std::string inputLine;
    size_t lineNum = 1;

    while(std::getline(mInputFile, inputLine))
    {
        if(inputLine.empty())
        {
            inputLine.clear();
            ++lineNum;
            continue;
        }

        size_t loc = inputLine.find(':');
        if(loc == std::string::npos)
        {
            mErrorList.push_back("Expected the format \"<key> : <value>\" (Line: " + std::to_string(lineNum) + " \"" + inputLine + "\")");
            inputLine.clear();
            ++lineNum;
            continue;
        }

        std::string key = trim_leading_ending(inputLine.substr(0, loc));
        std::string value = trim_leading_ending(inputLine.substr(loc + 1, inputLine.size() - loc - 1));

        setKeyValue(shapeVector, key, value, inputLine, lineNum);

        inputLine.clear();
        ++lineNum;
    }

    if(mShapeInfo.shapeID != 0)
        addShape(shapeVector);

    if(!mErrorList.empty())
    {
        std::cout << "In file " << mInputFilePath << ":" << std::endl;
        for(std::vector<std::string>::iterator it = mErrorList.begin(); it != mErrorList.end(); ++it)
            std::cout << "\t" << *it << std::endl;
        return false;
    }

    return true;
}

/*
 *  Helper functions
 */

 void Parser::addShape(Vector<Shape*>& shapeVector)
 {
    if(mShapeInfo.shapeType == "Line")
    {
        Line* line = new Line();
        QPen pen;

        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        line->setID(mShapeInfo.shapeID);
        line->setPoints(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1],
            mShapeInfo.shapeDimensions[2], mShapeInfo.shapeDimensions[3]);
        line->setPen(pen);

        shapeVector.push_back(line);
    }
    else if(mShapeInfo.shapeType == "Polyline")
    {
        Polyline* polyline = new Polyline();
        QPen pen;

        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        polyline->setID(mShapeInfo.shapeID);
        polyline->setPointData(mShapeInfo.shapeDimensions, mShapeInfo.shapeDimensionCount / 2);
        polyline->setPen(pen);

        shapeVector.push_back(polyline);
    }
    else if(mShapeInfo.shapeType == "Polygon")
    {
        Polygon* polygon = new Polygon();
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        polygon->setID(mShapeInfo.shapeID);
        polygon->setPointData(mShapeInfo.shapeDimensions, mShapeInfo.shapeDimensionCount / 2);
        polygon->setPen(pen);
        polygon->setBrush(brush);

        shapeVector.push_back(polygon);
    }
    else if(mShapeInfo.shapeType == "Rectangle")
    {
        Rectangle* rectangle = new Rectangle();
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        rectangle->setID(mShapeInfo.shapeID);
        rectangle->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        rectangle->setDimensions(mShapeInfo.shapeDimensions[2], mShapeInfo.shapeDimensions[3]);
        rectangle->setPen(pen);
        rectangle->setBrush(brush);

        shapeVector.push_back(rectangle);
    }
    else if(mShapeInfo.shapeType == "Square")
    {
        Square* square = new Square();
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        square->setID(mShapeInfo.shapeID);
        square->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        square->setSide(mShapeInfo.shapeDimensions[2]);
        square->setPen(pen);
        square->setBrush(brush);

        shapeVector.push_back(square);
    }
    else if(mShapeInfo.shapeType == "Ellipse")
    {
        Ellipse* ellipse = new Ellipse();
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        ellipse->setID(mShapeInfo.shapeID);
        ellipse->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        ellipse->setRadii(mShapeInfo.shapeDimensions[2], mShapeInfo.shapeDimensions[3]);
        ellipse->setPen(pen);
        ellipse->setBrush(brush);

        shapeVector.push_back(ellipse);
    }
    else if(mShapeInfo.shapeType == "Circle")
    {
        Circle* circle = new Circle();
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(mShapeInfo.penColor));
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));

        brush.setColor(QColor(mShapeInfo.brushColor));
        brush.setStyle(static_cast<Qt::BrushStyle>(mShapeInfo.brushStyle));

        circle->setID(mShapeInfo.shapeID);
        circle->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        circle->setRadius(mShapeInfo.shapeDimensions[2]);
        circle->setPen(pen);
        circle->setBrush(brush);

        shapeVector.push_back(circle);
    }
    else if(mShapeInfo.shapeType == "Text")
    {
        TextBox* text = new TextBox();
        QPen pen;
        QFont font;

        pen.setColor(QColor(mShapeInfo.textColor));

        font.setPointSize(mShapeInfo.textPointSize);
        font.setFamily(mShapeInfo.textFontFamily);
        font.setStyle(static_cast<QFont::Style>(mShapeInfo.textFontStyle));
        font.setWeight(mShapeInfo.textFontWeight);

        text->setID(mShapeInfo.shapeID);
        text->setPosition(mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1]);
        text->setDimensions(mShapeInfo.shapeDimensions[2], mShapeInfo.shapeDimensions[3]);
        text->setText(mShapeInfo.textString);
        text->setAlignment(static_cast<Qt::AlignmentFlag>(mShapeInfo.textAlignment));
        text->setPen(pen);
        text->setFont(font);

        shapeVector.push_back(text);
    }
    else
    {
        mErrorList.push_back("Missing shape type. (Shape Creator [ShapeID = " + std::to_string(mShapeInfo.shapeID) + "])");
    }
 }

int* Parser::extractDimensions(const std::string& source, int& size, const std::string& line, size_t lineNumber)
{
    std::string value;
    size_t low = 0;
    size_t i = 0;
    int* dest = nullptr;
    int* tmp = nullptr;

    for(; i < source.length(); ++i)
    {
        if(std::isdigit(source[i]))
        {
            continue;
        }
        else if(source[i] == ',')
        {
            value = source.substr(low, i - low);

            if(dest != nullptr)
            {
                tmp = dest;
                dest = new int[size + 1];

                for(int j = 0; j < size; ++j)
                    dest[j] = tmp[j];
                delete[] tmp;
                dest[size] = std::stoi(value);
                low = i + 1;
                ++size;
            }
            else
            {
                dest = new int[1];
                dest[0] = std::stoi(value);
                low = i + 1;
                size = 1;
            }
        }
        else
        {
            mErrorList.push_back("Unexpected character (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }

    /* Insert final value */
    value = source.substr(low, i - low);
    tmp = dest;
    dest = new int[size + 1];

    for(int j = 0; j < size; ++j)
        dest[j] = tmp[j];
    delete[] tmp;
    dest[size] = std::stoi(value);
    ++size;

    return dest;
}

bool Parser::setInteger(int& dest, const std::string& source) const
{
    for(size_t i = 0; i < source.length(); ++i)
    {
        if(!std::isdigit(source[i]))
            return false;
    }

    dest = std::stoi(source);
    return true;
}

void Parser::setKeyValue(Vector<Shape*>& shapeVector, const std::string& key, const std::string& value, const std::string& line, size_t lineNumber)
{
    if(key == "BrushColor")
    {
        if((value == "white") ||
            (value == "black") ||
            (value == "red") ||
            (value == "green") ||
            (value == "blue") ||
            (value == "cyan") ||
            (value == "magenta") ||
            (value == "yellow") ||
            (value == "gray"))
            mShapeInfo.brushColor = QString::fromStdString(value);
        else
            mErrorList.push_back("Unexpected value. Try \"white\", \"black\", \"red\", \"green\", \"blue\", \"cyan\", \"magenta\", " +
                std::string("\"yellow\", or \"gray\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "BrushStyle")
    {
        if(value == "NoBrush")
            mShapeInfo.brushStyle = Qt::NoBrush;
        else if(value == "SolidPattern")
            mShapeInfo.brushStyle = Qt::SolidPattern;
        else if(value == "HorPattern")
            mShapeInfo.brushStyle = Qt::HorPattern;
        else if(value == "VerPattern")
            mShapeInfo.brushStyle = Qt::VerPattern;
        else
            mErrorList.push_back("Unexpected value. Try \"NoBrush\", \"SolidPattern\", \"HorPattern\", or \"VerPattern\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "PenCapStyle")
    {
        if(value == "SquareCap")
            mShapeInfo.penCapStyle = Qt::SquareCap;
        else if(value == "FlatCap")
            mShapeInfo.penCapStyle = Qt::FlatCap;
        else if(value == "RoundCap")
            mShapeInfo.penCapStyle = Qt::RoundCap;
        else
            mErrorList.push_back("Unexpected value. Try \"SquareCap\", \"FlatCap\", or \"RoundCap\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "PenColor")
    {
        mShapeInfo.penColor = QString::fromStdString(value);
    }
    else if(key == "PenJoinStyle")
    {
        if(value == "MiterJoin")
            mShapeInfo.penJoinStyle = Qt::MiterJoin;
        else if(value == "BevelJoin")
            mShapeInfo.penJoinStyle = Qt::BevelJoin;
        else if(value == "RoundJoin")
            mShapeInfo.penJoinStyle = Qt::RoundJoin;
        else
            mErrorList.push_back("Unexpected value. Try \"MiterJoin\", \"BevelJoin\", or \"RoundJoin\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "PenStyle")
    {
        if(value == "SolidLine")
            mShapeInfo.penStyle = Qt::SolidLine;
        else if(value == "DashLine")
            mShapeInfo.penStyle = Qt::DashLine;
        else if(value == "DotLine")
            mShapeInfo.penStyle = Qt::DotLine;
        else if(value == "DashDotLine")
            mShapeInfo.penStyle = Qt::DashDotLine;
        else if(value == "DashDotDotLine")
            mShapeInfo.penStyle = Qt::DashDotDotLine;
        else
            mErrorList.push_back("Unexpected value. Try \"SolidLine\", \"DashLine\", \"DotLine\", \"DashDotLine\", or " +
                std::string("\"DashDotDotLine\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "PenWidth")
    {
        if(setInteger(mShapeInfo.penWidth, value))
        {
            if(mShapeInfo.penWidth < 0 || mShapeInfo.penWidth > 20)
            {
                mErrorList.push_back("Must be an integer between 0 and 20, inclusive (Line: " + std::to_string(lineNumber) +
                    " \"" + line + "\")");
                mShapeInfo.penWidth = -1;
            }
        }
        else
        {
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "ShapeDimensions")
    {
        int* array = nullptr;

        if(mShapeInfo.shapeType == "Line")
        {
           array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
           if(mShapeInfo.shapeDimensionCount == 4)
               mShapeInfo.shapeDimensions = array;
           else
               mErrorList.push_back("Expected four values [x1, y1, x2, y2] (Line: " +
                   std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Polyline")
        {
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(!(mShapeInfo.shapeDimensionCount % 2))
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Odd number of values. Expected coordinates pairs. [x1, y1, x2, y2, ...] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Polygon")
        {
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(!(mShapeInfo.shapeDimensionCount % 2))
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Odd number of values. Expected coordinates pairs. [x1, y1, x2, y2, ...] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Rectangle")
        {
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(mShapeInfo.shapeDimensionCount == 4)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected four values [x, y, width, height] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Square")
        {
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(mShapeInfo.shapeDimensionCount == 3)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected three values [x, y, side] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Circle")
        {
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(mShapeInfo.shapeDimensionCount == 3)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected three values [x, y, radius] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Ellipse")
        {
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(mShapeInfo.shapeDimensionCount == 4)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected three values [x, y, rx, ry] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Text")
        {
            array = extractDimensions(trim_whitespace(value), mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(mShapeInfo.shapeDimensionCount == 4)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected four values [x, y, width, height] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else
        {
            mErrorList.push_back("Shape type needs to be defined before defining dimensions (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "ShapeId")
    {
        if(mShapeInfo.shapeID > 0)
        {
            addShape(shapeVector);
            mShapeInfo.reset();
        }

        if(!setInteger(mShapeInfo.shapeID, value))
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "ShapeType")
    {
        if((value == "Line") ||
           (value == "Polyline") ||
           (value == "Polygon") ||
           (value == "Rectangle") ||
           (value == "Square") ||
           (value == "Circle") ||
           (value == "Ellipse") ||
           (value == "Text"))
            mShapeInfo.shapeType = QString::fromStdString(value);
        else
            mErrorList.push_back("Unexpected value. Try \"Line\", \"Polyline\", \"Polygon\", \"Rectangle\", \"Square\", \"Circle\", " +
                std::string("\"Ellipse\", \"Text\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "TextAlignment")
    {
        if(value == "AlignLeft")
            mShapeInfo.textAlignment |= Qt::AlignLeft;
        else if(value == "AlignRight")
            mShapeInfo.textAlignment |= Qt::AlignRight;
        else if(value == "AlignRight")
            mShapeInfo.textAlignment |= Qt::AlignTop;
        else if(value == "AlignBottom")
            mShapeInfo.textAlignment |= Qt::AlignBottom;
        else if(value == "AlignCenter")
            mShapeInfo.textAlignment |= Qt::AlignCenter;
        else
            mErrorList.push_back("Unexpected value. Try \"AlignLeft\", \"AlignRight\", \"AlignTop\", \"AlignBottom\", or " +
                std::string("\"AlignCenter\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");

    }
    else if(key == "TextColor")
    {
        if((value == "white") ||
            (value == "black") ||
            (value == "red") ||
            (value == "green") ||
            (value == "blue") ||
            (value == "cyan") ||
            (value == "magenta") ||
            (value == "yellow") ||
            (value == "gray"))
            mShapeInfo.textColor = QString::fromStdString(value);
        else
            mErrorList.push_back("Unexpected value. Try \"white\", \"black\", \"red\", \"green\", \"blue\", \"cyan\", \"magenta\", " +
                std::string("\"yellow\", or \"gray\" (Line: ") + std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "TextFontFamily")
    {
        if((value == "Comic Sans MS") ||
            (value == "Courier") ||
            (value == "Helvetica") ||
            (value == "Times"))
            mShapeInfo.textColor = QString::fromStdString(value);
        else
            mErrorList.push_back("Unexpected value. Try \"Courier Sans MS\", \"Courier\", \"Helvetica\", or \"Times\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "TextFontStyle")
    {
        if(value == "StyleNormal")
            mShapeInfo.textFontStyle = QFont::StyleNormal;
        else if(value == "StyleItalic")
            mShapeInfo.textFontStyle = QFont::StyleItalic;
        else if(value == "StyleOblique")
            mShapeInfo.textFontStyle = QFont::StyleOblique;
        else
            mErrorList.push_back("Unexpected value. Try \"StyleNormal\", \"StyleItalic\", or \"StyleOblique\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "TextFontWeight")
    {
        if(value == "Thin")
            mShapeInfo.textFontWeight = QFont::Thin;
        else if(value == "Light")
            mShapeInfo.textFontWeight = QFont::Light;
        else if(value == "Normal")
            mShapeInfo.textFontWeight = QFont::Normal;
        else if(value == "Bold")
            mShapeInfo.textFontWeight = QFont::Bold;
        else
            mErrorList.push_back("Unexpected value. Try \"Thin\", \"Light\", \"Normal\", or \"Bold\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "TextPointSize")
    {
        if(setInteger(mShapeInfo.textPointSize, value))
        {
            if(mShapeInfo.textPointSize <= 0 || mShapeInfo.textPointSize > 50)
            {
                mErrorList.push_back("Must be an integer greater than 0 and less than or equal to 50 (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
                mShapeInfo.penWidth = -1;
            }
        }
        else
        {
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
        }
    }
    else if(key == "TextString")
    {
        mShapeInfo.textString = QString::fromStdString(value);
    }
    else
    {
        mErrorList.push_back("Unexpected key (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
    }
}

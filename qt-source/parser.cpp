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
    std::string copyInput;
    size_t lineNum = 1;

    while(std::getline(mInputFile, inputLine))
    {
        copyInput = inputLine;
        inputLine.erase(std::remove_if(inputLine.begin(),
                                       inputLine.end(),
                                       [](unsigned char x) {return (x == ' ') || (x == '\t');}),
                        inputLine.end());
        if(inputLine.empty())
        {
            inputLine.clear();
            ++lineNum;
            continue;
        }

        size_t loc = inputLine.find(':');
        if(loc == std::string::npos)
        {
            mErrorList.push_back("Expected the format \"<key> : <value>\" (Line: " + std::to_string(lineNum) + " \"" + copyInput + "\")");
            inputLine.clear();
            copyInput.clear();
            ++lineNum;
            continue;
        }

        std::string key = inputLine.substr(0, loc);
        std::string value = inputLine.substr(loc + 1, inputLine.size() - loc - 1);
        setKeyValue(shapeVector, key, value, copyInput, lineNum);

        inputLine.clear();
        copyInput.clear();
        ++lineNum;
    }

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
        Line* line = new Line(mShapeInfo.shapeID,
                mShapeInfo.shapeDimensions[0], mShapeInfo.shapeDimensions[1],
                mShapeInfo.shapeDimensions[2], mShapeInfo.shapeDimensions[3]);

        QPen pen;
        pen.setColor(mShapeInfo.penColor);
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));
        line->setPen(pen);

        shapeVector.push_back(line);
    }
    else if(mShapeInfo.shapeType == "Polyline")
    {
        Polyline* polyline = new Polyline(mShapeInfo.shapeID, mShapeInfo.shapeDimensions, mShapeInfo.shapeDimensionCount / 2);

        QPen pen;
        pen.setColor(mShapeInfo.penColor);
        pen.setWidth(mShapeInfo.penWidth);
        pen.setStyle(static_cast<Qt::PenStyle>(mShapeInfo.penStyle));
        pen.setCapStyle(static_cast<Qt::PenCapStyle>(mShapeInfo.penCapStyle));
        pen.setJoinStyle(static_cast<Qt::PenJoinStyle>(mShapeInfo.penJoinStyle));
        polyline->setPen(pen);

        shapeVector.push_back(polyline);
    }
    else if(mShapeInfo.shapeType == "Polygon")
    {

    }
    else if(mShapeInfo.shapeType == "Rectangle")
    {

    }
    else if(mShapeInfo.shapeType == "Square")
    {

    }
    else if(mShapeInfo.shapeType == "Ellipse")
    {

    }
    else if(mShapeInfo.shapeType == "Circle")
    {

    }
    else if(mShapeInfo.shapeType == "Text")
    {

    }
    else
    {
        mErrorList.push_back("Missing shape type! (Shape Creator [ShapeID = " + std::to_string(mShapeInfo.shapeID) + "])");
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
        mShapeInfo.brushColor = QString::fromStdString(value);
    }
    else if(key == "BrushStyle")
    {
        mShapeInfo.brushStyle = QString::fromStdString(value);
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
            mErrorList.push_back("Invalid value. Expected \"SquareCap\", \"FlatCap\", or \"RoundCap\" (Line: " +
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
            mErrorList.push_back("Invalid value. Expected \"MiterJoin\", \"BevelJoin\", or \"RoundJoin\" (Line: " +
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
            mErrorList.push_back("Invalid value. Expected \"SolidLine\", \"DashLine\", \"DotLine\", \"DashDotLine\", or \"DashDotDotLine\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");

    }
    else if(key == "PenWidth")
    {
        if(!setInteger(mShapeInfo.penWidth, value))
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "ShapeDimensions")
    {
        int* array = nullptr;

        if(mShapeInfo.shapeType == "Line")
        {
           array = extractDimensions(value, mShapeInfo.shapeDimensionCount, line, lineNumber);
           if(mShapeInfo.shapeDimensionCount == 4)
               mShapeInfo.shapeDimensions = array;
           else
               mErrorList.push_back("Expected four values [x1, y1, x2, y2] (Line: " +
                   std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Polyline")
        {
            array = extractDimensions(value, mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(!(mShapeInfo.shapeDimensionCount % 2))
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Odd number of values. Expected coordinates pairs. [x1, y1, x2, y2, ...] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Polygon")
        {
            array = extractDimensions(value, mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(!(mShapeInfo.shapeDimensionCount % 2))
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Odd number of values. Expected coordinates pairs. [x1, y1, x2, y2, ...] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Rectangle")
        {
            array = extractDimensions(value, mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(mShapeInfo.shapeDimensionCount == 4)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected four values [x, y, width, height] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Square")
        {
            array = extractDimensions(value, mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(mShapeInfo.shapeDimensionCount == 3)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected three values [x, y, side] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Circle")
        {
            array = extractDimensions(value, mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(mShapeInfo.shapeDimensionCount == 3)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected three values [x, y, radius] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Ellipse")
        {
            array = extractDimensions(value, mShapeInfo.shapeDimensionCount, line, lineNumber);
            if(mShapeInfo.shapeDimensionCount == 4)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected three values [x, y, rx, ry] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Text")
        {
            array = extractDimensions(value, mShapeInfo.shapeDimensionCount, line, lineNumber);
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
        if(mShapeInfo.shapeID != 0)
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
            mErrorList.push_back("Unexpected value. Try \"Line\", \"\"Polyline\", \"Polygon\", \"Rectangle\", \"Ellipse\", \"Text\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "TextAlignment")
    {

    }
    else if(key == "TextColor")
    {
        mShapeInfo.textColor = QString::fromStdString(value);
    }
    else if(key == "TextFontFamily")
    {
        mShapeInfo.textFontFamily = QString::fromStdString(value);
    }
    else if(key == "TextFontStyle")
    {
        mShapeInfo.textFontStyle = QString::fromStdString(value);
    }
    else if(key == "TextFontWeight")
    {
        mShapeInfo.textFontWeight = QString::fromStdString(value);
    }
    else if(key == "TextPointSize")
    {
        if(!setInteger(mShapeInfo.textPointSize, value))
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
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

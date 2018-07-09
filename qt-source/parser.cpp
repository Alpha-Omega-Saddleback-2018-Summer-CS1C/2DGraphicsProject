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

bool Parser::parse(/* Pass vector here? */)
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
        setKeyValue(key, value, copyInput, lineNum);

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

int* Parser::extractDimensions(const std::string& source, size_t& size, const std::string& line, size_t lineNumber)
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

                for(size_t j = 0; j < size; ++j)
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

    for(size_t j = 0; j < size; ++j)
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

void Parser::setKeyValue(const std::string& key, const std::string& value, const std::string& line, size_t lineNumber)
{
    if(key == "BrushColor")
    {
        mShapeInfo.brushColor = value;
    }
    else if(key == "BrushStyle")
    {
        mShapeInfo.brushStyle = value;
    }
    else if(key == "PenCapStyle")
    {
        mShapeInfo.penCapStyle = value;
    }
    else if(key == "PenColor")
    {
        mShapeInfo.penColor = value;
    }
    else if(key == "PenJoinStyle")
    {
        mShapeInfo.penJoinStyle = value;
    }
    else if(key == "PenStyle")
    {
        mShapeInfo.penStyle = value;
    }
    else if(key == "PenWidth")
    {
        if(!setInteger(mShapeInfo.penWidth, value))
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "ShapeDimensions")
    {
        int* array = nullptr;
        size_t size = 0;

        if(mShapeInfo.shapeType == "Line")
        {
           array = extractDimensions(value, size, line, lineNumber);
           if(size == 4)
               mShapeInfo.shapeDimensions = array;
           else
               mErrorList.push_back("Expected four values [x1, y1, x2, y2] (Line: " +
                   std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Polyline")
        {
            array = extractDimensions(value, size, line, lineNumber);
            if(!(size % 2))
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Odd number of values. Expected coordinates pairs. [x1, y1, x2, y2, ...] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Polygon")
        {
            array = extractDimensions(value, size, line, lineNumber);
            if(!(size % 2))
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Odd number of values. Expected coordinates pairs. [x1, y1, x2, y2, ...] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Rectangle")
        {
            array = extractDimensions(value, size, line, lineNumber);
            if(size == 4)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected four values [x, y, width, height] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Square")
        {
            array = extractDimensions(value, size, line, lineNumber);
            if(size == 3)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected three values [x, y, side] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Circle")
        {
            array = extractDimensions(value, size, line, lineNumber);
            if(size == 3)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected three values [x, y, radius] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Ellipse")
        {
            array = extractDimensions(value, size, line, lineNumber);
            if(size == 4)
                mShapeInfo.shapeDimensions = array;
            else
                mErrorList.push_back("Expected three values [x, y, rx, ry] (Line: " +
                    std::to_string(lineNumber) + " \"" + line + "\")");
        }
        else if(mShapeInfo.shapeType == "Text")
        {
            array = extractDimensions(value, size, line, lineNumber);
            if(size == 4)
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
        // Add shape to vector
        // Check for duplicate shape ID

        mShapeInfo.reset();
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
            mShapeInfo.shapeType = value;
        else
            mErrorList.push_back("Unexpected value. Try \"Line\", \"\"Polyline\", \"Polygon\", \"Rectangle\", \"Ellipse\", \"Text\" (Line: " +
                std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "TextAlignment")
    {

    }
    else if(key == "TextColor")
    {
        mShapeInfo.textColor = value;
    }
    else if(key == "TextFontFamily")
    {
        mShapeInfo.textFontFamily = value;
    }
    else if(key == "TextFontStyle")
    {
        mShapeInfo.textFontStyle = value;
    }
    else if(key == "TextFontWeight")
    {
        mShapeInfo.textFontWeight = value;
    }
    else if(key == "TextPointSize")
    {
        if(!setInteger(mShapeInfo.textPointSize, value))
            mErrorList.push_back("Expected integer (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
    }
    else if(key == "TextString")
    {
        mShapeInfo.textString = value;
    }
    else
    {
        mErrorList.push_back("Unexpected key (Line: " + std::to_string(lineNumber) + " \"" + line + "\")");
    }
}

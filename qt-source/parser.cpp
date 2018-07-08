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

void Parser::closeFile()
{
    if(mInputFile.is_open())
        mInputFile.close();
}

bool Parser::loadFile(const std::string& filePath)
{
    mInputFile.open(filePath);

    if(mInputFile.is_open())
        return true;
    else
        return false;
}

bool Parser::parse(/* Pass vector here? */)
{
    if(!mInputFile.is_open())
    {
        mErrorList.insert({ 0, "File could not open!" });
    }

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
            mErrorList.insert({lineNum, "Expected a \':\'(Line " + std::to_string(lineNum) + " \"" + copyInput + "\")"});
            inputLine.clear();
            copyInput.clear();
            ++lineNum;
            continue;
        }

        std::string key = inputLine.substr(0, loc);
        std::string value = inputLine.substr(loc + 1, inputLine.size() - loc - 1);

        inputLine.clear();
        copyInput.clear();
        ++lineNum;
    }

    if(!mErrorList.empty())
    {
        for(auto it : mErrorList)
            std::cout << "[" << it.first << "] : " << it.second << std::endl;
        return false;
    }

    return true;
}

/*
 *  Helper functions
 */

bool Parser::setInteger(int& dest, const std::string& source)
{
    for(size_t i = 0; i < source.length(); ++i)
    {
        if(!std::isdigit(source[i]))
            return false;
    }

    dest = std::stoi(source);
    return true;
}

int Parser::setKeyValue(const std::string& key, const std::string& value, const std::string& line, size_t lineNumber)
{
    if(key == "BrushColor")
    {

    }
    else if(key == "BrushStyle")
    {

    }
    else if(key == "PenCapStyle")
    {

    }
    else if(key == "PenColor")
    {

    }
    else if(key == "PenJoinStyle")
    {

    }
    else if(key == "PenStyle")
    {

    }
    else if(key == "PenWidth")
    {

    }
    else if(key == "ShapeDimensions")
    {

    }
    else if(key == "ShapeId")
    {
        mShapeInfo.reset();
        if(!setInteger(mShapeInfo.shapeID, value))
            mErrorList.insert({lineNumber, "Expected integer (Line " + std::to_string(lineNumber) + " \"" + line + "\")"});
    }
    else if(key == "ShapeType")
    {

    }
    else if(key == "TextAlignment")
    {

    }
    else if(key == "TextColor")
    {

    }
    else if(key == "TextFontFamily")
    {

    }
    else if(key == "TextFontStyle")
    {

    }
    else if(key == "TextFontWeight")
    {

    }
    else if(key == "TextPointSize")
    {

    }
    else if(key == "TextString")
    {

    }
    else
    {
        return 0;
    }

    return 2;
}

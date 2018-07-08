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
    File: parser.h

    Reads input file and creates shapes
 */

#ifndef PARSER_H
#define PARSER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

/* Parser manager */
class Parser
{
private:

    /* Saves shape information */
    struct ShapeInfo
    {
        ShapeInfo()
        {
            reset();
        }

        void reset()
        {
            brushColor.clear();
            brushStyle.clear();
            penCapStyle.clear();
            penColor.clear();
            penJoinStyle.clear();
            penWidth = 0;
            shapeID = 0;
            shapeType.clear();
            textAlignment.clear();
            textColor.clear();
            textFontFamily.clear();
            textFontStyle.clear();
            textFontWeight.clear();
            textPointSize = 0;
            textString.clear();

            if(shapeDimensions != nullptr)
            {
                delete[] shapeDimensions;
                shapeDimensions = nullptr;
            }
        }

        std::string         brushColor;
        std::string         brushStyle;
        std::string         penCapStyle;
        std::string         penColor;
        std::string         penJoinStyle;
        std::string         penStyle;
        int                 penWidth;
        int*                shapeDimensions;
        int                 shapeID;
        std::string         shapeType;
        std::string         textAlignment;
        std::string         textColor;
        std::string         textFontFamily;
        std::string         textFontStyle;
        std::string         textFontWeight;
        int                 textPointSize;
        std::string         textString;
    };

public:
    Parser() {}
    ~Parser() { closeFile();}

    /* Closes the input file if it is open */
    void closeFile();

    /* Loads the file to be parsed. Returns true on success */
    bool loadFile(const std::string& filePath);

    /* Loads the file to be parsed. Returns true on success */
    bool parse(/* Pass vector here? */);

private:

    /* Sets the integer to the string if the string is an integer */
    bool setInteger(int& dest, const std::string& source);

    /* Sets a part of shape info. Returns 0 on failure, 1 on new shape, and 2 on normal data entry */
    int setKeyValue(const std::string& key, const std::string& value, const std::string& line, size_t lineNumber);

private:
    std::ifstream               mInputFile;
    ShapeInfo                   mShapeInfo;
    std::map<size_t, std::string>  mErrorList;
    // Parse object
    // Error handler

};

#endif

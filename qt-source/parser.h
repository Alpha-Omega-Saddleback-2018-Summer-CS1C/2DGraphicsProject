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
    File: parser.h

    Reads input file and creates shapes
 */

#ifndef PARSER_H
#define PARSER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <QString>

#include "custom_vector.h"
#include "shape.h"
#include "string_util.h"

/* Parser manager */
class Parser
{
private:

    /* Saves shape information */
    struct ShapeInfo
    {
        ShapeInfo()
        {
            brushStyle = -1;
            penCapStyle = -1;
            shapeDimensions = nullptr;
            penJoinStyle = -1;
            penStyle = -1;
            penWidth = -1;
            shapeDimensionCount = 0;
            shapeID = -1;
            textAlignment = 0;
            textFontStyle = -1;
            textFontWeight = 0;
            textPointSize = 0;
        }

        void reset()
        {
            brushColor.clear();
            brushStyle = -1;
            penCapStyle = -1;
            penColor.clear();
            penJoinStyle = -1;
            penStyle = -1;
            penWidth = -1;
            shapeDimensionCount = 0;
            shapeID = -1;
            shapeType.clear();
            textAlignment = 0;
            textColor.clear();
            textFontFamily.clear();
            textFontStyle = -1;
            textFontWeight = 0;
            textPointSize = 0;
            textString.clear();

            if(shapeDimensions != nullptr)
            {
                delete[] shapeDimensions;
                shapeDimensions = nullptr;
            }
        }

        QString         brushColor;
        int             brushStyle;
        int             penCapStyle;
        QString         penColor;
        int             penJoinStyle;
        int             penStyle;
        int             penWidth;
        int*            shapeDimensions;
        int             shapeDimensionCount;
        int             shapeID;
        QString         shapeType;
        int             textAlignment;
        QString         textColor;
        QString         textFontFamily;
        int             textFontStyle;
        int             textFontWeight;
        int             textPointSize;
        QString         textString;
    };

public:
    Parser() {}
    ~Parser() { close();}

    /* Closes the input file if it is open */
    void close();

    /* Loads the file to be parsed. Returns true on success */
    bool loadFile(const std::string& filePath);

    /* Loads the file to be parsed. Returns true on success */
    bool parse(Vector<Shape*>& shapeVector);

public:
    /* Functions used by MainWindow class to get QString values */

private:

    /* Adds a shape to the shape vector */
    void addShape(Vector<Shape*>& shapeVector);

    /* Parses ShapeDimension key/value. Returns the number of values extracted */
    int* extractDimensions(const std::string& source, int& size, const std::string& line, size_t lineNumber);

    /* Sets the integer to the string if the string is an integer */
    bool setInteger(int& dest, const std::string& source) const;

    /* Sets a part of shape info */
    void setKeyValue(Vector<Shape*>& shapeVector, const std::string& key, const std::string& value, const std::string& line, size_t lineNumber);

private:
    std::string                 mInputFilePath;
    std::ifstream               mInputFile;
    std::vector<std::string>    mErrorList;
    ShapeInfo                   mShapeInfo;
};

#endif

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

#include <string>
#include <fstream>

/* Parser manager */
class Parser
{
public:
    Parser() {}

    /* Loads the file to be parsed. Returns true on success */
    bool loadFile(const std::string& filePath);

    /* Loads the file to be parsed. Returns true on success */
    bool parse(/* Pass vector here? */);

private:

    // Parse object
    // Error handler

};

#endif

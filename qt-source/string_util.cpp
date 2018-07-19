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
    File: string_util.cpp

    Defines functions for the C++ Standard Library string
*/

#include "string_util.h"

const std::string WHITESPACE = " \n\r\t\f\v";

std::string trim_leading_whitespace(const std::string& str)
{
    size_t start = str.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : str.substr(start);
}

std::string trim_ending_whitespace(const std::string& str)
{
    size_t end = str.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string trim_leading_ending(const std::string& str)
{
    return trim_leading_whitespace(trim_ending_whitespace(str));
}

std::string trim_whitespace(const std::string& str)
{
    std::string ret = str;

    ret.erase(std::remove_if
    (
        ret.begin(), ret.end(),
        [](unsigned char x) {return (x == ' ') || (x == '\t');}),
        ret.end()
    );

    return ret;
}

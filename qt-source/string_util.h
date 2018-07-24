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
    File: string_util.h

    Defines functions for the C++ Standard Library string
*/

#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <algorithm>
#include <string>

/* Trims the leading whitespace */
std::string trim_leading_whitespace(const std::string& str);

/* Trims the ending whitespace */
std::string trim_ending_whitespace(const std::string& str);

/* Trims the leading and ending whitespace */
std::string trim_leading_ending(const std::string& str);

/* Trims whitespace in the entire string */
std::string trim_whitespace(const std::string& str);

#endif // STRING_UTIL_H

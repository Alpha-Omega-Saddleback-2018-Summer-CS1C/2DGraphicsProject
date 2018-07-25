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
    File: userserializer.h

    Saves the users into a text file
 */

#ifndef USERSERIALIZER_H
#define USERSERIALIZER_H

#include <fstream>
#include <iostream>
#include <string>
#include "custom_vector.h"
#include "userparser.h"

class UserSerializer
{
public:
    UserSerializer() {}
    ~UserSerializer() { close(); }

    /* Closes the input file if it is open */
    void close();

    /* Loads the file to be parsed. Returns true on success */
    bool loadFile(const std::string& filePath);

    /* Loads the file to be parsed. Returns true on success */
    void save(Vector<User>& userVector);

private:
    std::string     mOutputFilePath;
    std::ofstream   mOutputFile;
};

#endif // USERSERIALIZER_H

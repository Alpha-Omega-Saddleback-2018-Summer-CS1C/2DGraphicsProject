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
    File: serializer.h

    Saves the shape into a text file
 */

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <fstream>
#include <iostream>
#include <string>
#include "custom_vector.h"
#include "shape.h"

using shape::Shape;

/**	Writes shape data to a text file. */
class Serializer
{
public:
	/** Default constructor. */
    Serializer() {}
	
	/** Destructor. Closes the file. */
    ~Serializer() { close(); }

    /** Closes the input file if it is open. */
    void close();

    /** Loads the file to be parsed. Returns true on success. */
    bool loadFile(const std::string& filePath);

    /** Loads the file to be parsed. Returns true on success. */
    void save(Vector<Shape*>& shapeVector);

private:
    std::string     mOutputFilePath;
    std::ofstream   mOutputFile;
};

#endif // SERIALIZER_H

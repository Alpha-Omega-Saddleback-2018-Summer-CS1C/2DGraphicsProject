/*
 *  2D Graphics Modeler
 *  July 2018
 *
 *  David Epstein <DavidE92@live.com>
 *  Greg Graffius <ggraffius0@saddleback.edu>
 *  Justis Ketcham <justis.ketcham@gmail.com>
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
    File: userparser.h

    Parses a file to add users to a users list
 */

#ifndef USERPARSER_H
#define USERPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <QString>
#include "custom_vector.h"

/** Object that stores a users information */
struct User
{
	/** Stores username */
    QString mUsername;
	/** Stores password */
    QString mPassword;
	/** Stores privileges */
    bool mIsAdmin;
};

/** Parses a file that contains shape information and converts them into shapes
 * to be used by the program.
 */
class UserParser
{
public:
	/** Default constructor. */
    UserParser() {}
	
	/** Destructor. Closes the file. */
    ~UserParser() { close(); }

    /** Closes the input file if it is open. */
    void close();

    /** Loads an input file. */
    bool loadFile(const std::string& filePath);

    /** Parses the input file. */
    bool parse(Vector<User>& userVector);

private:
    std::string                 mInputFilePath;
    std::ifstream               mInputFile;
};

#endif // USERSPARSER_H

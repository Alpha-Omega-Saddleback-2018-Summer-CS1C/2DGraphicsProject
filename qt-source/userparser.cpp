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
    File: userparser.cpp

    Parses a file to add users to a users list
 */

#include "userparser.h"

void UserParser::close()
{
    if(mInputFile.is_open())
    {
        mInputFile.close();
        mInputFilePath.clear();
    }
}

bool UserParser::loadFile(const std::string& filePath)
{
    mInputFile.open(filePath);
    mInputFilePath = filePath;

    return mInputFile.is_open();
}

bool UserParser::parse(Vector<User>& userVector)
{
    if(!mInputFile.is_open())
        return false;

    User user;
    std::string inputLine;
    int inputType = 0;

    while(mInputFile >> inputLine)
    {
        if(inputType == 0)
        {
            user.mUsername = inputLine.c_str();
            ++inputType;
        }
        else if(inputType == 1)
        {
            user.mPassword = inputLine.c_str();
            ++inputType;
        }
        else
        {
            if(inputLine == "0")        user.mIsAdmin = false;
            else if(inputLine == "1")   user.mIsAdmin = true;
            else                        return false;

            userVector.push_back(user);
            user.mUsername.clear();
            user.mPassword.clear();
            user.mIsAdmin = 0;
            inputType = 0;
        }
    }

    return true;
}

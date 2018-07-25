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
    File: userserializer.cpp

    Saves the users into a text file
 */


#include "userserializer.h"

void UserSerializer::close()
{
    if(mOutputFile.is_open())
    {
        mOutputFile.close();
        mOutputFilePath.clear();
    }
}

bool UserSerializer::loadFile(const std::string& filePath)
{
    mOutputFile.open(filePath, std::ios_base::trunc);
    mOutputFilePath = filePath;

    return mOutputFile.is_open();
}

void UserSerializer::save(Vector<User>& userVector)
{
    for(Vector<User>::iterator it = userVector.begin(); it != userVector.end(); ++it)
        mOutputFile << it->mUsername.toUtf8().data() << " " << it->mPassword.toUtf8().data() << " " <<
            ((it->mIsAdmin) ? (1) : (0)) << std::endl;
}

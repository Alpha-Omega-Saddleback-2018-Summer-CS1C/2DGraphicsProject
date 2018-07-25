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
    File: main.cpp

    Entry point of the program
 */

#include <QApplication>
#include <string>
#include <iostream>
#include "login.h"
#include "parser.h"
#include "custom_vector.h"
#include "serializer.h"
#include "shape.h"
#include "userparser.h"
#include "userserializer.h"

using namespace shape;

const std::string shapeFile = "shapes.txt";
const std::string userFile = "users.txt";

int main(int argc, char *argv[])
{
    Parser shapeParser;
    UserParser userParser;
    Serializer serializer;
    UserSerializer userSerializer;
    Vector<Shape*> shapeVector;
    Vector<User> userVector;

    if(!shapeParser.loadFile(shapeFile))
    {
        std::cout << "Couldn't load file \"" << shapeFile << "\"!" << std::endl;
        return 0;
    }

    if(!userParser.loadFile(userFile))
    {
        std::cout << "Couldn't load file \"" << userFile << "\"!" << std::endl;
        return 0;
    }

    if(!shapeParser.parse(shapeVector))
    {
        std::cout << "Parsing file \"" << shapeFile << "\"failed!" << std::endl;
        return 0;
    }

    if(!userParser.parse(userVector))
    {
        std::cout << "Parsing file \"" << userFile << "\"failed!" << std::endl;
        return 0;
    }

    std::cout << "File \"" << shapeFile << "\" loaded and parsed successfully." << std::endl;
    std::cout << "File \"" << userFile << "\" loaded and parsed successfully." << std::endl;
    shapeParser.close();
    userParser.close();

    QApplication a(argc, argv);
    Login w;
    w.passParams(&shapeVector, &userVector);
    w.show();

    if(a.exec())
        return 1;

    if(!serializer.loadFile(shapeFile))
    {
        std::cout << "Could not save \"" << shapeFile << "\"" << std::endl;
    }
    else
    {
        serializer.save(shapeVector);
        serializer.close();
        std::cout << "File \"" << shapeFile << "\" saved successfully" << std::endl;
    }

    if(!userSerializer.loadFile(userFile))
    {
        std::cout << "Could not save \"" << userFile << "\"" << std::endl;
    }
    else
    {
        userSerializer.save(userVector);
        userSerializer.close();
        std::cout << "File \"" << userFile << "\" saved successfully" << std::endl;
    }

    return 0;
}


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
    File: main.cpp

    Entry point of the program
 */

#include <QApplication>
#include <string>
#include <iostream>
#include "login.h"
#include "parser.h"
#include "custom_vector.h"
#include "shape.h"
//#include "secdialog.h"

const std::string file = "shapes.txt";

int main(int argc, char *argv[])
{
    Parser parser;
    Vector<Shape*> shapeVector;

    //
    // Parser
    //

    if(!parser.loadFile(file))
    {
        std::cout << "Couldn't load file \"" << file << "\"!" << std::endl;
        return 0;
    }

    if(!parser.parse(shapeVector))
    {
        std::cout << "Parsing failed!" << std::endl;
        return 0;
    }

    std::cout << "File \"" << file << "\" loaded and parsed successfully." << std::endl;
    parser.close();

    //
    // QApplication
    //

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


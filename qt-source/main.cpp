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
#include "mainwindow.h"
#include "parser.h"

const std::string file = "shapes.txt";

int main(int argc, char *argv[])
{
    Parser parser;

    if(parser.loadFile(file))
        std::cout << "File loaded." << std::endl;
    else
        std::cout << "File failed." << std::endl;
    if(parser.parse())
        std::cout << "File parsed." << std::endl;
    else
        std::cout << "Parsing failed." << std::endl;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	return 0;
}

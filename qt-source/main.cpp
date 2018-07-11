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
#include "custom_vector.h"

const std::string file = "shapes.txt";
/*
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

    return a.exec();
}

*/

int main(int argc, char *argv[])
{
    Vector<double> vector;
    vector.push_back(1.0);
    vector.push_back(2.0);
    vector.push_back(3.0);

    Vector<double> copy(vector);
    copy.push_back(4.0);
    copy.push_back(5.0);
    copy.push_back(6.0);
    copy.push_back(7.0);
    copy.push_back(8.0);
    copy.push_back(9.0);

    copy.insert(copy.begin() + 4, 3.14);
    copy.erase(copy.begin() + 4);

    std::cout << "[vector] <" << vector.size() << ", " << vector.capacity() << "> : ";
    for(Vector<double>::iterator it = vector.begin(); it != vector.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

   std::cout << "[copy] <" << copy.size() << ", " << copy.capacity() << "> : ";
    for(Vector<double>::iterator it = copy.begin(); it != copy.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}

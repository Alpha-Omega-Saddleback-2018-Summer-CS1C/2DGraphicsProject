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
    File: addshape.h

    Defines an "add shape" widget
 */

#include <QtWidgets>
#include "addshape.h"

AddShape::AddShape(QWidget *parent)
    : QWidget(parent)
{
    shapeHeaderLabel[0] = new QLabel("Shape ID:");
    shapeHeaderLabel[1] = new QLabel("Shape Type:");
    shapeIDTextEdit = new QLineEdit;

    shapeTypeComboBox = new QComboBox;
    shapeTypeComboBox->addItem("Line");
    shapeTypeComboBox->addItem("Polyine");
    shapeTypeComboBox->addItem("Polygon");
    shapeTypeComboBox->addItem("Rectangle");
    shapeTypeComboBox->addItem("Square");
    shapeTypeComboBox->addItem("Ellipse");
    shapeTypeComboBox->addItem("Circle");
    shapeTypeComboBox->addItem("Text");

    addShapeButton = new QPushButton("Add Shape");
    cancelButton = new QPushButton("Cancel");

    mainLayout = new QGridLayout;
    mainLayout->addWidget(shapeHeaderLabel[0], 0, 0, 1, 1);
    mainLayout->addWidget(shapeIDTextEdit, 0, 1, 1, 1);
    mainLayout->addWidget(shapeHeaderLabel[1], 1, 0, 1, 1);
    mainLayout->addWidget(shapeTypeComboBox, 1, 1, 1, 1);
    mainLayout->addWidget(addShapeButton, 100, 0, 1, 1);
    mainLayout->addWidget(cancelButton, 100, 1, 1, 1);

    setLayout(mainLayout);
    setWindowTitle("Shape Manager");
}

AddShape::~AddShape()
{
    delete mainLayout;

    delete shapeHeaderLabel[0];
    delete shapeHeaderLabel[1];
    delete shapeIDTextEdit;
    delete shapeTypeComboBox;

    delete addShapeButton;
    delete cancelButton;
}

void AddShape::passParams(Vector<Shape*>* shapes)
{
    shapeVector = shapes;
}

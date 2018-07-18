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
    File: mainwindow.cpp

    Defines a main window
 */

#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    renderArea = new RenderArea;

    addShapeButton = new QPushButton("Add Shape", this);
    editShapeButton = new QPushButton("Edit Shape", this);
    deleteShapeButton = new QPushButton("Delete Shape", this);

    shapeComboBox = new QComboBox;

    QGridLayout* leftSideLayout = new QGridLayout;
    leftSideLayout->addWidget(addShapeButton, 0, 0, 1, 1);
    leftSideLayout->addWidget(editShapeButton, 1, 0, 1, 1);
    leftSideLayout->addWidget(deleteShapeButton, 2, 0, 1, 1);
    leftSideLayout->setContentsMargins(100, 10, 100, 10);

    QGridLayout* rightSideLayout = new QGridLayout;
    rightSideLayout->setContentsMargins(100, 10, 100, 10);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0, 1, 2);
    mainLayout->addLayout(leftSideLayout, 1, 0, 1, 1);

    setLayout(mainLayout);
    setWindowTitle("Basic Drawing");
    setMinimumSize(1100, 700);
    setMaximumSize(1100, 700);
}

MainWindow::~MainWindow()
{
    delete renderArea;

    delete shapeComboBox;
    delete addShapeButton;
    delete editShapeButton;
    delete deleteShapeButton;
}

void MainWindow::shapeChanged()
{

}

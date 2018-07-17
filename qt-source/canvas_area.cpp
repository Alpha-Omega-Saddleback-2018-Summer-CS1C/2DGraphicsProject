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
    File: canvas_area.cpp

    Defines a widget that will be drawn on by QPainter
*/

#include "canvas_area.h"
#include "ui_canvas_area.h"

CanvasArea::CanvasArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CanvasArea)
{
    ui->setupUi(this);

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

CanvasArea::~CanvasArea()
{
    delete ui;
}

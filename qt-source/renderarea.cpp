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
    File: renderarea.cpp

    Defines a main window
 */

#include "renderarea.h"

RenderArea::RenderArea(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(1000, 500);
    setMaximumSize(1000, 500);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void RenderArea::addShapeVector(Vector<Shape*>* shapes)
{
    shapeVector = shapes;
    update();
}

void RenderArea::paintEvent(QPaintEvent* /* event */)
{
    for(Vector<Shape*>::iterator it = shapeVector->begin(); it != shapeVector->end(); ++it)
    {
        (*it)->getPainter().begin(this);
        (*it)->getPainter().setRenderHint(QPainter::Antialiasing, true);
        (*it)->getPainter().save();
        (*it)->draw();
        (*it)->getPainter().restore();
        (*it)->getPainter().end();
    }

    QPainter localPainter(this);
    localPainter.setPen(palette().dark().color());
    localPainter.setBrush(Qt::NoBrush);
    localPainter.drawRect(QRect(0, 0, width() - 1, height() -1 ));
}

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
    File: renderarea.h

    Defines a main window
 */

#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPen>
#include <QWidget>
#include "custom_vector.h"
#include "shape.h"

class RenderArea : public QWidget
{
public:
    RenderArea(QWidget* parent = 0);
    void addShapeVector(Vector<Shape*>* shapes);

public slots:

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Vector<Shape*>* shapeVector;
};

#endif // RENDERAREA_H

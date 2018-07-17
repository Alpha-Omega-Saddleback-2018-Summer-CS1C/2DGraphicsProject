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
    File: canvas_area.h

    Defines a widget that will be drawn on by QPainter
*/

#ifndef CANVAS_AREA_H
#define CANVAS_AREA_H

#include <QWidget>

namespace Ui {
class CanvasArea;
}

class CanvasArea : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasArea(QWidget* parent = 0);
    ~CanvasArea();

private:
    Ui::CanvasArea *ui;
};

#endif // CANVAS_H

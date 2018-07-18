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
    File: mainwindow.h

    Defines a main window
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "custom_vector.h"
#include "renderarea.h"
#include "shape.h"

/* Forward decleration */
class QPushButton;
class QComboBox;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(Vector<Shape*>* shapes = nullptr);
    ~MainWindow();

    void addShapes(Vector<Shape*>* shapes);

private slots:
    void shapeChanged();

private:
    RenderArea*     renderArea;
    QComboBox*      shapeComboBox;
    QPushButton*    addShapeButton;
    QPushButton*    editShapeButton;
    QPushButton*    deleteShapeButton;

    Vector<Shape*>* shapeVector;
};

#endif // MAINWINDOW_H

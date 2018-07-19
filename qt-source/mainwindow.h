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
#include "renderarea.h"
#include "usermanager.h"
#include "shape.h"
#include "custom_vector.h"

/* Forward decleration */
class QPushButton;
class QComboBox;
class QLabel;
class QGridLayout;

class MainWindow : public QWidget
{
    Q_OBJECT

    static const int shapeHeaderLabelCount = 4;
    static const int shapeDimensionLabelCount = 10;
    static const int shapeDescriptionLabelCount = 14;

public:
    MainWindow();
    ~MainWindow();

    void addShapes(Vector<Shape*>& shapes);

private slots:
    void updateShapeInfo();
    void createUserManager();

private:
    RenderArea*     renderArea;
    QGridLayout*    mainLayout;
    QGridLayout*    leftSideLayout;
    QGridLayout*    rightSideLayout;

    /* Left side */
    QLabel*         selectedShapeLabel;
    QComboBox*      shapeComboBox;
    QPushButton*    addShapeButton;
    QPushButton*    editShapeButton;
    QPushButton*    deleteShapeButton;
    QPushButton*    userManagerButton;

    /* Right-side */
    QLabel*         shapeHeaderLabels[shapeHeaderLabelCount];
    QLabel*         shapeDimensionLabels[shapeDimensionLabelCount];
    QLabel*         shapeDescriptionLabels[shapeDescriptionLabelCount];
    bool            isText;

    Vector<Shape*> shapeVector;
    UserManager* userManager;
};

#endif // MAINWINDOW_H

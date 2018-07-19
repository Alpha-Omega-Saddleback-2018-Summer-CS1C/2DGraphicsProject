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
class QLabel;
class QGridLayout;

class MainWindow : public QWidget
{
    Q_OBJECT

    static const int shapeDimensionLabelCount = 10;

public:
    MainWindow();
    ~MainWindow();

    void addShapes(Vector<Shape*>* shapes);

private slots:
    void shapeChanged();

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

    /* Right-side (general) */
    QLabel*         shapeIDLabel;
    QLabel*         shapeIDValueLabel;
    QLabel*         shapeTypeLabel;
    QLabel*         shapeTypeValueLabel;
    QLabel*         shapeDimensionLabels[shapeDimensionLabelCount];
    bool            isText;

    /* Right side (non-text) */
    QLabel*         penColorLabel;
    QLabel*         penColorValueLabel;
    QLabel*         penWidthLabel;
    QLabel*         penWidthValueLabel;
    QLabel*         penStyleLabel;
    QLabel*         penStyleValueLabel;
    QLabel*         penCapStyleLabel;
    QLabel*         penCapStyleValueLabel;
    QLabel*         penJoinStyleLabel;
    QLabel*         penJoinStyleValueLabel;
    QLabel*         brushColorLabel;
    QLabel*         brushColorValueLabel;
    QLabel*         brushStyleLabel;
    QLabel*         brushStyleValueLabel;

    /* Right side (text) */
    QLabel*         textStringLabel;
    QLabel*         textStringValueLabel;
    QLabel*         textColorLabel;
    QLabel*         textColorValueLabel;
    QLabel*         textAlignmentLabel;
    QLabel*         textAlignmentValueLabel;
    QLabel*         textPointSizeLabel;
    QLabel*         textPointSizeValueLabel;
    QLabel*         textFontFamilyLabel;
    QLabel*         textFontFamilyValueLabel;
    QLabel*         textFontStyleLabel;
    QLabel*         textFontStyleValueLabel;
    QLabel*         textFontWeightLabel;
    QLabel*         textFontWeightValueLabel;

    Vector<Shape*>* shapeVector;
};

#endif // MAINWINDOW_H

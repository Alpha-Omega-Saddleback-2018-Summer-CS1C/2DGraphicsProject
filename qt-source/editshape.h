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

#ifndef EDITSHAPE_H
#define EDITSHAPE_H

#include <QWidget>
#include "custom_vector.h"
#include "shape.h"

// Forward decleration
class QGridLayout;
class QPushButton;
class QLineEdit;
class QComboBox;
class QLabel;
class QScrollArea;
class MainWindow;

using shape::Shape;

class EditShape : public QWidget
{
    Q_OBJECT

    static const int shapeDimensionCount = 4;
    static const int shapeDescriptionCount = 7;

public:
    explicit EditShape(QWidget *parent = nullptr);
    ~EditShape();

    void passParams(Shape* shape, MainWindow* mainWindow);

signals:

public slots:
    void addDimensionPoint();
    void editShape();
    void removeDimensionPoint();

private:
    QGridLayout*        mainLayout;

    QLabel*             shapeHeaderLabel[4];

    QWidget*            shapeDimensionTable;
    QScrollArea*        shapeDimensionTableScrollArea;
    QGridLayout*        shapeDimensionTableLayout;
    Vector<QLabel*>     shapeDimensionTableLabels;
    Vector<QLineEdit*>  shapeDimensionTableLineEdits;
    QPushButton*        shapeDimensionTableButton[2];

    QLabel*             shapeDimensionLabel[4];
    QLineEdit*          shapeDimensionLineEdit[4];

    QLabel*             shapeDescriptionLabel[7];
    QComboBox*          shapeDescriptionComboBox[7];

    QComboBox*          penWidthComboBox;
    QComboBox*          fontSizeComboBox;
    QLineEdit*          textStringLineEdit;

    QPushButton*        editShapeButton;
    QPushButton*        cancelButton;

    Shape*              selectedShape;
    MainWindow*         mainWindow;
};

#endif // ADDSHAPE_H

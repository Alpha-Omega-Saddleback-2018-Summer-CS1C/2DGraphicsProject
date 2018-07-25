/*
 *  2D Graphics Modeler
 *  July 2018
 *
 *  David Epstein <DavidE92@live.com>
 *  Greg Graffius <ggraffius0@saddleback.edu>
 *  Justis Ketcham <justis.ketcham@gmail.com>
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
    File: editshape.h

    Defines an "add shape" widget
 */

#include <QtWidgets>
#include "editshape.h"
#include "circle.h"
#include "ellipse.h"
#include "line.h"
#include "mainwindow.h"
#include "polygon.h"
#include "polyline.h"
#include "rectangle.h"
#include "square.h"
#include "textbox.h"

EditShape::EditShape(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QGridLayout;
    mainLayout->setVerticalSpacing(20);

    shapeHeaderLabel[0] = new QLabel("Shape ID:");
    shapeHeaderLabel[1] = new QLabel;
    shapeHeaderLabel[2] = new QLabel("Shape Type:");
    shapeHeaderLabel[3] = new QLabel;

    editShapeButton = new QPushButton("Edit Shape");
    cancelButton = new QPushButton("Cancel");

    mainLayout->addWidget(shapeHeaderLabel[0], 0, 0, 1, 1);
    mainLayout->addWidget(shapeHeaderLabel[1], 0, 1, 1, 1);
    mainLayout->addWidget(shapeHeaderLabel[2], 1, 0, 1, 1);
    mainLayout->addWidget(shapeHeaderLabel[3], 1, 1, 1, 1);
    mainLayout->addWidget(cancelButton, 7, 0, 1, 1);
    mainLayout->addWidget(editShapeButton, 7, 5, 1, 1);

    shapeDimensionTableScrollArea = new QScrollArea;
    shapeDimensionTable = new QWidget(shapeDimensionTableScrollArea);
    shapeDimensionTableLayout = new QGridLayout(shapeDimensionTable);
    QLabel* tableHeader[3];

    for(int i = 0; i <3; ++i)
        tableHeader[i] = new QLabel(shapeDimensionTable);

    tableHeader[0]->setText("Point");
    tableHeader[1]->setText("X");
    tableHeader[2]->setText("Y");
    shapeDimensionTableLabels.push_back(tableHeader[0]);
    shapeDimensionTableLabels.push_back(tableHeader[1]);
    shapeDimensionTableLabels.push_back(tableHeader[2]);
    shapeDimensionTableLayout->addWidget(tableHeader[0], 0, 0, 1, 1);
    shapeDimensionTableLayout->addWidget(tableHeader[1], 0, 1, 1, 1);
    shapeDimensionTableLayout->addWidget(tableHeader[2], 0, 2, 1, 1);
    shapeDimensionTableLayout->setColumnMinimumWidth(0, 20);
    shapeDimensionTableLayout->setAlignment(Qt::AlignTop);

    shapeDimensionTable->setLayout(shapeDimensionTableLayout);
    shapeDimensionTableScrollArea->setWidget(shapeDimensionTable);
    shapeDimensionTableScrollArea->setWidgetResizable(true);
    shapeDimensionTableScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    shapeDimensionTableScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mainLayout->addWidget(shapeDimensionTableScrollArea, 2, 0, 4, 3);

    shapeDimensionTableButton[0] = new QPushButton("Add Point");
    shapeDimensionTableButton[1] = new QPushButton("Remove Point");
    mainLayout->addWidget(shapeDimensionTableButton[0], 6, 0, 1, 1);
    mainLayout->addWidget(shapeDimensionTableButton[1], 6, 2, 1, 1);

    for(int i = 0; i < shapeDimensionCount; ++i)
    {
        shapeDimensionLabel[i] = new QLabel;
        shapeDimensionLineEdit[i] = new QLineEdit;
        mainLayout->addWidget(shapeDimensionLabel[i], i + 2, 0, 1, 1);
        mainLayout->addWidget(shapeDimensionLineEdit[i], i + 2, 1, 1, 1);
        shapeDimensionLineEdit[i]->setMaximumWidth(50);
    }

    for(int i = 0; i < shapeDescriptionCount; ++i)
    {
        shapeDescriptionLabel[i] = new QLabel;
        shapeDescriptionComboBox[i] = new QComboBox;
        mainLayout->addWidget(shapeDescriptionLabel[i], i, 3, 1, 1);
        mainLayout->addWidget(shapeDescriptionComboBox[i], i, 4, 1, 1);
    }

    penWidthComboBox = new QComboBox;
    fontSizeComboBox = new QComboBox;
    textStringLineEdit = new QLineEdit;

    for(int i = 0; i <= 20; ++i)
        penWidthComboBox->addItem(QString::number(i));

    for(int i = 0; i <= 50; ++i)
        fontSizeComboBox->addItem(QString::number(i));

    mainLayout->addWidget(penWidthComboBox, 1, 4, 1, 1);
    mainLayout->addWidget(fontSizeComboBox, 3, 4, 1, 1);
    mainLayout->addWidget(textStringLineEdit, 0, 4, 1, 2);

    connect(editShapeButton, SIGNAL(clicked(bool)), this, SLOT(editShape()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(shapeDimensionTableButton[0], SIGNAL(clicked(bool)), this, SLOT(addDimensionPoint()));
    connect(shapeDimensionTableButton[1], SIGNAL(clicked(bool)), this, SLOT(removeDimensionPoint()));

    setLayout(mainLayout);
    setWindowTitle("Shape Manager");
    setMinimumSize(650, 350);
    setMaximumSize(650, 350);
}

EditShape::~EditShape()
{
    delete mainLayout;
    delete shapeDimensionTableLayout;
}

void EditShape::passParams(Shape* shape, MainWindow* parentWindow)
{
    selectedShape = shape;
    mainWindow = parentWindow;

    QString type = selectedShape->getTypeAsQString();
    shapeHeaderLabel[1]->setText(QString::number(shape->getID()));
    shapeHeaderLabel[3]->setText(type);

    if(type == "Textbox")
    {
        shape::TextBox* text = dynamic_cast<shape::TextBox*>(selectedShape);

        shapeDescriptionLabel[0]->setText("Text String:");
        shapeDescriptionLabel[1]->setText("Text Color:");
        shapeDescriptionLabel[2]->setText("Text Alignment:");
        shapeDescriptionLabel[3]->setText("Font Size:");
        shapeDescriptionLabel[4]->setText("Font Family:");
        shapeDescriptionLabel[5]->setText("Font Style:");
        shapeDescriptionLabel[6]->setText("Font Weight:");

        shapeDescriptionComboBox[0]->hide();

        penWidthComboBox->hide();
        shapeDescriptionComboBox[1]->show();
        shapeDescriptionComboBox[1]->addItem("White");
        shapeDescriptionComboBox[1]->addItem("Black");
        shapeDescriptionComboBox[1]->addItem("Red");
        shapeDescriptionComboBox[1]->addItem("Green");
        shapeDescriptionComboBox[1]->addItem("Blue");
        shapeDescriptionComboBox[1]->addItem("Magenta");
        shapeDescriptionComboBox[1]->addItem("Yellow");
        shapeDescriptionComboBox[1]->addItem("Gray");

        shapeDescriptionComboBox[2]->addItem("Left");
        shapeDescriptionComboBox[2]->addItem("Right");
        shapeDescriptionComboBox[2]->addItem("Top");
        shapeDescriptionComboBox[2]->addItem("Bottom");
        shapeDescriptionComboBox[2]->addItem("Center");

        shapeDescriptionComboBox[3]->hide();

        shapeDescriptionComboBox[4]->addItem("Comic Sans MS");
        shapeDescriptionComboBox[4]->addItem("Courier");
        shapeDescriptionComboBox[4]->addItem("Helvetica");
        shapeDescriptionComboBox[4]->addItem("Times");

        shapeDescriptionComboBox[5]->addItem("Normal");
        shapeDescriptionComboBox[5]->addItem("Italic");
        shapeDescriptionComboBox[5]->addItem("Oblique");

        shapeDescriptionComboBox[6]->addItem("Thin");
        shapeDescriptionComboBox[6]->addItem("Light");
        shapeDescriptionComboBox[6]->addItem("Normal");
        shapeDescriptionComboBox[6]->addItem("Bold");

        textStringLineEdit->setText(text->getText());
        shapeDescriptionComboBox[1]->setCurrentText(getQColorAsQString(text->getPen().color()));
        shapeDescriptionComboBox[2]->setCurrentText(getTextAlignmentAsQString(text->getAlignment()));
        fontSizeComboBox->setCurrentText(QString::number(text->getFont().pointSize()));
        shapeDescriptionComboBox[4]->setCurrentText(text->getFont().family());
        shapeDescriptionComboBox[5]->setCurrentText(getFontStyleAsQString(text->getFont().style()));
        shapeDescriptionComboBox[6]->setCurrentText(getFontWeightAsQString(text->getFont().weight()));
    }
    else
    {
        shapeDescriptionLabel[0]->setText("Pen Color:");
        shapeDescriptionLabel[1]->setText("Pen Width:");
        shapeDescriptionLabel[2]->setText("Pen Style:");
        shapeDescriptionLabel[3]->setText("Pen Cap Style:");
        shapeDescriptionLabel[4]->setText("Pen Join Style:");

        textStringLineEdit->hide();
        shapeDescriptionComboBox[0]->addItem("White");
        shapeDescriptionComboBox[0]->addItem("Black");
        shapeDescriptionComboBox[0]->addItem("Red");
        shapeDescriptionComboBox[0]->addItem("Green");
        shapeDescriptionComboBox[0]->addItem("Blue");
        shapeDescriptionComboBox[0]->addItem("Magenta");
        shapeDescriptionComboBox[0]->addItem("Yellow");
        shapeDescriptionComboBox[0]->addItem("Gray");

        shapeDescriptionComboBox[1]->hide();

        shapeDescriptionComboBox[2]->addItem("Solid");
        shapeDescriptionComboBox[2]->addItem("Dashed");
        shapeDescriptionComboBox[2]->addItem("Dotted");
        shapeDescriptionComboBox[2]->addItem("Dashed/Dotted");
        shapeDescriptionComboBox[2]->addItem("Dashed/Dotted/Dotted");

        fontSizeComboBox->hide();
        shapeDescriptionComboBox[3]->show();
        shapeDescriptionComboBox[3]->addItem("Square");
        shapeDescriptionComboBox[3]->addItem("Flat");
        shapeDescriptionComboBox[3]->addItem("Round");

        shapeDescriptionComboBox[4]->addItem("Miter");
        shapeDescriptionComboBox[4]->addItem("Bevel");
        shapeDescriptionComboBox[4]->addItem("Round");

        shapeDescriptionComboBox[0]->setCurrentText(getQColorAsQString(selectedShape->getPen().color()));
        penWidthComboBox->setCurrentText(QString::number(selectedShape->getPen().width()));
        shapeDescriptionComboBox[2]->setCurrentText(getPenStyleAsQString(selectedShape->getPen().style()));
        shapeDescriptionComboBox[3]->setCurrentText(getPenCapStyleAsQString(selectedShape->getPen().capStyle()));
        shapeDescriptionComboBox[4]->setCurrentText(getPenJoinStyleAsQString(selectedShape->getPen().joinStyle()));

        if(type == "Line" || type == "Polyline")
        {
            shapeDescriptionLabel[5]->setText("");
            shapeDescriptionLabel[6]->setText("");
            shapeDescriptionComboBox[5]->hide();
            shapeDescriptionComboBox[6]->hide();
        }
        else
        {
            shapeDescriptionLabel[5]->setText("Brush Color:");
            shapeDescriptionLabel[6]->setText("Brush Style:");

            shapeDescriptionComboBox[5]->addItem("White");
            shapeDescriptionComboBox[5]->addItem("Black");
            shapeDescriptionComboBox[5]->addItem("Red");
            shapeDescriptionComboBox[5]->addItem("Green");
            shapeDescriptionComboBox[5]->addItem("Blue");
            shapeDescriptionComboBox[5]->addItem("Magenta");
            shapeDescriptionComboBox[5]->addItem("Yellow");
            shapeDescriptionComboBox[5]->addItem("Gray");

            shapeDescriptionComboBox[6]->addItem("None");
            shapeDescriptionComboBox[6]->addItem("Solid");
            shapeDescriptionComboBox[6]->addItem("Horizonal Lines");
            shapeDescriptionComboBox[6]->addItem("Vertical Lines");

            shapeDescriptionComboBox[5]->setCurrentText(getQColorAsQString(selectedShape->getBrush().color()));
            shapeDescriptionComboBox[6]->setCurrentText(getBrushStyleAsQString(selectedShape->getBrush().style()));
        }
    }

    Vector<int> dimensions = selectedShape->getDimensions();
    if(type == "Polyline" || type == "Polygon")
    {
        QLabel* label[dimensions.size() / 2];
        for(int i = 0; i < dimensions.size() / 2; ++i)
        {
            label[i] = new QLabel(QString::number(i + 1), shapeDimensionTable);
            shapeDimensionTableLabels.push_back(label[i]);
            shapeDimensionTableLayout->addWidget(label[i], i + 1, 0, 1, 1);
        }

        QLineEdit* lineEdit[dimensions.size()];
        for(int i = 0; i < dimensions.size(); ++i)
        {
            lineEdit[i] = new QLineEdit(shapeDimensionTable);
            lineEdit[i]->setMaximumWidth(50);
            lineEdit[i]->setText(QString::number(dimensions[i]));
            shapeDimensionTableLineEdits.push_back(lineEdit[i]);
            shapeDimensionTableLayout->addWidget(lineEdit[i], (i / 2) + 1, (i % 2) + 1, 1, 1);
        }
    }

    if(type == "Line")
    {
        shapeDimensionTableScrollArea->hide();
        shapeDimensionTableButton[0]->hide();
        shapeDimensionTableButton[1]->hide();
        for(int i = 0; i < shapeDimensionCount; ++i)
            shapeDimensionLineEdit[i]->setText(QString::number(dimensions[i]));

        shapeDimensionLabel[0]->setText("X1:");
        shapeDimensionLabel[1]->setText("Y1:");
        shapeDimensionLabel[2]->setText("X1:");
        shapeDimensionLabel[3]->setText("Y2:");
    }
    else if(type == "Polyline")
    {
        for(int i = 0; i < shapeDimensionCount; ++i)
        {
            shapeDimensionLabel[i]->hide();
            shapeDimensionLineEdit[i]->hide();
        }
    }
    else if(type == "Polygon")
    {
        for(int i = 0; i < shapeDimensionCount; ++i)
        {
            shapeDimensionLabel[i]->hide();
            shapeDimensionLineEdit[i]->hide();
        }
    }
    else if(type == "Rectangle")
    {
        shapeDimensionTableScrollArea->hide();
        shapeDimensionTableButton[0]->hide();
        shapeDimensionTableButton[1]->hide();
        for(int i = 0; i < shapeDimensionCount; ++i)
            shapeDimensionLineEdit[i]->setText(QString::number(dimensions[i]));

        shapeDimensionLabel[0]->setText("X:");
        shapeDimensionLabel[1]->setText("Y:");
        shapeDimensionLabel[2]->setText("Width:");
        shapeDimensionLabel[3]->setText("Height:");
    }
    else if(type == "Square")
    {
        shapeDimensionTableScrollArea->hide();
        shapeDimensionTableButton[0]->hide();
        shapeDimensionTableButton[1]->hide();
        for(int i = 0; i < shapeDimensionCount - 1; ++i)
            shapeDimensionLineEdit[i]->setText(QString::number(dimensions[i]));
        shapeDimensionLineEdit[3]->hide();

        shapeDimensionLabel[0]->setText("X:");
        shapeDimensionLabel[1]->setText("Y:");
        shapeDimensionLabel[2]->setText("Side:");
    }
    else if(type == "Ellipse")
    {
        shapeDimensionTableScrollArea->hide();
        shapeDimensionTableButton[0]->hide();
        shapeDimensionTableButton[1]->hide();
        for(int i = 0; i < shapeDimensionCount; ++i)
            shapeDimensionLineEdit[i]->setText(QString::number(dimensions[i]));

        shapeDimensionLabel[0]->setText("X:");
        shapeDimensionLabel[1]->setText("Y:");
        shapeDimensionLabel[2]->setText("RadiusX:");
        shapeDimensionLabel[3]->setText("RadiusY:");
    }
    else if(type == "Circle")
    {
        shapeDimensionTableScrollArea->hide();
        shapeDimensionTableButton[0]->hide();
        shapeDimensionTableButton[1]->hide();
        for(int i = 0; i < shapeDimensionCount - 1; ++i)
            shapeDimensionLineEdit[i]->setText(QString::number(dimensions[i]));
        shapeDimensionLineEdit[3]->hide();

        shapeDimensionLabel[0]->setText("X:");
        shapeDimensionLabel[1]->setText("Y:");
        shapeDimensionLabel[2]->setText("Radius:");
    }
    else // Textbox
    {
        shapeDimensionTableScrollArea->hide();
        shapeDimensionTableButton[0]->hide();
        shapeDimensionTableButton[1]->hide();
        for(int i = 0; i < shapeDimensionCount; ++i)
            shapeDimensionLineEdit[i]->setText(QString::number(dimensions[i]));

        shapeDimensionLabel[0]->setText("X:");
        shapeDimensionLabel[1]->setText("Y:");
        shapeDimensionLabel[2]->setText("Width:");
        shapeDimensionLabel[3]->setText("Height:");
    }
}

void EditShape::addDimensionPoint()
{
    int row = shapeDimensionTableLineEdits.size() / 2 + 1;
    QLabel* label = new QLabel(QString::number(row));
    QLineEdit* lineEditX = new QLineEdit;
    QLineEdit* lineEditY = new QLineEdit;
    lineEditX->setMaximumWidth(50);
    lineEditY->setMaximumWidth(50);

    shapeDimensionTableLabels.push_back(label);
    shapeDimensionTableLineEdits.push_back(lineEditX);
    shapeDimensionTableLineEdits.push_back(lineEditY);
    shapeDimensionTableLayout->addWidget(label, row, 0, 1, 1);
    shapeDimensionTableLayout->addWidget(lineEditX, row, 1, 1, 1);
    shapeDimensionTableLayout->addWidget(lineEditY, row, 2, 1, 1);
}

void EditShape::editShape()
{
    QString type = selectedShape->getTypeAsQString();

    if(type == "Line")
    {
        shape::Line* line = dynamic_cast<shape::Line*>(selectedShape);
        QPen pen;

        pen.setColor(QColor(shapeDescriptionComboBox[0]->currentText()));
        pen.setWidth(penWidthComboBox->currentText().toInt());
        pen.setStyle(getPenStyleFromQString(shapeDescriptionComboBox[2]->currentText()));
        pen.setCapStyle(getPenCapStyleFromQString(shapeDescriptionComboBox[3]->currentText()));
        pen.setJoinStyle(getPenJoinStyleFromQString(shapeDescriptionComboBox[4]->currentText()));

        if(!isNumber(shapeDimensionLineEdit[0]->text()) ||
            !isNumber(shapeDimensionLineEdit[1]->text()) ||
            !isNumber(shapeDimensionLineEdit[2]->text()) ||
            !isNumber(shapeDimensionLineEdit[3]->text()))
        {
            QMessageBox::information(this, "Action Denied", "Non-numberical input detected!", QMessageBox::Ok);
            return;
        }

        line->setPoints(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt(),
            shapeDimensionLineEdit[2]->text().toInt(), shapeDimensionLineEdit[3]->text().toInt());
        line->setPen(pen);
    }
    else if(type == "Polyline")
    {
        shape::Polyline* polyline = dynamic_cast<shape::Polyline*>(selectedShape);
        QPen pen;

        pen.setColor(QColor(shapeDescriptionComboBox[0]->currentText()));
        pen.setWidth(penWidthComboBox->currentText().toInt());
        pen.setStyle(getPenStyleFromQString(shapeDescriptionComboBox[2]->currentText()));
        pen.setCapStyle(getPenCapStyleFromQString(shapeDescriptionComboBox[3]->currentText()));
        pen.setJoinStyle(getPenJoinStyleFromQString(shapeDescriptionComboBox[4]->currentText()));

        polyline->setPen(pen);
        polyline->clearPoints();

        for(int i = 0; i < shapeDimensionTableLineEdits.size() / 2; ++i)
        {
            QLineEdit* lineEditX = shapeDimensionTableLineEdits[2 * i];
            QLineEdit* lineEditY = shapeDimensionTableLineEdits[2 * i + 1];

            if(!isNumber(lineEditX->text()) || !isNumber(lineEditY->text()))
            {
                QMessageBox::information(this, "Action Denied", "Non-numberical input detected!", QMessageBox::Ok);
                return;
            }

            polyline->addPoint({ lineEditX->text().toInt(), lineEditY->text().toInt() });
        }
    }
    else if(type == "Polygon")
    {
        shape::Polygon* polygon = dynamic_cast<shape::Polygon*>(selectedShape);
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(shapeDescriptionComboBox[0]->currentText()));
        pen.setWidth(penWidthComboBox->currentText().toInt());
        pen.setStyle(getPenStyleFromQString(shapeDescriptionComboBox[2]->currentText()));
        pen.setCapStyle(getPenCapStyleFromQString(shapeDescriptionComboBox[3]->currentText()));
        pen.setJoinStyle(getPenJoinStyleFromQString(shapeDescriptionComboBox[4]->currentText()));

        brush.setColor(QColor(shapeDescriptionComboBox[5]->currentText()));
        brush.setStyle(getBrushStyleFromQString(shapeDescriptionComboBox[6]->currentText()));

        polygon->setPen(pen);
        polygon->setBrush(brush);
        polygon->clearPoints();

        for(int i = 0; i < shapeDimensionTableLineEdits.size() / 2; ++i)
        {
            QLineEdit* lineEditX = shapeDimensionTableLineEdits[2 * i];
            QLineEdit* lineEditY = shapeDimensionTableLineEdits[2 * i + 1];

            if(!isNumber(lineEditX->text()) || !isNumber(lineEditY->text()))
            {
                QMessageBox::information(this, "Action Denied", "Non-numberical input detected!", QMessageBox::Ok);
                return;
            }

            polygon->addPoint({ lineEditX->text().toInt(), lineEditY->text().toInt() });
        }
    }
    else if(type == "Rectangle")
    {
        shape::Rectangle* rect = dynamic_cast<shape::Rectangle*>(selectedShape);
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(shapeDescriptionComboBox[0]->currentText()));
        pen.setWidth(penWidthComboBox->currentText().toInt());
        pen.setStyle(getPenStyleFromQString(shapeDescriptionComboBox[2]->currentText()));
        pen.setCapStyle(getPenCapStyleFromQString(shapeDescriptionComboBox[3]->currentText()));
        pen.setJoinStyle(getPenJoinStyleFromQString(shapeDescriptionComboBox[4]->currentText()));

        brush.setColor(QColor(shapeDescriptionComboBox[5]->currentText()));
        brush.setStyle(getBrushStyleFromQString(shapeDescriptionComboBox[6]->currentText()));

        if(!isNumber(shapeDimensionLineEdit[0]->text()) ||
            !isNumber(shapeDimensionLineEdit[1]->text()) ||
            !isNumber(shapeDimensionLineEdit[2]->text()) ||
            !isNumber(shapeDimensionLineEdit[3]->text()))
        {
            QMessageBox::information(this, "Action Denied", "Non-numberical input detected!", QMessageBox::Ok);
            return;
        }

        rect->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        rect->setDimensions(shapeDimensionLineEdit[2]->text().toInt(), shapeDimensionLineEdit[3]->text().toInt());
        rect->setPen(pen);
        rect->setBrush(brush);
    }
    else if(type == "Square")
    {
        shape::Square* square = dynamic_cast<shape::Square*>(selectedShape);
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(shapeDescriptionComboBox[0]->currentText()));
        pen.setWidth(penWidthComboBox->currentText().toInt());
        pen.setStyle(getPenStyleFromQString(shapeDescriptionComboBox[2]->currentText()));
        pen.setCapStyle(getPenCapStyleFromQString(shapeDescriptionComboBox[3]->currentText()));
        pen.setJoinStyle(getPenJoinStyleFromQString(shapeDescriptionComboBox[4]->currentText()));

        brush.setColor(QColor(shapeDescriptionComboBox[5]->currentText()));
        brush.setStyle(getBrushStyleFromQString(shapeDescriptionComboBox[6]->currentText()));

        if(!isNumber(shapeDimensionLineEdit[0]->text()) ||
            !isNumber(shapeDimensionLineEdit[1]->text()) ||
            !isNumber(shapeDimensionLineEdit[2]->text()))
        {
            QMessageBox::information(this, "Action Denied", "Non-numberical input detected!", QMessageBox::Ok);
            return;
        }
        square->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        square->setSide(shapeDimensionLineEdit[2]->text().toInt());
        square->setPen(pen);
        square->setBrush(brush);
    }
    else if(type == "Ellipse")
    {
        shape::Ellipse* ellipse = dynamic_cast<shape::Ellipse*>(selectedShape);
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(shapeDescriptionComboBox[0]->currentText()));
        pen.setWidth(penWidthComboBox->currentText().toInt());
        pen.setStyle(getPenStyleFromQString(shapeDescriptionComboBox[2]->currentText()));
        pen.setCapStyle(getPenCapStyleFromQString(shapeDescriptionComboBox[3]->currentText()));
        pen.setJoinStyle(getPenJoinStyleFromQString(shapeDescriptionComboBox[4]->currentText()));

        brush.setColor(QColor(shapeDescriptionComboBox[5]->currentText()));
        brush.setStyle(getBrushStyleFromQString(shapeDescriptionComboBox[6]->currentText()));

        if(!isNumber(shapeDimensionLineEdit[0]->text()) ||
            !isNumber(shapeDimensionLineEdit[1]->text()) ||
            !isNumber(shapeDimensionLineEdit[2]->text()) ||
            !isNumber(shapeDimensionLineEdit[3]->text()))
        {
            QMessageBox::information(this, "Action Denied", "Non-numberical input detected!", QMessageBox::Ok);
            return;
        }
        ellipse->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        ellipse->setRadii(shapeDimensionLineEdit[2]->text().toInt(), shapeDimensionLineEdit[3]->text().toInt());
        ellipse->setPen(pen);
        ellipse->setBrush(brush);
    }
    else if(type == "Circle")
    {
        shape::Circle* circle = dynamic_cast<shape::Circle*>(selectedShape);
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(shapeDescriptionComboBox[0]->currentText()));
        pen.setWidth(penWidthComboBox->currentText().toInt());
        pen.setStyle(getPenStyleFromQString(shapeDescriptionComboBox[2]->currentText()));
        pen.setCapStyle(getPenCapStyleFromQString(shapeDescriptionComboBox[3]->currentText()));
        pen.setJoinStyle(getPenJoinStyleFromQString(shapeDescriptionComboBox[4]->currentText()));

        brush.setColor(QColor(shapeDescriptionComboBox[5]->currentText()));
        brush.setStyle(getBrushStyleFromQString(shapeDescriptionComboBox[6]->currentText()));

        if(!isNumber(shapeDimensionLineEdit[0]->text()) ||
            !isNumber(shapeDimensionLineEdit[1]->text()) ||
            !isNumber(shapeDimensionLineEdit[2]->text()))
        {
            QMessageBox::information(this, "Action Denied", "Non-numberical input detected!", QMessageBox::Ok);
            return;
        }

        circle->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        circle->setRadius(shapeDimensionLineEdit[2]->text().toInt());
        circle->setPen(pen);
        circle->setBrush(brush);
    }
    else // Textbox
    {
        shape::TextBox* text = dynamic_cast<shape::TextBox*>(selectedShape);
        QPen pen;
        QFont font;

        pen.setColor(QColor(shapeDescriptionComboBox[1]->currentText()));

        font.setPointSize(fontSizeComboBox->currentText().toInt());
        font.setFamily(shapeDescriptionComboBox[4]->currentText());
        font.setStyle(getFontStyleFromQString(shapeDescriptionComboBox[5]->currentText()));
        font.setWeight(getFontWeightFromQString(shapeDescriptionComboBox[6]->currentText()));

        if(!isNumber(shapeDimensionLineEdit[0]->text()) ||
            !isNumber(shapeDimensionLineEdit[1]->text()) ||
            !isNumber(shapeDimensionLineEdit[2]->text()) ||
            !isNumber(shapeDimensionLineEdit[3]->text()))
        {
            QMessageBox::information(this, "Action Denied", "Non-numberical input detected!", QMessageBox::Ok);
            return;
        }

        text->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        text->setDimensions(shapeDimensionLineEdit[2]->text().toInt(), shapeDimensionLineEdit[3]->text().toInt());
        text->setText(textStringLineEdit->text());
        text->setAlignment(getTextAlignmentFromQString(shapeDescriptionComboBox[2]->currentText()));
        text->setPen(pen);
        text->setFont(font);
    }

    mainWindow->updateShapeList();
    close();
}

void EditShape::removeDimensionPoint()
{
    int row = shapeDimensionTableLineEdits.size() / 2;

    if(selectedShape->getTypeAsQString() == "Polyline" && row < 3)
    {
        QMessageBox::information(this, "Action Denied", "This shape requires a minimum of two points", QMessageBox::Ok);
        return;
    }

    if(selectedShape->getTypeAsQString() == "Polygon" && row < 4)
    {
        QMessageBox::information(this, "Action Denied", "This shape requires a minimum of two points", QMessageBox::Ok);
        return;
    }

    Vector<QLabel*>::iterator lastLabel = shapeDimensionTableLabels.end() - 1;
    Vector<QLineEdit*>::iterator lastLineEdit = shapeDimensionTableLineEdits.end() - 1;

    shapeDimensionTableLayout->removeWidget(*lastLabel);
    shapeDimensionTableLayout->removeWidget(*lastLineEdit);
    shapeDimensionTableLayout->removeWidget(*(lastLineEdit - 1));

    delete *lastLabel;
    delete *lastLineEdit;
    delete *(lastLineEdit - 1);

    shapeDimensionTableLabels.pop_back();
    shapeDimensionTableLineEdits.pop_back();
    shapeDimensionTableLineEdits.pop_back();
}

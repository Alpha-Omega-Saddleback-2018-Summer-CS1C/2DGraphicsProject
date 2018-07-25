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

#include <QtWidgets>
#include "addshape.h"
#include "circle.h"
#include "ellipse.h"
#include "line.h"
#include "mainwindow.h"
#include "polygon.h"
#include "polyline.h"
#include "rectangle.h"
#include "square.h"
#include "textbox.h"

AddShape::AddShape(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QGridLayout;
    mainLayout->setVerticalSpacing(20);

    shapeHeaderLabel[0] = new QLabel("Shape ID:");
    shapeHeaderLabel[1] = new QLabel("Shape Type:");
    shapeIDComboBox = new QComboBox;
    shapeTypeComboBox = new QComboBox;

    shapeTypeComboBox->addItem("Line");
    shapeTypeComboBox->addItem("Polyline");
    shapeTypeComboBox->addItem("Polygon");
    shapeTypeComboBox->addItem("Rectangle");
    shapeTypeComboBox->addItem("Square");
    shapeTypeComboBox->addItem("Ellipse");
    shapeTypeComboBox->addItem("Circle");
    shapeTypeComboBox->addItem("Textbox");
    addShapeButton = new QPushButton("Add Shape");
    cancelButton = new QPushButton("Cancel");

    mainLayout->addWidget(shapeHeaderLabel[0], 0, 0, 1, 1);
    mainLayout->addWidget(shapeIDComboBox, 0, 1, 1, 1);
    mainLayout->addWidget(shapeHeaderLabel[1], 1, 0, 1, 1);
    mainLayout->addWidget(shapeTypeComboBox, 1, 1, 1, 1);
    mainLayout->addWidget(cancelButton, 7, 0, 1, 1);
    mainLayout->addWidget(addShapeButton, 7, 5, 1, 1);

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

    connect(shapeTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(shapeTypeChanged()));
    connect(addShapeButton, SIGNAL(clicked(bool)), this, SLOT(addShape()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(shapeDimensionTableButton[0], SIGNAL(clicked(bool)), this, SLOT(addDimensionPoint()));
    connect(shapeDimensionTableButton[1], SIGNAL(clicked(bool)), this, SLOT(removeDimensionPoint()));

    setLayout(mainLayout);
    setWindowTitle("Shape Manager");
    setMinimumSize(650, 350);
    setMaximumSize(650, 350);
    shapeTypeChanged();
}

AddShape::~AddShape()
{
    delete mainLayout;
    delete shapeDimensionTableLayout;
}

void AddShape::passParams(Vector<Shape*>* shapes, MainWindow* parentWindow)
{
    shapeVector = shapes;
    mainWindow = parentWindow;

    for(int i = 1; i < 100; ++i)
    {
        if(custom_find(shapeVector->begin(), shapeVector->end(), i,
            [](Shape* s, int id)
            {
                return s->getID() == id;
            }) ==  shapeVector->end())
            shapeIDComboBox->addItem(QString::number(i));
    }
}

void AddShape::addDimensionPoint()
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

void AddShape::addShape()
{
    QString type = shapeTypeComboBox->currentText();

    if(type == "Line")
    {
        shape::Line* line = new shape::Line;
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

        line->setID(shapeIDComboBox->currentText().toInt());
        line->setPoints(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt(),
            shapeDimensionLineEdit[2]->text().toInt(), shapeDimensionLineEdit[3]->text().toInt());
        line->setPen(pen);

        shapeVector->push_back(line);
    }
    else if(type == "Polyline")
    {
        shape::Polyline* polyline = new shape::Polyline;
        QPen pen;

        pen.setColor(QColor(shapeDescriptionComboBox[0]->currentText()));
        pen.setWidth(penWidthComboBox->currentText().toInt());
        pen.setStyle(getPenStyleFromQString(shapeDescriptionComboBox[2]->currentText()));
        pen.setCapStyle(getPenCapStyleFromQString(shapeDescriptionComboBox[3]->currentText()));
        pen.setJoinStyle(getPenJoinStyleFromQString(shapeDescriptionComboBox[4]->currentText()));

        polyline->setID(shapeIDComboBox->currentText().toInt());
        polyline->setPen(pen);

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

        shapeVector->push_back(polyline);
    }
    else if(type == "Polygon")
    {
        shape::Polygon* polygon = new shape::Polygon;
        QPen pen;
        QBrush brush;

        pen.setColor(QColor(shapeDescriptionComboBox[0]->currentText()));
        pen.setWidth(penWidthComboBox->currentText().toInt());
        pen.setStyle(getPenStyleFromQString(shapeDescriptionComboBox[2]->currentText()));
        pen.setCapStyle(getPenCapStyleFromQString(shapeDescriptionComboBox[3]->currentText()));
        pen.setJoinStyle(getPenJoinStyleFromQString(shapeDescriptionComboBox[4]->currentText()));

        brush.setColor(QColor(shapeDescriptionComboBox[5]->currentText()));
        brush.setStyle(getBrushStyleFromQString(shapeDescriptionComboBox[6]->currentText()));

        polygon->setID(shapeIDComboBox->currentText().toInt());
        polygon->setPen(pen);
        polygon->setBrush(brush);

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

        shapeVector->push_back(polygon);
    }
    else if(type == "Rectangle")
    {
        shape::Rectangle* rect = new shape::Rectangle;
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

        rect->setID(shapeIDComboBox->currentText().toInt());
        rect->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        rect->setDimensions(shapeDimensionLineEdit[2]->text().toInt(), shapeDimensionLineEdit[3]->text().toInt());
        rect->setPen(pen);
        rect->setBrush(brush);

        shapeVector->push_back(rect);
    }
    else if(type == "Square")
    {
        shape::Square* square = new shape::Square;
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

        square->setID(shapeIDComboBox->currentText().toInt());
        square->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        square->setSide(shapeDimensionLineEdit[2]->text().toInt());
        square->setPen(pen);
        square->setBrush(brush);

        shapeVector->push_back(square);
    }
    else if(type == "Ellipse")
    {
        shape::Ellipse* ellipse = new shape::Ellipse;
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

        ellipse->setID(shapeIDComboBox->currentText().toInt());
        ellipse->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        ellipse->setRadii(shapeDimensionLineEdit[2]->text().toInt(), shapeDimensionLineEdit[3]->text().toInt());
        ellipse->setPen(pen);
        ellipse->setBrush(brush);

        shapeVector->push_back(ellipse);
    }
    else if(type == "Circle")
    {
        shape::Circle* circle = new shape::Circle();
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

        circle->setID(shapeIDComboBox->currentText().toInt());
        circle->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        circle->setRadius(shapeDimensionLineEdit[2]->text().toInt());
        circle->setPen(pen);
        circle->setBrush(brush);

        shapeVector->push_back(circle);
    }
    else // Textbox
    {
        shape::TextBox* text = new shape::TextBox();
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

        text->setID(shapeIDComboBox->currentText().toInt());
        text->setPosition(shapeDimensionLineEdit[0]->text().toInt(), shapeDimensionLineEdit[1]->text().toInt());
        text->setDimensions(shapeDimensionLineEdit[2]->text().toInt(), shapeDimensionLineEdit[3]->text().toInt());
        text->setText(textStringLineEdit->text());
        text->setAlignment(getTextAlignmentFromQString(shapeDescriptionComboBox[2]->currentText()));
        text->setPen(pen);
        text->setFont(font);

        shapeVector->push_back(text);
    }

    mainWindow->updateShapeList();
    close();
}

void AddShape::removeDimensionPoint()
{
    int row = shapeDimensionTableLineEdits.size() / 2;

    if(shapeTypeComboBox->currentText() == "Polyline" && row < 3)
    {
        QMessageBox::information(this, "Action Denied", "This shape requires a minimum of two points", QMessageBox::Ok);
        return;
    }

    if(shapeTypeComboBox->currentText() == "Polygon" && row < 4)
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

void AddShape::shapeTypeChanged()
{
    QString type = shapeTypeComboBox->currentText();

    for(int i = 0; i < shapeDescriptionCount; ++i)
        shapeDescriptionComboBox[i]->clear();
    textStringLineEdit->clear();

    if(type == "Textbox")
    {
        shapeDescriptionLabel[0]->setText("Text String:");
        shapeDescriptionLabel[1]->setText("Text Color:");
        shapeDescriptionLabel[2]->setText("Text Alignment:");
        shapeDescriptionLabel[3]->setText("Font Size:");
        shapeDescriptionLabel[4]->setText("Font Family:");
        shapeDescriptionLabel[5]->setText("Font Style:");
        shapeDescriptionLabel[6]->setText("Font Weight:");

        shapeDescriptionComboBox[0]->hide();
        textStringLineEdit->show();

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
        fontSizeComboBox->show();

        shapeDescriptionComboBox[4]->addItem("Comic Sans MS");
        shapeDescriptionComboBox[4]->addItem("Courier");
        shapeDescriptionComboBox[4]->addItem("Helvetica");
        shapeDescriptionComboBox[4]->addItem("Times");

        shapeDescriptionComboBox[5]->show();
        shapeDescriptionComboBox[5]->addItem("Normal");
        shapeDescriptionComboBox[5]->addItem("Italic");
        shapeDescriptionComboBox[5]->addItem("Oblique");

        shapeDescriptionComboBox[6]->show();
        shapeDescriptionComboBox[6]->addItem("Thin");
        shapeDescriptionComboBox[6]->addItem("Light");
        shapeDescriptionComboBox[6]->addItem("Normal");
        shapeDescriptionComboBox[6]->addItem("Bold");
    }
    else
    {
        shapeDescriptionLabel[0]->setText("Pen Color:");
        shapeDescriptionLabel[1]->setText("Pen Width:");
        shapeDescriptionLabel[2]->setText("Pen Style:");
        shapeDescriptionLabel[3]->setText("Pen Cap Style:");
        shapeDescriptionLabel[4]->setText("Pen Join Style:");

        textStringLineEdit->hide();
        shapeDescriptionComboBox[0]->show();
        shapeDescriptionComboBox[0]->addItem("White");
        shapeDescriptionComboBox[0]->addItem("Black");
        shapeDescriptionComboBox[0]->addItem("Red");
        shapeDescriptionComboBox[0]->addItem("Green");
        shapeDescriptionComboBox[0]->addItem("Blue");
        shapeDescriptionComboBox[0]->addItem("Magenta");
        shapeDescriptionComboBox[0]->addItem("Yellow");
        shapeDescriptionComboBox[0]->addItem("Gray");

        shapeDescriptionComboBox[1]->hide();
        penWidthComboBox->show();

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
            shapeDescriptionComboBox[5]->show();
            shapeDescriptionComboBox[6]->show();

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
        }
    }

    if(type == "Line")
    {
        shapeDimensionTableScrollArea->hide();
        shapeDimensionTableButton[0]->hide();
        shapeDimensionTableButton[1]->hide();
        for(int i = 0; i < shapeDimensionCount; ++i)
        {
            shapeDimensionLabel[i]->show();
            shapeDimensionLineEdit[i]->show();
            shapeDimensionLineEdit[i]->clear();
        }

        shapeDimensionLabel[0]->setText("X1:");
        shapeDimensionLabel[1]->setText("Y1:");
        shapeDimensionLabel[2]->setText("X2:");
        shapeDimensionLabel[3]->setText("Y2:");
    }
    else if(type == "Polyline")
    {
        shapeDimensionTableScrollArea->show();
        shapeDimensionTableButton[0]->show();
        shapeDimensionTableButton[1]->show();
        for(int i = 0; i < shapeDimensionCount; ++i)
        {
            shapeDimensionLabel[i]->hide();
            shapeDimensionLineEdit[i]->hide();
        }

        QLabel* label[2];
        for(int i = 0; i < 2; ++i)
        {
            label[i] = new QLabel(QString::number(i + 1), shapeDimensionTable);
            shapeDimensionTableLabels.push_back(label[i]);
            shapeDimensionTableLayout->addWidget(label[i], i + 1, 0, 1, 1);
        }

        QLineEdit* lineEdit[4];
        for(int i = 0; i < 4; ++i)
        {
            lineEdit[i] = new QLineEdit(shapeDimensionTable);
            lineEdit[i]->setMaximumWidth(50);
            shapeDimensionTableLineEdits.push_back(lineEdit[i]);
            shapeDimensionTableLayout->addWidget(lineEdit[i], (i / 2) + 1, (i % 2) + 1, 1, 1);
        }
    }
    else if(type == "Polygon")
    {
        shapeDimensionTableScrollArea->show();
        shapeDimensionTableButton[0]->show();
        shapeDimensionTableButton[1]->show();
        for(int i = 0; i < shapeDimensionCount; ++i)
        {
            shapeDimensionLabel[i]->hide();
            shapeDimensionLineEdit[i]->hide();
        }

        QLabel* label[3];
        for(int i = 0; i < 3; ++i)
        {
            label[i] = new QLabel(QString::number(i + 1), shapeDimensionTable);
            shapeDimensionTableLabels.push_back(label[i]);
            shapeDimensionTableLayout->addWidget(label[i], i + 1, 0, 1, 1);
        }

        QLineEdit* lineEdit[6];
        for(int i = 0; i < 6; ++i)
        {
            lineEdit[i] = new QLineEdit(shapeDimensionTable);
            lineEdit[i]->setMaximumWidth(50);
            shapeDimensionTableLineEdits.push_back(lineEdit[i]);
            shapeDimensionTableLayout->addWidget(lineEdit[i], (i / 2) + 1, (i % 2) + 1, 1, 1);
        }
    }
    else if(type == "Rectangle" || type == "Textbox")
    {
        shapeDimensionTableScrollArea->hide();
        shapeDimensionTableButton[0]->hide();
        shapeDimensionTableButton[1]->hide();
        for(int i = 0; i < shapeDimensionCount; ++i)
        {
            shapeDimensionLabel[i]->show();
            shapeDimensionLineEdit[i]->show();
        }

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
        shapeDimensionLabel[3]->hide();
        shapeDimensionLineEdit[3]->hide();

        for(int i = 0; i < shapeDimensionCount - 1; ++i)
        {
            shapeDimensionLabel[i]->show();
            shapeDimensionLineEdit[i]->show();
            shapeDimensionLineEdit[i]->clear();
        }

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
        {
            shapeDimensionLabel[i]->show();
            shapeDimensionLineEdit[i]->show();
            shapeDimensionLineEdit[i]->clear();
        }

        shapeDimensionLabel[0]->setText("X:");
        shapeDimensionLabel[1]->setText("Y:");
        shapeDimensionLabel[2]->setText("RadiusX:");
        shapeDimensionLabel[3]->setText("RadiusY:");
    }
    else /* "Circle" */
    {
        shapeDimensionTableScrollArea->hide();
        shapeDimensionTableButton[0]->hide();
        shapeDimensionTableButton[1]->hide();
        shapeDimensionLabel[3]->hide();
        shapeDimensionLineEdit[3]->hide();

        for(int i = 0; i < shapeDimensionCount - 1; ++i)
        {
            shapeDimensionLabel[i]->show();
            shapeDimensionLineEdit[i]->show();
            shapeDimensionLineEdit[i]->clear();
        }

        shapeDimensionLabel[0]->setText("X:");
        shapeDimensionLabel[1]->setText("Y:");
        shapeDimensionLabel[2]->setText("Radius:");
    }
}

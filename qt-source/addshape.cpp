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
#include <iostream>

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

void AddShape::passParams(Vector<Shape*>* shapes)
{
    shapeVector = shapes;

    for(int i = 1; i < 100; ++i)
    {
        if(custom_find(shapeVector->begin(), shapeVector->end(), i,
            [](Vector<Shape*>::iterator it, int id)
            {
                return (*it)->getID() == id;
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

void AddShape::removeDimensionPoint()
{
    int row = shapeDimensionTableLineEdits.size() / 2;
    if(row < 3)
    {

    }
    else
    {
        shapeDimensionTableLayout->removeWidget(*(shapeDimensionTableLabels.end() - 1));
        shapeDimensionTableLabels.pop_back();
        shapeDimensionTableLayout->removeWidget(*(shapeDimensionTableLineEdits.end() - 1));
        shapeDimensionTableLineEdits.pop_back();
        shapeDimensionTableLayout->removeWidget(*(shapeDimensionTableLineEdits.end() - 1));
        shapeDimensionTableLineEdits.pop_back();
    }
}

void AddShape::addShape()
{

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
        shapeDescriptionComboBox[3]->addItem("Solid");
        shapeDescriptionComboBox[3]->addItem("Dashed");
        shapeDescriptionComboBox[3]->addItem("Dotted");

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

    if(type == "Polyline" || type == "Polygon")
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
    else if(type == "Line")
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
    else if(type == "Circle")
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
    else // Square
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
}

bool AddShape::verifyShape()
{
    return true;
}

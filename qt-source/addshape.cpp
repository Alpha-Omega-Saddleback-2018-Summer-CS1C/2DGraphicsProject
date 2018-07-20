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

AddShape::AddShape(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QGridLayout;
    mainLayout->setVerticalSpacing(10);

    shapeHeaderLabel[0] = new QLabel("Shape ID:");
    shapeHeaderLabel[1] = new QLabel("Shape Type:");
    shapeIDComboBox = new QComboBox;
    shapeTypeComboBox = new QComboBox;

    for(int i = 1; i < 100; ++i)
        shapeIDComboBox->addItem(QString::number(i));

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

    mainLayout->addWidget(shapeHeaderLabel[0], 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(shapeIDComboBox, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(shapeHeaderLabel[1], 1, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(shapeTypeComboBox, 1, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(cancelButton, 100, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(addShapeButton, 100, 5, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    for(int i = 0; i < shapeDescriptionCount; ++i)
    {
        shapeDescriptionLabel[i] = new QLabel;
        shapeDescriptionComboBox[i] = new QComboBox;
        mainLayout->addWidget(shapeDescriptionLabel[i], i, 3, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
        mainLayout->addWidget(shapeDescriptionComboBox[i], i, 4, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);
    }

    penWidthSpinBox = new QSpinBox;
    fontSizeSpinBox = new QSpinBox;
    textStringLineEdit = new QLineEdit;
    penWidthSpinBox->setRange(0, 20);
    fontSizeSpinBox->setRange(0, 50);

    mainLayout->addWidget(penWidthSpinBox, 1, 4, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(fontSizeSpinBox, 3, 4, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(textStringLineEdit, 0, 4, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);

    connect(shapeTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(shapeTypeChanged()));
    connect(addShapeButton, SIGNAL(clicked(bool)), this, SLOT(addShape()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    setLayout(mainLayout);
    setWindowTitle("Shape Manager");
    setMinimumSize(600, 300);
    setMaximumSize(600, 300);
    shapeTypeChanged();
}

AddShape::~AddShape()
{
    delete mainLayout;

    delete shapeHeaderLabel[0];
    delete shapeHeaderLabel[1];
    delete shapeIDComboBox;
    delete shapeTypeComboBox;

    for(int i = 0; i < shapeDescriptionCount; ++i)
    {
        delete shapeDescriptionLabel[i];
        delete shapeDescriptionComboBox[i];
    }

    delete penWidthSpinBox;
    delete fontSizeSpinBox;
    delete textStringLineEdit;

    delete addShapeButton;
    delete cancelButton;
}

void AddShape::passParams(Vector<Shape*>* shapes)
{
    shapeVector = shapes;

    for(Vector<Shape*>::iterator it = shapeVector->begin(); it != shapeVector->end(); ++it)
        shapeIDComboBox->removeItem((*it)->getID() - 1);
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

        penWidthSpinBox->hide();
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
        fontSizeSpinBox->show();

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
        penWidthSpinBox->show();

        shapeDescriptionComboBox[2]->addItem("Solid");
        shapeDescriptionComboBox[2]->addItem("Dashed");
        shapeDescriptionComboBox[2]->addItem("Dotted");
        shapeDescriptionComboBox[2]->addItem("Dashed/Dotted");
        shapeDescriptionComboBox[2]->addItem("Dashed/Dotted/Dotted");

        fontSizeSpinBox->hide();
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
}

bool AddShape::verifyShape()
{
    return true;
}

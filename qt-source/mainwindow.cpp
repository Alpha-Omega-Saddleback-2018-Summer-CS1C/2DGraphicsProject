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
    File: mainwindow.cpp

    Defines a main window
 */

#include <QtWidgets>
#include "mainwindow.h"
#include "parser.h"

/*
 *  Helper functions
 */

/* Returns pen color as a QString */
static QString getPenColorAsQString(QColor color)
{
    if(color == QColor("white"))            return QString("White");
    else if(color == QColor("black"))       return QString("Black");
    else if(color == QColor("red"))         return QString("Red");
    else if(color == QColor("green"))       return QString("Green");
    else if(color == QColor("blue"))        return QString("Blue");
    else if(color == QColor("cyan"))        return QString("Cyan");
    else if(color == QColor("magenta"))     return QString("Magenta");
    else if(color == QColor("yellow"))      return QString("Yellow");
    else /* color == QColor("gray") */      return QString("Gray");
}

/* Returns pen style as a QString */
QString getPenStyleAsQString(Qt::PenStyle style)
{
    if(style == Qt::SolidLine)              return QString("Solid");
    else if(style == Qt::DashLine)          return QString("Dashed");
    else if(style == Qt::DotLine)           return QString("Dotted");
    else if(style == Qt::DashDotLine)       return QString("Dashed/Dotted");
    else /* style == Qt::DashDotDotLine */  return QString("Dashed/Dotted/Dotted");
}

/* Returns pen cap style as a QString */
QString getPenCapStyleAsQString(Qt::PenCapStyle style)
{
    if(style == Qt::SquareCap)          return QString("Square");
    else if(style == Qt::FlatCap)       return QString("Flat");
    else /* style == Qt::RoundCap */    return QString("Round");
}

/* Returns pen join style as a QString */
QString getPenJoinStyleAsQString(Qt::PenJoinStyle style)
{
    if(style == Qt::MiterJoin)          return QString("Miter");
    else if(style == Qt::BevelJoin)     return QString("Bevel");
    else /* style == Qt::RoundJoin */   return QString("Round");
}

/*
 *  Class definitions
 */

MainWindow::MainWindow()
{
    renderArea = new RenderArea;

    /* Left-side */
    shapeComboBox = new QComboBox;   
    addShapeButton = new QPushButton("Add Shape", this);
    editShapeButton = new QPushButton("Edit Shape", this);
    deleteShapeButton = new QPushButton("Delete Shape", this);

    selectedShapeLabel = new QLabel("Selected Shape:");
    selectedShapeLabel->setBuddy(shapeComboBox);

    /* Right-side (general) */
    shapeIDLabel = new QLabel("Shape ID:");
    shapeTypeLabel = new QLabel("Shape Type:");

    /* Right-side (non-text) */

    penColorLabel = new QLabel("Pen Color:");
    penWidthLabel = new QLabel("Pen Width:");
    penStyleLabel = new QLabel("Pen Style:");
    penCapStyleLabel = new QLabel("Pen Cap Style:");
    penJoinStyleLabel = new QLabel("Pen Join Style:");
    brushColorLabel = new QLabel("Brush Color:");
    brushStyleLabel = new QLabel("Brush Style:");

    /* Right-side (text) */
    textStringLabel = new QLabel("Text:");
    textColorLabel = new QLabel("Text Color:");
    textAlignmentLabel = new QLabel("Text Alignment:");
    textPointSizeLabel = new QLabel("Font Size:");
    textFontFamilyLabel = new QLabel("Font Family:");
    textFontStyleLabel = new QLabel("Font Style:");
    textFontWeightLabel = new QLabel("Font Weight:");

    /* Layout */

    leftSideLayout = new QGridLayout;
    leftSideLayout->addWidget(selectedShapeLabel, 0, 0, 1, 1);
    leftSideLayout->addWidget(shapeComboBox, 0, 1, 1, 2);
    leftSideLayout->addWidget(addShapeButton, 1, 0, 1, 3);
    leftSideLayout->addWidget(editShapeButton, 2, 0, 1, 3);
    leftSideLayout->addWidget(deleteShapeButton, 3, 0, 1, 3);
    leftSideLayout->setContentsMargins(100, 10, 100, 10);

    rightSideLayout = new QGridLayout;
    rightSideLayout->addWidget(shapeIDLabel, 0, 0, 1, 1);
    rightSideLayout->addWidget(shapeTypeLabel, 1, 0, 1, 1);
    rightSideLayout->setContentsMargins(100, 0, 100, 0);

    mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0, 1, 2, Qt::AlignHCenter);
    mainLayout->addLayout(leftSideLayout, 1, 0, 1, 1);
    mainLayout->addLayout(rightSideLayout, 1, 1, 1, 1);

    setLayout(mainLayout);
    setWindowTitle("Basic Drawing");
    setMinimumSize(1100, 800);
    setMaximumSize(1100, 800);
}

void MainWindow::addShapes(Vector<Shape*>* shapes)
{
    renderArea->addShapeVector(shapes);
    shapeVector = shapes;
    for(Vector<Shape*>::iterator it = shapeVector->begin(); it != shapeVector->end(); ++it)
    {
        shapeComboBox->addItem(QString::number((*it)->getID()) + " - " + (*it)->getTypeAsQString());
    }

    Shape* shape = (*shapeVector)[0];

    shapeIDValueLabel = new QLabel(QString::number(shape->getID()));
    shapeTypeValueLabel = new QLabel(shape->getTypeAsQString());
    rightSideLayout->addWidget(shapeIDValueLabel, 0, 1, 1, 2);
    rightSideLayout->addWidget(shapeTypeValueLabel, 1, 1, 1, 2);

    if(shape->getTypeAsQString() == "Text")
    {
        /* Labels */
        rightSideLayout->addWidget(textStringLabel, 0, 0, 1, 1);
        rightSideLayout->addWidget(textColorLabel, 1, 0, 1, 1);
        rightSideLayout->addWidget(textAlignmentLabel, 2, 0, 1, 1);
        rightSideLayout->addWidget(textPointSizeLabel, 3, 0, 1, 1);
        rightSideLayout->addWidget(textFontFamilyLabel, 4, 0, 1, 1);
        rightSideLayout->addWidget(textFontStyleLabel, 5, 0, 1, 1);
        rightSideLayout->addWidget(textFontWeightLabel, 6, 0, 1, 1);

        /* Values */

    }
    else
    {
        /* Labels */
        rightSideLayout->addWidget(penColorLabel, 2, 0, 1, 1);
        rightSideLayout->addWidget(penWidthLabel, 3, 0, 1, 1);
        rightSideLayout->addWidget(penStyleLabel, 4, 0, 1, 1);
        rightSideLayout->addWidget(penCapStyleLabel, 5, 0, 1, 1);
        rightSideLayout->addWidget(penJoinStyleLabel, 6, 0, 1, 1);
        rightSideLayout->addWidget(brushColorLabel, 7, 0, 1, 1);
        rightSideLayout->addWidget(brushStyleLabel, 8, 0, 1, 1);

        /* Values */
        penColorValueLabel = new QLabel(getPenColorAsQString(shape->getPen().color()));
        penWidthValueLabel = new QLabel(QString::number(shape->getPen().width()));
        penStyleValueLabel = new QLabel(getPenStyleAsQString(shape->getPen().style()));
        penCapStyleValueLabel = new QLabel(getPenCapStyleAsQString(shape->getPen().capStyle()));
        penJoinStyleValueLabel = new QLabel(getPenJoinStyleAsQString(shape->getPen().joinStyle()));

        rightSideLayout->addWidget(penColorValueLabel, 2, 1, 1, 2);
        rightSideLayout->addWidget(penWidthValueLabel, 3, 1, 1, 2);
        rightSideLayout->addWidget(penStyleValueLabel, 4, 1, 1, 2);
        rightSideLayout->addWidget(penCapStyleValueLabel, 5, 1, 1, 2);
        rightSideLayout->addWidget(penJoinStyleValueLabel, 6, 1, 1, 2);
    }
}

MainWindow::~MainWindow()
{
    delete renderArea;

    delete selectedShapeLabel;
    delete shapeComboBox;
    delete addShapeButton;
    delete editShapeButton;
    delete deleteShapeButton;

    delete shapeIDLabel;
    delete shapeIDValueLabel;
    delete shapeTypeLabel;
    delete shapeTypeValueLabel;

    delete penColorLabel;
    delete penColorValueLabel;
    delete penWidthLabel;
    delete penWidthValueLabel;
    delete penStyleLabel;
    delete penStyleValueLabel;
    delete penCapStyleLabel;
    delete penCapStyleValueLabel;
    delete penJoinStyleLabel;
    delete penJoinStyleValueLabel;
    delete brushColorLabel;
    delete brushColorValueLabel;
    delete brushStyleLabel;
    delete brushStyleValueLabel;

    delete textStringLabel;
    delete textStringValueLabel;
    delete textColorLabel;
    delete textColorValueLabel;
    delete textAlignmentLabel;
    delete textAlignmentValueLabel;
    delete textPointSizeLabel;
    delete textPointSizeValueLabel;
    delete textFontFamilyLabel;
    delete textFontFamilyValueLabel;
    delete textFontStyleLabel;
    delete textFontStyleValueLabel;
    delete textFontWeightLabel;
    delete textFontWeightValueLabel;
}

void MainWindow::shapeChanged()
{

}

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
#include "textbox.h"

/*
 *  Helper functions
 */

/* Returns QColor as a QString */
static QString getQColorAsQString(QColor color)
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

/* Returns PenStyle as a QString */
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

/* Returns brush style as a QString */
QString getBrushStyleAsQString(Qt::BrushStyle style)
{
    if(style == Qt::NoBrush)            return QString("None");
    else if(style == Qt::SolidPattern)  return QString("Solid");
    else if(style == Qt::HorPattern)    return QString("Horizontal Lines");
    else /* style == Qt::VerPattern */  return QString("Vertical Lines");
}

/*
 *  Class definitions
 */

MainWindow::MainWindow()
{
    renderArea = new RenderArea;

    /* Left-side */
    selectedShapeLabel = new QLabel("Selected Shape:");
    shapeComboBox = new QComboBox;   
    addShapeButton = new QPushButton("Add Shape", this);
    editShapeButton = new QPushButton("Edit Shape", this);
    deleteShapeButton = new QPushButton("Delete Shape", this);

    leftSideLayout = new QGridLayout;
    leftSideLayout->addWidget(selectedShapeLabel, 0, 0, 1, 1);
    leftSideLayout->addWidget(shapeComboBox, 0, 1, 1, 2);
    leftSideLayout->addWidget(addShapeButton, 1, 0, 1, 3);
    leftSideLayout->addWidget(editShapeButton, 2, 0, 1, 3);
    leftSideLayout->addWidget(deleteShapeButton, 3, 0, 1, 3);
    leftSideLayout->setContentsMargins(100, 10, 100, 10);

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

    /* Right-side (general) */
    rightSideLayout = new QGridLayout;
    rightSideLayout->addWidget(shapeIDLabel, 0, 0, 1, 1);
    rightSideLayout->addWidget(shapeTypeLabel, 1, 0, 1, 1);

    for(int i = 0; i < shapeDimensionLabelCount; ++i)
    {
        shapeDimensionLabels[i] = new QLabel;
        rightSideLayout->addWidget(shapeDimensionLabels[i], (i / 2) + 2, i % 2);
    }

    /* Layout */
    mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0, 1, 2, Qt::AlignHCenter);
    mainLayout->addLayout(leftSideLayout, 1, 0, 1, 1);
    mainLayout->addLayout(rightSideLayout, 1, 1, 1, 1);

    setLayout(mainLayout);
    setWindowTitle("Basic Drawing");
    setMinimumSize(1100, 800);
    setMaximumSize(1100, 800);
}

void MainWindow::addShapes(Vector<Shape*>& shapes)
{
    shapeVector = shapes;

    renderArea->addShapeVector(shapes);
    for(Vector<Shape*>::iterator it = shapeVector.begin(); it != shapeVector.end(); ++it)
        shapeComboBox->addItem(QString::number((*it)->getID()) + " - " + (*it)->getTypeAsQString());

    Shape* shape = shapeVector[0];
    Vector<QString> dimensionLabels = shape->dimensionLabels();

    shapeIDValueLabel = new QLabel(QString::number(shape->getID()));
    shapeTypeValueLabel = new QLabel(shape->getTypeAsQString());
    rightSideLayout->addWidget(shapeIDValueLabel, 0, 1, 1, 2);
    rightSideLayout->addWidget(shapeTypeValueLabel, 1, 1, 1, 2);

    for(int i = 0; i < dimensionLabels.size(); ++i)
        shapeDimensionLabels[i]->setText(dimensionLabels[i]);

    if(shape->getType() == TEXTBOX)
    {
        TextBox* textBox = dynamic_cast<TextBox*>(shape);

        /* Labels */
        rightSideLayout->addWidget(textStringLabel, 0, 4, 1, 1);
        rightSideLayout->addWidget(textColorLabel, 1, 4, 1, 1);
        rightSideLayout->addWidget(textAlignmentLabel, 2, 4, 1, 1);
        rightSideLayout->addWidget(textPointSizeLabel, 3, 4, 1, 1);
        rightSideLayout->addWidget(textFontFamilyLabel, 4, 4, 1, 1);
        rightSideLayout->addWidget(textFontStyleLabel, 5, 4, 1, 1);
        rightSideLayout->addWidget(textFontWeightLabel, 6, 4, 1, 1);

        /* Values */
        textStringValueLabel = new QLabel(textBox->getText());
        textColorValueLabel = new QLabel(getQColorAsQString(textBox->getPen().color()));
        textAlignmentValueLabel = new QLabel;
        textPointSizeValueLabel = new QLabel;
        textFontFamilyValueLabel = new QLabel;
        textFontStyleValueLabel = new QLabel;
        textFontWeightValueLabel = new QLabel;
        penColorValueLabel = new QLabel;
        penWidthValueLabel = new QLabel;
        penStyleValueLabel = new QLabel;
        penCapStyleValueLabel = new QLabel;
        penJoinStyleValueLabel = new QLabel;
        brushColorValueLabel = new QLabel;
        brushStyleValueLabel = new QLabel;

        rightSideLayout->addWidget(textStringValueLabel, 0, 5, 1, 3);
        rightSideLayout->addWidget(textColorValueLabel, 1, 5, 1, 3);
        rightSideLayout->addWidget(textAlignmentValueLabel, 2, 5, 1, 3);
        rightSideLayout->addWidget(textPointSizeValueLabel, 3, 5, 1, 3);
        rightSideLayout->addWidget(textFontFamilyValueLabel, 4, 5, 1, 3);
        rightSideLayout->addWidget(textFontStyleValueLabel, 5, 5, 1, 3);
        rightSideLayout->addWidget(textFontWeightValueLabel, 6, 5, 1, 3);
    }
    else
    {
        /* Labels */
        rightSideLayout->addWidget(penColorLabel, 0, 4, 1, 1);
        rightSideLayout->addWidget(penWidthLabel, 1, 4, 1, 1);
        rightSideLayout->addWidget(penStyleLabel, 2, 4, 1, 1);
        rightSideLayout->addWidget(penCapStyleLabel, 3, 4, 1, 1);
        rightSideLayout->addWidget(penJoinStyleLabel, 4, 4, 1, 1);
        rightSideLayout->addWidget(brushColorLabel, 5, 4, 1, 1);
        rightSideLayout->addWidget(brushStyleLabel, 6, 4, 1, 1);

        /* Values */
        penColorValueLabel = new QLabel(getQColorAsQString(shape->getPen().color()));
        penWidthValueLabel = new QLabel(QString::number(shape->getPen().width()));
        penStyleValueLabel = new QLabel(getPenStyleAsQString(shape->getPen().style()));
        penCapStyleValueLabel = new QLabel(getPenCapStyleAsQString(shape->getPen().capStyle()));
        penJoinStyleValueLabel = new QLabel(getPenJoinStyleAsQString(shape->getPen().joinStyle()));
        brushColorValueLabel = new QLabel(getQColorAsQString(shape->getBrush().color()));
        brushStyleValueLabel = new QLabel(getBrushStyleAsQString(shape->getBrush().style()));
        textStringValueLabel = new QLabel;
        textColorValueLabel = new QLabel;
        textAlignmentValueLabel = new QLabel;
        textPointSizeValueLabel = new QLabel;
        textFontFamilyValueLabel = new QLabel;
        textFontStyleValueLabel = new QLabel;
        textFontWeightValueLabel = new QLabel;

        rightSideLayout->addWidget(penColorValueLabel, 0, 5, 1, 3);
        rightSideLayout->addWidget(penWidthValueLabel, 1, 5, 1, 3);
        rightSideLayout->addWidget(penStyleValueLabel, 2, 5, 1, 3);
        rightSideLayout->addWidget(penCapStyleValueLabel, 3, 5, 1, 3);
        rightSideLayout->addWidget(penJoinStyleValueLabel, 4, 5, 1, 3);
        rightSideLayout->addWidget(brushColorValueLabel, 5, 5, 1, 3);
        rightSideLayout->addWidget(brushStyleValueLabel, 6, 5, 1, 3);
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

    for(int i = 0; i < shapeDimensionLabelCount; ++i)
        delete shapeDimensionLabels[i];
}

void MainWindow::shapeChanged()
{

}

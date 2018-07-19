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

/* Returns brush style as a QString */
QString getBrushStyleAsQString(Qt::BrushStyle style)
{
    if(style == Qt::NoBrush)            return QString("None");
    else if(style == Qt::SolidPattern)  return QString("Solid");
    else if(style == Qt::HorPattern)    return QString("Horizontal Lines");
    else /* style == Qt::VerPattern */  return QString("Vertical Lines");
}

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

/* Returns PenStyle as a QString */
QString getPenStyleAsQString(Qt::PenStyle style)
{
    if(style == Qt::SolidLine)              return QString("Solid");
    else if(style == Qt::DashLine)          return QString("Dashed");
    else if(style == Qt::DotLine)           return QString("Dotted");
    else if(style == Qt::DashDotLine)       return QString("Dashed/Dotted");
    else /* style == Qt::DashDotDotLine */  return QString("Dashed/Dotted/Dotted");
}

/* Returns brush style as a QString */
QString getTextAlignmentAsQString(int alignment)
{
    if(alignment == Qt::AlignLeft)          return QString("Left");
    else if(alignment == Qt::AlignRight)    return QString("Right");
    else if(alignment == Qt::AlignTop)      return QString("Top");
    else if(alignment == Qt::AlignBottom)   return QString("Bottom");
    else /* alignment == Qt::AlignCenter */     return QString("Center");
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

    /* Right-side */
    rightSideLayout = new QGridLayout;

    shapeHeaderLabels[0] = new QLabel("Shape ID:");
    shapeHeaderLabels[1] = new QLabel;
    shapeHeaderLabels[2] = new QLabel("Shape Type:");
    shapeHeaderLabels[3] = new QLabel;

    rightSideLayout->addWidget(shapeHeaderLabels[0], 0, 0, 1, 1);
    rightSideLayout->addWidget(shapeHeaderLabels[1], 0, 1, 1, 3);
    rightSideLayout->addWidget(shapeHeaderLabels[2], 1, 0, 1, 1);
    rightSideLayout->addWidget(shapeHeaderLabels[3], 1, 1, 1, 3);

    for(int i = 0; i < shapeDimensionLabelCount; ++i)
    {
        shapeDimensionLabels[i] = new QLabel;
        rightSideLayout->addWidget(shapeDimensionLabels[i], (i / 2) + 2, i % 2, 1, 1);
    }

    for(int i = 0; i < shapeDescriptionLabelCount / 2; ++i)
    {
        shapeDescriptionLabels[2 * i] = new QLabel;
        shapeDescriptionLabels[2 * i + 1] = new QLabel;
        rightSideLayout->addWidget(shapeDescriptionLabels[2 * i], i, 4, 1, 1);
        rightSideLayout->addWidget(shapeDescriptionLabels[2 * i + 1], i, 5, 1, 3);
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

    shapeHeaderLabels[1] = new QLabel(QString::number(shape->getID()));
    shapeHeaderLabels[3] = new QLabel(shape->getTypeAsQString());
    rightSideLayout->addWidget(shapeHeaderLabels[1], 0, 1, 1, 2);
    rightSideLayout->addWidget(shapeHeaderLabels[3], 1, 1, 1, 2);

    for(int i = 0; i < dimensionLabels.size(); ++i)
        shapeDimensionLabels[i]->setText(dimensionLabels[i]);

    if(shape->getType() == TEXTBOX)
    {
        TextBox* textBox = dynamic_cast<TextBox*>(shape);

        /* Labels */
        shapeDescriptionLabels[0]->setText("Text:");
        shapeDescriptionLabels[2]->setText("Text Color:");
        shapeDescriptionLabels[4]->setText("Text Alignment:");
        shapeDescriptionLabels[6]->setText("Text Size:");
        shapeDescriptionLabels[8]->setText("Font Family:");
        shapeDescriptionLabels[10]->setText("Font Style:");
        shapeDescriptionLabels[12]->setText("Font Weight:");

        /* Values */
        shapeDescriptionLabels[1]->setText(textBox->getText());
        shapeDescriptionLabels[3]->setText(getQColorAsQString(textBox->getBrush().color()));
        shapeDescriptionLabels[5]->setText("");
        shapeDescriptionLabels[7]->setText(QString::number(textBox->getFont().pointSize()));
        shapeDescriptionLabels[9]->setText("");
        shapeDescriptionLabels[11]->setText("");
        shapeDescriptionLabels[13]->setText("");
    }
    else
    {
        /* Labels */
        shapeDescriptionLabels[0]->setText("Pen Color:");
        shapeDescriptionLabels[2]->setText("Pen Width:");
        shapeDescriptionLabels[4]->setText("Pen Style:");
        shapeDescriptionLabels[6]->setText("Pen Cap Style:");
        shapeDescriptionLabels[8]->setText("Pen Join Style:");
        shapeDescriptionLabels[10]->setText("Brush Color:");
        shapeDescriptionLabels[12]->setText("Brush Style:");

        /* Values */
        shapeDescriptionLabels[1]->setText(getQColorAsQString(shape->getPen().color()));
        shapeDescriptionLabels[3]->setText(QString::number(shape->getPen().width()));
        shapeDescriptionLabels[5]->setText(getPenStyleAsQString(shape->getPen().style()));
        shapeDescriptionLabels[7]->setText(getPenCapStyleAsQString(shape->getPen().capStyle()));
        shapeDescriptionLabels[9]->setText(getPenJoinStyleAsQString(shape->getPen().joinStyle()));
        shapeDescriptionLabels[11]->setText(getQColorAsQString(shape->getBrush().color()));
        shapeDescriptionLabels[13]->setText(getBrushStyleAsQString(shape->getBrush().style()));
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

    for(int i = 0; i < shapeHeaderLabelCount; ++i)
        delete shapeHeaderLabels[i];

    for(int i = 0; i < shapeDimensionLabelCount; ++i)
        delete shapeDimensionLabels[i];

    for(int i = 0; i < shapeDescriptionLabelCount; ++i)
        delete shapeDescriptionLabels[i];
}

void MainWindow::shapeChanged()
{

}

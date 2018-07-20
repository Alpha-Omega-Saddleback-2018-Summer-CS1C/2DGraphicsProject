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
    File: mainwindow.cpp

    Defines a main window
 */

#include <string>
#include <QMessageBox>
#include <QtWidgets>
#include "login.h"
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
    else if(style == Qt::VerPattern)    return QString("Vertical Lines");
    else                                return QString("--");
}

/* Returns font weight as a QString */
QString getFontStyleAsQString(QFont::Style style)
{
    if(style == QFont::StyleNormal)         return QString("Normal");
    else if(style == QFont::StyleItalic)    return QString("Italic");
    else if(style == QFont::StyleOblique)   return QString("Oblique");
    else                                    return QString("--");
}

/* Returns font style as a QString */
QString getFontWeightAsQString(int weight)
{
    if(weight == QFont::Thin)           return QString("Thin");
    else if(weight == QFont::Light)     return QString("Light");
    else if(weight == QFont::Normal)    return QString("Normal");
    else if(weight == QFont::Bold)      return QString("Bold");
    else                                return QString("--");
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
    else if(color == QColor("gray"))        return QString("Gray");
    else                                    return QString("--");
}

/* Returns pen cap style as a QString */
QString getPenCapStyleAsQString(Qt::PenCapStyle style)
{
    if(style == Qt::SquareCap)          return QString("Square");
    else if(style == Qt::FlatCap)       return QString("Flat");
    else if(style == Qt::RoundCap)      return QString("Round");
    else                                return QString("--");
}

/* Returns pen join style as a QString */
QString getPenJoinStyleAsQString(Qt::PenJoinStyle style)
{
    if(style == Qt::MiterJoin)          return QString("Miter");
    else if(style == Qt::BevelJoin)     return QString("Bevel");
    else if(style == Qt::RoundJoin)     return QString("Round");
    else                                return QString("--");
}

/* Returns PenStyle as a QString */
QString getPenStyleAsQString(Qt::PenStyle style)
{
    if(style == Qt::SolidLine)              return QString("Solid");
    else if(style == Qt::DashLine)          return QString("Dashed");
    else if(style == Qt::DotLine)           return QString("Dotted");
    else if(style == Qt::DashDotLine)       return QString("Dashed/Dotted");
    else if(style == Qt::DashDotDotLine)    return QString("Dashed/Dotted/Dotted");
    else                                    return QString("--");
}

/* Returns brush style as a QString */
QString getTextAlignmentAsQString(int alignment)
{
    if(alignment == Qt::AlignLeft)          return QString("Left");
    else if(alignment == Qt::AlignRight)    return QString("Right");
    else if(alignment == Qt::AlignTop)      return QString("Top");
    else if(alignment == Qt::AlignBottom)   return QString("Bottom");
    else if(alignment == Qt::AlignCenter)   return QString("Center");
    else                                    return QString("--");
}

/* Trims the QString if necessary */
QString getTextStringTrimmed(const QString& str)
{
    if(str.length() > 30)
    {
        std::string tmp = str.toUtf8().constData();
        tmp = tmp.substr(0, 27);
        tmp += "...";
        return QString(tmp.c_str());
    }

    return QString(str);
}

/*
 *  Class definitions
 */

MainWindow::MainWindow()
{
    renderArea = new RenderArea;
    userManager = nullptr;

    /* Left-side */
    selectedShapeLabel = new QLabel("Selected Shape:");
    shapeComboBox = new QComboBox;   
    addShapeButton = new QPushButton("Add Shape", this);
    editShapeButton = new QPushButton("Edit Shape", this);
    deleteShapeButton = new QPushButton("Delete Shape", this);
    userManagerButton = new QPushButton("User Manager", this);
    logoutButton = new QPushButton("Logout", this);

    leftSideLayout = new QGridLayout;
    leftSideLayout->addWidget(selectedShapeLabel, 0, 0, 1, 1);
    leftSideLayout->addWidget(shapeComboBox, 0, 1, 1, 2);
    leftSideLayout->addWidget(addShapeButton, 1, 1, 1, 2);
    leftSideLayout->addWidget(editShapeButton, 2, 1, 1, 2);
    leftSideLayout->addWidget(deleteShapeButton, 3, 1, 1, 2);
    leftSideLayout->addWidget(userManagerButton, 4, 1, 1, 1);
    leftSideLayout->addWidget(logoutButton, 4, 2, 1, 1);
    leftSideLayout->setContentsMargins(100, 10, 100, 10);

    /* Right-side */
    shapeHeaderLabels[0] = new QLabel("Shape ID:");
    shapeHeaderLabels[1] = new QLabel;
    shapeHeaderLabels[2] = new QLabel("Shape Type:");
    shapeHeaderLabels[3] = new QLabel;

    rightSideLayout = new QGridLayout;
    rightSideLayout->addWidget(shapeHeaderLabels[0], 0, 0, 1, 1);
    rightSideLayout->addWidget(shapeHeaderLabels[1], 0, 1, 1, 2);
    rightSideLayout->addWidget(shapeHeaderLabels[2], 1, 0, 1, 1);
    rightSideLayout->addWidget(shapeHeaderLabels[3], 1, 1, 1, 2);

    for(int i = 0; i < shapeDimensionLabelCount / 2; ++i)
    {
        shapeDimensionLabels[2 * i] = new QLabel;
        shapeDimensionLabels[2 * i + 1] = new QLabel;
        rightSideLayout->addWidget(shapeDimensionLabels[2 * i], i + 2, 0, 1, 1);
        rightSideLayout->addWidget(shapeDimensionLabels[2 * i + 1], i + 2, 1, 1, 2);
    }

    for(int i = 0; i < shapeDescriptionLabelCount / 2; ++i)
    {
        shapeDescriptionLabels[2 * i] = new QLabel;
        shapeDescriptionLabels[2 * i + 1] = new QLabel;
        rightSideLayout->addWidget(shapeDescriptionLabels[2 * i], i, 3, 1, 1);
        rightSideLayout->addWidget(shapeDescriptionLabels[2 * i + 1], i, 4, 1, 4);
    }

    /* Layout */
    mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0, 1, 2, Qt::AlignHCenter);
    mainLayout->addLayout(leftSideLayout, 1, 0, 1, 1);
    mainLayout->addLayout(rightSideLayout, 1, 1, 1, 1);

    connect(userManagerButton, SIGNAL(clicked(bool)), this, SLOT(createUserManager()));
    connect(shapeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateShapeInfo()));
    connect(deleteShapeButton, SIGNAL(clicked(bool)), this, SLOT(deleteShape()));

    setLayout(mainLayout);
    setWindowTitle("2D Graphics Project Program");
    setMinimumSize(1100, 800);
    setMaximumSize(1100, 800);
}

void MainWindow::passParams(Login* login, Vector<Shape*>* shapes, Vector<User>* users, User* user)
{
    loginWindow = login;
    shapeVector = shapes;
    userVector = users;
    currentUser = user;

    connect(logoutButton, SIGNAL(clicked(bool)), loginWindow, SLOT(closeMainWindow()));

    renderArea->addShapeVector(shapes);
    for(Vector<Shape*>::iterator it = shapeVector->begin(); it != shapeVector->end(); ++it)
        shapeComboBox->addItem(QString::number((*it)->getID()) + " - " + (*it)->getTypeAsQString());
}

MainWindow::~MainWindow()
{
    delete renderArea;
    delete userManager;

    delete selectedShapeLabel;
    delete shapeComboBox;
    delete addShapeButton;
    delete editShapeButton;
    delete deleteShapeButton;

    delete userManagerButton;
    delete logoutButton;

    for(int i = 0; i < shapeHeaderLabelCount; ++i)
        delete shapeHeaderLabels[i];

    for(int i = 0; i < shapeDimensionLabelCount; ++i)
        delete shapeDimensionLabels[i];

    for(int i = 0; i < shapeDescriptionLabelCount; ++i)
        delete shapeDescriptionLabels[i];
}

void MainWindow::createUserManager()
{
    if(!currentUser->mIsAdmin)
    {
        QMessageBox::information(this, "Shape Manager",
                "Current user is not an adminstrator!", QMessageBox::Ok);
        return;
    }

    if(userManager)
    {
        userManager->close();
        delete userManager;
    }

    userManager = new UserManager();
    userManager->passParams(userVector, currentUser);
    userManager->show();
}

void MainWindow::deleteShape()
{
    if(!currentUser->mIsAdmin)
    {
        QMessageBox::information(this, "Shape Manager",
                "Current user is not an adminstrator!", QMessageBox::Ok);
        return;
    }

    if(shapeVector->size() == 0)
    {
        QMessageBox::information(this, "Shape Manager",
                "There are no shapes to delete!", QMessageBox::Ok);
        return;
    }

    int offset = shapeComboBox->currentIndex();
    int clickedButton = QMessageBox::question(this, "Shape Manager",
        "Are you sure you want to delete this shape?", QMessageBox::Ok | QMessageBox::Cancel);

    if(clickedButton == QMessageBox::Ok)
    {
        Vector<Shape*>::iterator it = shapeVector->begin() + offset;
        delete (*it);
        shapeVector->erase(it);
        shapeComboBox->removeItem(offset);
    }
}

void MainWindow::updateShapeInfo()
{
    if(shapeVector->size() == 0)
    {
        shapeHeaderLabels[1]->setText("--");
        shapeHeaderLabels[3]->setText("--");

        for(int i = 0; i < shapeDimensionLabelCount; ++i)
            shapeDimensionLabels[i]->setText("");

        for(int i = 0; i < shapeDescriptionLabelCount / 2; ++i)
            shapeDescriptionLabels[2 * i + 1]->setText("--");

        return;
    }

    Shape* shape = (*shapeVector)[shapeComboBox->currentIndex()];
    Vector<QString> dimensionLabels = shape->dimensionLabels();
    int i = 0;

    for(; i < dimensionLabels.size(); ++i)
        shapeDimensionLabels[i]->setText(dimensionLabels[i]);

    for(; i < shapeDimensionLabelCount; ++i)
        shapeDimensionLabels[i]->setText("");

    shapeHeaderLabels[1]->setText(QString::number(shape->getID()));
    shapeHeaderLabels[3]->setText(shape->getTypeAsQString());

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
        shapeDescriptionLabels[1]->setText(getTextStringTrimmed(textBox->getText()));
        shapeDescriptionLabels[3]->setText(getQColorAsQString(textBox->getBrush().color()));
        shapeDescriptionLabels[5]->setText(getTextAlignmentAsQString(textBox->getAlignment()));
        shapeDescriptionLabels[7]->setText(QString::number(textBox->getFont().pointSize()));
        shapeDescriptionLabels[9]->setText(textBox->getFont().family());
        shapeDescriptionLabels[11]->setText(getFontStyleAsQString(textBox->getFont().style()));
        shapeDescriptionLabels[13]->setText(getFontWeightAsQString(textBox->getFont().weight()));
    }
    else
    {
        /* Labels */
        shapeDescriptionLabels[0]->setText("Pen Color:");
        shapeDescriptionLabels[2]->setText("Pen Width:");
        shapeDescriptionLabels[4]->setText("Pen Style:");
        shapeDescriptionLabels[6]->setText("Pen Cap Style:");
        shapeDescriptionLabels[8]->setText("Pen Join Style:");

        if(shape->getType() != LINE && shape->getType() != POLYLINE)
        {
            shapeDescriptionLabels[10]->setText("Brush Color:");
            shapeDescriptionLabels[12]->setText("Brush Style:");
        }
        else
        {
            shapeDescriptionLabels[10]->setText("");
            shapeDescriptionLabels[12]->setText("");
        }

        /* Values */
        shapeDescriptionLabels[1]->setText(getQColorAsQString(shape->getPen().color()));
        shapeDescriptionLabels[3]->setText(QString::number(shape->getPen().width()));
        shapeDescriptionLabels[5]->setText(getPenStyleAsQString(shape->getPen().style()));
        shapeDescriptionLabels[7]->setText(getPenCapStyleAsQString(shape->getPen().capStyle()));
        shapeDescriptionLabels[9]->setText(getPenJoinStyleAsQString(shape->getPen().joinStyle()));

        if(shape->getType() != LINE && shape->getType() != POLYLINE)
        {
            shapeDescriptionLabels[11]->setText(getQColorAsQString(shape->getBrush().color()));
            shapeDescriptionLabels[13]->setText(getBrushStyleAsQString(shape->getBrush().style()));
        }
        else
        {
            shapeDescriptionLabels[11]->setText("");
            shapeDescriptionLabels[13]->setText("");
        }
    }
}

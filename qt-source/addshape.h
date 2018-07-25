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
    File: addshape.h

    Defines an "add shape" widget
 */

#ifndef ADDSHAPE_H
#define ADDSHAPE_H

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

/**	Implements a QWidget that allows a user to add a shape to the shape vector.
 *	Upon exiting this widget, the RenderArea QWidget will be updated and the shape
 *	will be rendered.
 */
class AddShape : public QWidget
{
    Q_OBJECT

    static const int shapeDimensionCount = 4;
    static const int shapeDescriptionCount = 7;

public:
	/**	Default constructor. Initializes widgets */
    explicit AddShape(QWidget *parent = nullptr);
	
	/** Destroys all child widgets and layouts */
    ~AddShape();
	
	/**	Passes the shape vector and previous window. */
    void passParams(Vector<Shape*>* shapes, MainWindow* mainWindow);

public slots:

	/** Adds an additional (x, y) input when creating a polyline or polygon. */	
    void addDimensionPoint();
	
	/** Adds a shape to the shape vector and exits the widget. Before exiting, the shape vector will
	 * be sorted numerically by ID.
	 */	
    void addShape();
	
	/** Removes an (x, y) input when creating a polyline or polygon. If there are only two or three points for a
	 *	polyline and polygon, respectively, it will notify the user and will not remove an input.
	 */	
    void removeDimensionPoint();
	
	/** Changes the interface accordingly when the shape type has been changed. */
    void shapeTypeChanged();

private:
    QGridLayout*        mainLayout;

    QLabel*             shapeHeaderLabel[2];
    QComboBox*          shapeIDComboBox;
    QComboBox*          shapeTypeComboBox;

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

    QPushButton*        addShapeButton;
    QPushButton*        cancelButton;

    Vector<Shape*>*     shapeVector;
    MainWindow*         mainWindow;
};

#endif // ADDSHAPE_H

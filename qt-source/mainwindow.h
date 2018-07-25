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
    File: mainwindow.h

    Defines a main window
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "addshape.h"
#include "editShape.h"
#include "custom_vector.h"
#include "renderarea.h"
#include "shape.h"
#include "usermanager.h"
#include "userparser.h"

using shape::Shape;

/* Forward decleration */
class QPushButton;
class QComboBox;
class QLabel;
class QGridLayout;
class Login;

/**	Implements a QWidget that serves as the main application window. It contains the render area and buttons
 *	that will add, edit, and remove shapes as well as open the user manager or logout.
 */
class MainWindow : public QWidget
{
    Q_OBJECT

    static const int shapeHeaderLabelCount = 4;
    static const int shapeDimensionLabelCount = 10;
    static const int shapeDescriptionLabelCount = 14;

public:
	/**	Default constructor. Initializes widgets */
    MainWindow();
	
	/** Destroys all child widgets and layouts */
    ~MainWindow();

	/**	Passes the shape vector, user vector, current user, and previous window */
    void passParams(Login* login, Vector<Shape*>* shapes, Vector<User>* users, User* user);
	
	/** Updates the interface when a new shape is added. */
    void updateShapeList();

private slots:

	/** Opens the AddShape widget if the user is an administrator. */
    void createAddShape();
	
	/** Opens the EditShape widget if the user is an administrator. */
    void createEditShape();
	
	/** Opens the UserManager widget. */
    void createUserManager();
	
	/** Deletes the selected shape if the user is an administrator */
    void deleteShape();
	
	/** Updates the interface when the selected shape is changed. */
    void updateShapeInfo();

private:
    RenderArea*     renderArea;
    QGridLayout*    mainLayout;
    QGridLayout*    leftSideLayout;
    QGridLayout*    rightSideLayout;

    /* Left side */
    QLabel*         selectedShapeLabel;
    QComboBox*      shapeComboBox;
    QPushButton*    addShapeButton;
    QPushButton*    editShapeButton;
    QPushButton*    deleteShapeButton;
    QPushButton*    userManagerButton;
    QPushButton*    logoutButton;

    /* Right-side */
    QLabel*         shapeHeaderLabels[shapeHeaderLabelCount];
    QLabel*         shapeDimensionLabels[shapeDimensionLabelCount];
    QLabel*         shapeDescriptionLabels[shapeDescriptionLabelCount];
    bool            isText;

    Login* loginWindow;
    UserManager* userManager;
    AddShape* addShape;
    EditShape* editShape;

    Vector<Shape*>* shapeVector; // Does not require deletion
    Vector<User>* userVector; // Does not require deletion
    User* currentUser; // Does not require deletion
};

#endif // MAINWINDOW_H

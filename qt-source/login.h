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
    File: login.h

    Defines login window
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "mainwindow.h"
#include "custom_vector.h"
#include "shape.h"
#include "userparser.h"

using shape::Shape;

/** \namespace Ui
 *	
 * 	Created by Qt. All UI-defined widgets are under this namespace
 */
namespace Ui 
{
	/**	External widget created by the QT UI editor that is used by the Login class.
	 *	Manages all widgets and layouts.
  	 */
	class Login;
}

/**	Implements a QWidget that prompts users to login. If there are no users in the user vector,
 * 	the user is logged in under the default user until a new user is created.
 */
class Login : public QMainWindow
{
    Q_OBJECT

public:
	/** Default constructor. Initializes widgets. */
    explicit Login(QWidget *parent = nullptr);
	
	/** Destroys all child widgets and layouts. */
    ~Login();

	/**	Passes the shape vector and the user vector. */
    void passParams(Vector<Shape*>* shapes, Vector<User>* users);

public slots:

	/** Closes the MainWindow widget. This functions is called externally from widgets that have a member
	 *	that points to this object.
	 */
    void closeMainWindow();

private slots:

	/** Verifies login credentials and calls openMainWindow() if the username and password match a given
	 *	user profile.
	 */
    void on_loginButton_clicked();
	
	/** Opens the contact widget */
    void openContactWindow();
	
	/** Opens the MainWindow widget */
    void openMainWindow();

private:
    Ui::Login* ui;
    MainWindow* mainWindow;

    Vector<Shape*>* shapeVector; // Does not require deletion
    Vector<User>* userVector; // Does not require deletion
    User currentUser;
};

#endif // LOGIN_H

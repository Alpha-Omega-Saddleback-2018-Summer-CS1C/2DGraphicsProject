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
    File: adduser.h

    Defines the "Add User" window
 */

#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include "custom_vector.h"
#include "userparser.h"

class UserManager;
class Login;

/** \namespace Ui
 *	
 * 	Created by Qt. All UI-defined widgets are under this namespace
 */
namespace Ui {
	
	/**	External widget created by the QT UI editor that is used by the AddUser class.
	 *	Manages all widgets and layouts.
  	 */
	class AddUser;
}

/**	Implements a QWidget that allows a user to add a user to the user vector. */
class AddUser : public QDialog
{
    Q_OBJECT

public:

	/** Default constructor. Initializes widgets. */
    explicit AddUser(QWidget *parent = 0);
	
	/** Destroys all child widgets and layouts */
    ~AddUser();

	/**	Passes the user vector, previous window, and initial login window. */
    void passParams(Vector<User>* users, UserManager* parentWindow, Login* login);

private slots:

	/** Adds a new user to the user vector if the username is not already taken, and both password inputs 
	 * are the same. If the user is signed in as the default user (no saved users in the user vector),
	 * the created user must be an administrator. Once the new user is created, the user is signed out
	 * of the default user.
	 */
    void on_createNewUserButton_clicked();

private:
    Ui::AddUser*    ui;
    Vector<User>*   userVector;
    UserManager*    userManager;
    Login*          loginWindow;
};

#endif // ADDUSER_H

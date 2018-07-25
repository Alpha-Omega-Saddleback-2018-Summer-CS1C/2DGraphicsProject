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

    Defines the "Edit User" window
 */

#ifndef EDITUSER_H
#define EDITUSER_H

#include <QDialog>
#include "custom_vector.h"
#include "userparser.h"

class UserManager;

/** \namespace Ui
 *	
 * 	Created by Qt. All UI-defined widgets are under this namespace
 */
namespace Ui 
{
	/**	External widget created by the QT UI editor that is used by the AddUser class.
	 *	Manages all widgets and layouts.
  	 */
	class EditUser;
}

/**	Implements a QWidget that allows a user to change the password of a user in the user vector. 
 *  A guest user can only edit their own user profile. An administrator can edit any guest user as
 * 	well as their own, but not another administrators
 */
class EditUser : public QDialog
{
    Q_OBJECT

public:

	/** Default constructor. Initializes widgets. */
    explicit EditUser(QWidget *parent = 0);
	
	/** Destroys all child widgets and layouts */
    ~EditUser();
	
	/**	Passes the user vector, previous window, and initial login window. */
    void passParams(Vector<User>* users, User* user, UserManager* parentWindow);

private slots:

	/** Saves the user if both password inputs are the same. */
    void on_saveUserButton_clicked();

private:
    Ui::EditUser *ui;
    Vector<User>* userVector;
    User* currentUser;
    UserManager* userManager;
};

#endif // ADDUSER_H

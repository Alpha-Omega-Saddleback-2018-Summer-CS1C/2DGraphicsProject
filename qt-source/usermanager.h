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
    File: usermanager.h

    Defines the "User Manager" window
 */

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QDialog>
#include "adduser.h"
#include "edituser.h"
#include "custom_vector.h"
#include "userparser.h"

class Login;

/** \namespace Ui
 *	
 * 	Created by Qt. All UI-defined widgets are under this namespace
 */
namespace Ui 
{
	/**	External widget created by the QT UI editor that is used by the Login class.
	 *	Manages all widgets and layouts.
  	 */
	class UserManager;
}

/**	Implements a QWidget that allows an administrative user to add, edit, or delete users. A guest user is only
 * allowed to edit and delete their own user.
 */
class UserManager : public QDialog
{
    Q_OBJECT

public:
	/** Default constructor. Initializes widgets. */
    explicit UserManager(QWidget *parent = 0);
	
	/** Destroys all child widgets and layouts. */
    ~UserManager();

	/**	Passes the user vector, current user, and Login widget */
    void passParams(Vector<User>* users, User* user, Login* login);
	
	/** Updates the list of users when a new user is added. Sorts users alphabetically. */
    void updateUserList();

private slots:

	/** Opens the AddUser widget if the current user is an adminstrator */
    void on_addUserButton_clicked();
	
	/** Opens the EditUser widget if:
     * 		- The current user is an administrator and is editing a guest user or their own user.
	 *		- The current user is a guest and is editing their own user.
	 */
    void on_editUserButton_clicked();
	
	/** Deletes the selected user if:
     * 		- The current user is an administrator and is editing a guest user or their own user.
	 *		- The current user is a guest and is editing their own user.
	 */
    void on_deleteUserManager_clicked();

private:
    Ui::UserManager *ui;
    AddUser*    adduser;
    EditUser*   edituser;

    Vector<User>* userVector; // Does not require deletion
    User* currentUser; // Does not require deletion
    Login* loginWindow;
};

#endif // USERMANAGER_H

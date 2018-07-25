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
    File: adduser.h

    Defines the "Edit User" window
 */

#ifndef EDITUSER_H
#define EDITUSER_H

#include <QDialog>
#include "custom_vector.h"
#include "userparser.h"

class UserManager;

namespace Ui {
class EditUser;
}

class EditUser : public QDialog
{
    Q_OBJECT

public:
    explicit EditUser(QWidget *parent = 0);
    ~EditUser();

    void passParams(Vector<User>* users, User* user, UserManager* parentWindow);

private slots:
    void on_saveUserButton_clicked();

private:
    Ui::EditUser *ui;
    Vector<User>* userVector;
    User* currentUser;
    UserManager* userManager;
};

#endif // ADDUSER_H

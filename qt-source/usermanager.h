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
#include "custom_vector.h"
#include "userparser.h"

namespace Ui {
class UserManager;
}

class UserManager : public QDialog
{
    Q_OBJECT

public:
    explicit UserManager(QWidget *parent = 0);
    ~UserManager();

    void passParams(Vector<User>& users, User& user);

private slots:
    void on_addUserButton_clicked();

    void on_editUserButton_clicked();

    void on_deleteUserManager_clicked();

private:
    Ui::UserManager *ui;
    AddUser *adduser;

    Vector<User> userVector;
    User currentUser;
};

#endif // USERMANAGER_H

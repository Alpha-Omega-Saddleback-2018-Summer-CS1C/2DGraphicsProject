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

    Defines the "Add User" window
 */

#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include "custom_vector.h"
#include "userparser.h"

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = 0);
    ~AddUser();

    void passParams(Vector<User>& users, User user);

private slots:
    void on_createNewUserButton_clicked();

private:
    Ui::AddUser *ui;
    Vector<User> userVector;
    User currentUser;
};

#endif // ADDUSER_H

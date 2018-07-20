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
    File: deleteuser.h

    Defines the "Delete User" window
 */

#ifndef DELETEUSER_H
#define DELETEUSER_H

#include <QDialog>
#include "custom_vector.h"
#include "userparser.h"

namespace Ui {
class DeleteUser;
}

class DeleteUser : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteUser(QWidget *parent = 0);
    ~DeleteUser();

    void passParams(Vector<User>* users, User* user);

private:
    Ui::DeleteUser *ui;
    Vector<User>* userVector; // Does not require deletion
    User* currentUser; // Does not require deletion
};

#endif // DELETEUSER_H

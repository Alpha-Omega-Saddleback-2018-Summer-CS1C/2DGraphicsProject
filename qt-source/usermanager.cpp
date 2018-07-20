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
    File: usermanager.cpp

    Defines the "User Manager" window
 */

#include "usermanager.h"
#include "ui_usermanager.h"

UserManager::UserManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);
    adduser = nullptr;
}

UserManager::~UserManager()
{
    delete ui;
    if(adduser) delete adduser;
}

void UserManager::passParams(Vector<User>* users, User* user)
{
    userVector = users;
    currentUser = user;

    for(Vector<User>::iterator it = userVector->begin(); it != userVector->end(); ++it)
        ui->userComboBox->addItem(it->mUsername);

}

void UserManager::on_addUserButton_clicked()
{
   adduser = new AddUser;
   adduser->passParams(userVector, currentUser);
   adduser->show();
}

void UserManager::on_editUserButton_clicked()
{
    //go to edit user
}

void UserManager::on_deleteUserManager_clicked()
{
    //go to delete user
}


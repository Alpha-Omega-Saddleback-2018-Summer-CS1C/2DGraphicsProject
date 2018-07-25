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

#include <QtWidgets>
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

void UserManager::on_addUserButton_clicked()
{
    if(!currentUser->mIsAdmin)
    {
        QMessageBox::information(this, "Add User",
                "Current user is not an adminstrator!", QMessageBox::Ok);
        return;
    }

    if(adduser)
        delete adduser;

    adduser = new AddUser;
    adduser->passParams(userVector, currentUser, this);
    adduser->show();
}

void UserManager::on_editUserButton_clicked()
{   
    User& selectedUser = (*userVector)[ui->userComboBox->currentIndex()];

    if(!currentUser->mIsAdmin && selectedUser.mUsername != currentUser->mUsername)
    {
        QMessageBox::information(this, "Edit User",
                "Non-administrators can only edit their own user profile!", QMessageBox::Ok);
        return;
    }

    if(selectedUser.mIsAdmin && selectedUser.mUsername != currentUser->mUsername)
    {
        QMessageBox::information(this, "Edit User",
                "Cannot edit an administrator account that is not your own!", QMessageBox::Ok);
        return;
    }
}

void UserManager::on_deleteUserManager_clicked()
{
    int offset = ui->userComboBox->currentIndex();
    User& selectedUser = (*userVector)[offset];

    if(!currentUser->mIsAdmin)
    {
        QMessageBox::information(this, "Delete User",
                "Current user is not an adminstrator!", QMessageBox::Ok);
        return;
    }

    if(selectedUser.mIsAdmin && selectedUser.mUsername != currentUser->mUsername)
    {
        QMessageBox::information(this, "Delete User",
                "Cannot delete an administrator account that is not your own!", QMessageBox::Ok);
        return;
    }

    int clickedButton = QMessageBox::question(this, "Delete User",
        "Are you sure you want to delete this user?", QMessageBox::Ok | QMessageBox::Cancel);

    if(clickedButton == QMessageBox::Ok)
    {
        if(selectedUser.mUsername == currentUser->mUsername)
        {
            QMessageBox::question(this, "Delete User",
                "You will stay logged in as this user until you exit the program.", QMessageBox::Ok);
        }

        userVector->erase(userVector->begin() + offset);
        ui->userComboBox->removeItem(offset);
    }
}

void UserManager::passParams(Vector<User>* users, User* user, Login* login)
{
    userVector = users;
    currentUser = user;
    loginWindow = login;
    updateUserList();
}

void UserManager::updateUserList()
{
    ui->userComboBox->clear();
    for(Vector<User>::iterator it = userVector->begin(); it != userVector->end(); ++it)
        ui->userComboBox->addItem(it->mUsername);
}

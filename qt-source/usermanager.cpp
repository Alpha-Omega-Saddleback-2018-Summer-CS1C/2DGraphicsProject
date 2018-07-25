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
#include "login.h"

UserManager::UserManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);
    adduser = nullptr;
    edituser = nullptr;
}

UserManager::~UserManager()
{
    delete ui;
    if(adduser) delete adduser;
    if(edituser) delete edituser;
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
    adduser->passParams(userVector, this, loginWindow);
    adduser->show();
}

void UserManager::on_editUserButton_clicked()
{   
    if(userVector->size() == 0)
    {
        QMessageBox::information(this, "Edit User", "No users to edit!", QMessageBox::Ok);
        return;
    }


    int offset = ui->userComboBox->currentIndex();
    User selectedUser = (*userVector)[offset];

    if(!currentUser->mIsAdmin && selectedUser.mUsername != currentUser->mUsername)
    {
        QMessageBox::information(this, "Edit User", "Non-administrators can only edit their own user profile!", QMessageBox::Ok);
        return;
    }

    if(selectedUser.mIsAdmin && selectedUser.mUsername != currentUser->mUsername)
    {
        QMessageBox::information(this, "Edit User", "Cannot edit an administrator account that is not your own!", QMessageBox::Ok);
        return;
    }

    if(edituser)
        delete edituser;

    edituser = new EditUser;
    edituser->passParams(userVector, userVector->begin() + offset, this);
    edituser->show();
}

void UserManager::on_deleteUserManager_clicked()
{
    if(userVector->size() == 0)
    {
        QMessageBox::information(this, "Delete User", "No users to delete!", QMessageBox::Ok);
        return;
    }

    int offset = ui->userComboBox->currentIndex();
    User selectedUser = (*userVector)[offset];

    if(!currentUser->mIsAdmin && selectedUser.mUsername != currentUser->mUsername)
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
        userVector->erase(userVector->begin() + offset);
        ui->userComboBox->removeItem(offset);

        if(selectedUser.mUsername == currentUser->mUsername)
        {
            QMessageBox::information(this, "Logout Notice",
                "Your profile has been deleted. You will be logged out.", QMessageBox::Ok);
            close();
            loginWindow->closeMainWindow();
        }
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
    selection_sort(userVector->begin(), userVector->end(),
        [](User u1, User u2)
        {
            char* s1 = u1.mUsername.toUtf8().data();
            char* s2 = u2.mUsername.toUtf8().data();

            for(int i = 0; s1[i] != '\0'; ++i)
                s1[i] = tolower(s1[i]);

            for(int i = 0; s2[i] != '\0'; ++i)
                s2[i] = tolower(s2[i]);

            return strcmp(s1, s2) > 0;
        });

    ui->userComboBox->clear();
    for(Vector<User>::iterator it = userVector->begin(); it != userVector->end(); ++it)
        ui->userComboBox->addItem(it->mUsername);
}

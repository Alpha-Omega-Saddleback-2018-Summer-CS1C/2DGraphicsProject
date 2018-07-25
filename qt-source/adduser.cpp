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
    File: adduser.cpp

    Defines the "Add User" window
 */

#include <QtWidgets>
#include "adduser.h"
#include "ui_adduser.h"
#include "usermanager.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::passParams(Vector<User>* users, User* user, UserManager* parentWindow)
{
    userVector = users;
    currentUser = user;
    userManager = parentWindow;
}

void AddUser::on_createNewUserButton_clicked()
{
    QString newUser = ui->input_newUser->text();
    QString password1 = ui->input_password1->text();
    QString password2 = ui->input_password2->text();

    if(custom_find(userVector->begin(), userVector->end(), newUser,
        [](User u, QString v) { return u.mUsername == v; }) != userVector->end())
    {
        QMessageBox::information(this, "Action Denied", "Username already taken!", QMessageBox::Ok);
        return;
    }

    if(password1 != password2)
    {
        QMessageBox::information(this, "Action Denied", "Passwords do not match!", QMessageBox::Ok);
        return;
    }

    User user;
    user.mUsername = newUser;
    user.mPassword = password1;
    user.mIsAdmin = ui->checkBox->isChecked();

    userVector->push_back(user);
    userManager->updateUserList();
    close();
}

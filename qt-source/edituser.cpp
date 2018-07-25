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

    Defines the "Edit User" window
 */

#include <QtWidgets>
#include "edituser.h"
#include "ui_edituser.h"
#include "usermanager.h"

EditUser::EditUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUser)
{
    ui->setupUi(this);
}

EditUser::~EditUser()
{
    delete ui;
}

void EditUser::passParams(Vector<User>* users, User* user, UserManager* parentWindow)
{
    userVector = users;
    currentUser = user;
    userManager = parentWindow;

    ui->usernameLabel->setText(currentUser->mUsername);
    ui->input_password1->setText(currentUser->mPassword);
    ui->input_password2->setText(currentUser->mPassword);
}

void EditUser::on_saveUserButton_clicked()
{
    QString password1 = ui->input_password1->text();
    QString password2 = ui->input_password2->text();

    if(password1 != password2)
    {
        QMessageBox::information(this, "Action Denied", "Passwords do not match!", QMessageBox::Ok);
        return;
    }

    currentUser->mPassword = password1;
    close();
}

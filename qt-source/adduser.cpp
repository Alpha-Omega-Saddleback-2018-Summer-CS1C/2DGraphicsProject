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

#include "adduser.h"
#include "ui_adduser.h"

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

void AddUser::passParams(Vector<User>* users, User* user)
{
    userVector = users;
    currentUser = user;
}

void AddUser::on_createNewUserButton_clicked()
{
    QString newUser = ui->input_newUser->text();
    QString password1 = ui->input_password1->text();
    QString password2 = ui->input_password2->text();

    if(password1 == password2 /*&& newUser doesnt already exist*/ )
    {
        //create new user
    }
}

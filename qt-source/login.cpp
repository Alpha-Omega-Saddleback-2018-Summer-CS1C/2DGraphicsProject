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
    File: login.cpp

    Defines login window
 */

#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

#include <QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    QString userName = ui->input_username->text();
    QString password = ui->input_password->text();

    if(userName == "test" && password == "test")
    {
        QMessageBox::information(this, "Login", "Username and password is correct");
        hide();
        MainWindow mainWindow;
        this->hide();
    }
    else
    {
        QMessageBox::information(this, "Login", "Username and password is NOT correct");
    }
}

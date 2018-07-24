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
#include "contact.h"
//#include "ui_contact.h" // ///////////////////////
#include <QMessageBox>

contact* contactWindow = nullptr;
MainWindow* gMainWindow = nullptr;

Login::Login(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(this, SIGNAL(requestNewMainWindow()), this, SLOT(openMainWindow()));
    connect(this, SIGNAL(requestContactWindow()), this, SLOT(openContactWindow()));
}

Login::~Login()
{
    delete ui;
}

void Login::addShapes(Vector<Shape*>& shapes)
{
    shapeVector = shapes;
}

void Login::on_loginButton_clicked()
{
    QString userName = ui->input_username->text();
    QString password = ui->input_password->text();

    if(userName == "test" && password == "test")
    {
        emit requestNewMainWindow();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Incorrect username or password!");
    }
}

void Login::openMainWindow()
{
    gMainWindow = new MainWindow;
    gMainWindow->show();
    gMainWindow->addShapes(shapeVector);
    this->hide();
}

void Login::on_Contact_clicked()
{
    emit requestContactWindow();
}

void Login::openContactWindow()
{
    contactWindow = new contact(this);  // 'this' specifies object to return to (login) from contact window
    contactWindow->show();
    this->hide();
}

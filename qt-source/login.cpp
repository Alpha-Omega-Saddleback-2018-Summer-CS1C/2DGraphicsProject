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

#include <QBitmap>
#include <QMessageBox>
#include <QPixmap>

#include "login.h"
#include "ui_login.h"

Login::Login(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //custom image
    //QLabel topLevelLabel;
    QPixmap pixmap("alphaOmega.png");
    ui->alphaOmegaPic->setPixmap(pixmap);
    ui->alphaOmegaPic->setMask(pixmap.mask());
    ui->alphaOmegaPic->setScaledContents(true);
    ui->alphaOmegaPic->show();
    //ui->verticalLayout->addItem(pixmap);
}

Login::~Login()
{
    delete ui;
}

void Login::passParams(Vector<Shape*>* shapes, Vector<User>* users)
{
    shapeVector = shapes;
    userVector = users;
}

void Login::on_loginButton_clicked()
{
    QString username = ui->input_username->text();
    QString password = ui->input_password->text();
    bool loginSuccess = false;

    for(Vector<User>::iterator it = userVector->begin(); it != userVector->end(); ++it)
    {
        if(username == it->mUsername && password == it->mPassword)
        {
            loginSuccess = true;
            currentUser = *it;
            break;
        }
    }

    if(loginSuccess)
    {
        openMainWindow();
    }
    else
    {
        QMessageBox::warning(this, "Invalid Sign In", "Incorrect username or password!");
    }
}

void Login::openMainWindow()
{
    mainWindow = new MainWindow;
    mainWindow->show();
    mainWindow->passParams(this, shapeVector, userVector, &currentUser);
    this->hide();
}

void Login::closeMainWindow()
{
    mainWindow->close();
    delete mainWindow;

    ui->input_username->clear();
    ui->input_password->clear();
    this->show();
}

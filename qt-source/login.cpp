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

    Defines UI features
 */

#include "login.h"
#include "ui_login.h"
#include "secdialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString userName = ui->lineEdit_userName->text();
    QString password = ui->lineEdit_password->text();

    if(userName == "test" && password == "test")
    {
        QMessageBox::information(this, "Login", "Username and password is correct");
        hide();
        secDialog secondWindow;
        secondWindow.setModal(true);
        secondWindow.exec();
    }
    else
        QMessageBox::information(this, "Login", "Username and password is NOT correct");
}

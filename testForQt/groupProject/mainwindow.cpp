#include "mainwindow.h"
#include "ui_mainwindow.h"
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
        //secDialog = new SecDialog(this);
        //secDialog->show();
    }
    else
        QMessageBox::information(this, "Login", "Username and password is NOT correct");
}

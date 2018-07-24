#include "contact.h"
#include "ui_contact.h"
#include "ui_login.h"
#include "login.h"


contact::contact(QMainWindow* previous, QWidget *parent) : QMainWindow(parent),

    ui(new Ui::contact), m_login{previous}
{
    ui->setupUi(this);
    QPixmap pic("alphaOmega.png");
    int w = ui->logo->width();
    int h = ui->logo->height();
    ui->logo->setPixmap(pic.scaled(w,h,Qt::KeepAspectRatio));
}


void contact::on_pushButton_clicked()  // email link
{
    QString link("mailto:support@alphaomega.com");
    QDesktopServices::openUrl(QUrl(link));
}

void contact::on_pushButton_2_clicked()  // back to login
{
    this->hide();
    m_login->show();
}

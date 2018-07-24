#include "contact.h"
#include "ui_contact.h"
#include "ui_login.h"
#include "login.h"


contact::contact(QMainWindow* previous, QWidget *parent) : QMainWindow(parent),

    ui(new Ui::contact), m_login{previous}
{
    ui->setupUi(this);
    QPixmap pic(":/graphics/logo.jpg");
    int w = ui->logo->width();
    int h = ui->logo->height();
    ui->logo->setPixmap(pic.scaled(w,h,Qt::KeepAspectRatio));
    connect(this, SIGNAL(requestLoginWindow()), this, SLOT(openLoginWindow()));
    connect(this, SIGNAL(requestMailTo()), this, SLOT(mailTo()));
}


void contact::on_pushButton_clicked()  // email link
{
    emit requestMailTo();
}

void contact::on_pushButton_2_clicked()  // back to login
{
    emit requestLoginWindow();
}

void contact::openLoginWindow()
{
    this->hide();
    m_login->show();
}

void contact::mailTo()
{
    QString link("mailto:support@alphaomega.com");
    QDesktopServices::openUrl(QUrl(link));

}

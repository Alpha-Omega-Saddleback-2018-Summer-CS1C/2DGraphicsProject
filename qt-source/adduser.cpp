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

#include "usermanager.h"
#include "ui_usermanager.h"

UserManager::UserManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);
}

UserManager::~UserManager()
{
    delete ui;
}

void UserManager::on_addUserButton_clicked()
{
   // probably wrong emit requestNewAddUser();
}

void UserManager::on_editUserButton_clicked()
{
    //go to edit user
}

void UserManager::on_deleteUserManager_clicked()
{
    //go to delete user
}

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QDialog>
#include "adduser.h"

namespace Ui {
class UserManager;
}

class UserManager : public QDialog
{
    Q_OBJECT

public:
    explicit UserManager(QWidget *parent = 0);
    ~UserManager();

private slots:
    void on_addUserButton_clicked();

    void on_editUserButton_clicked();

    void on_deleteUserManager_clicked();

private:
    Ui::UserManager *ui;
    AddUser *adduser;

};

#endif // USERMANAGER_H

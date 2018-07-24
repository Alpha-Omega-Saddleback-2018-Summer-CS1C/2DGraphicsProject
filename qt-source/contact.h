#ifndef CONTACT_H
#define CONTACT_H
#include <QMainWindow>
#include "login.h"
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {class contact;}

class contact : public QMainWindow
{
    Q_OBJECT
public:
    explicit contact(QMainWindow *previous, QWidget *parent = nullptr);
    ~contact(){};
signals:
    void requestMailTo();
    void requestLoginWindow();
public slots:

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::contact *ui;
    QMainWindow* m_login;
};

#endif // CONTACT_H

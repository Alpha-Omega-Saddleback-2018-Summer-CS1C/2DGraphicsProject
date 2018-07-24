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
    File: login.h

    Defines login window
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "mainwindow.h"
#include "custom_vector.h"
#include "shape.h"
#include "userparser.h"

using shape::Shape;

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void passParams(Vector<Shape*>* shapes, Vector<User>* users);

private slots:
    void on_loginButton_clicked();
    void openMainWindow();
    void closeMainWindow();

private:
    Ui::Login* ui;
    MainWindow* mainWindow;

    Vector<Shape*>* shapeVector; // Does not require deletion
    Vector<User>* userVector; // Does not require deletion
    User currentUser;
};

#endif // LOGIN_H

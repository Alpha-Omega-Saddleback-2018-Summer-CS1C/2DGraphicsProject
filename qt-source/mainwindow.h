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
    File: mainwindow.h

    Defines a main window
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "custom_vector.h"
#include "renderarea.h"
#include "shape.h"
#include "usermanager.h"
#include "userparser.h"

/* Forward decleration */
class QPushButton;
class QComboBox;
class QLabel;
class QGridLayout;
class Login;

class MainWindow : public QWidget
{
    Q_OBJECT

    static const int shapeHeaderLabelCount = 4;
    static const int shapeDimensionLabelCount = 10;
    static const int shapeDescriptionLabelCount = 14;

public:
    MainWindow();
    ~MainWindow();

    void passParams(Login* login, Vector<Shape*>& shapes, Vector<User>& users, User& user);

private slots:
    void updateShapeInfo();
    void createUserManager();

private:
    RenderArea*     renderArea;
    QGridLayout*    mainLayout;
    QGridLayout*    leftSideLayout;
    QGridLayout*    rightSideLayout;

    /* Left side */
    QLabel*         selectedShapeLabel;
    QComboBox*      shapeComboBox;
    QPushButton*    addShapeButton;
    QPushButton*    editShapeButton;
    QPushButton*    deleteShapeButton;
    QPushButton*    userManagerButton;
    QPushButton*    logoutButton;

    /* Right-side */
    QLabel*         shapeHeaderLabels[shapeHeaderLabelCount];
    QLabel*         shapeDimensionLabels[shapeDimensionLabelCount];
    QLabel*         shapeDescriptionLabels[shapeDescriptionLabelCount];
    bool            isText;

    Login* loginWindow;
    UserManager* userManager;
    Vector<Shape*> shapeVector;
    Vector<User> userVector;
    User currentUser;
};

#endif // MAINWINDOW_H

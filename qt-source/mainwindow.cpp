#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_canvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    canvasArea(new Canvas)
{
    ui->setupUi(this);
    canvasArea->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete canvasArea;
}

/*
    rendering area
    add user  //verify password //third dialog box
    add shapes
    edit shape
    move
    update
*/

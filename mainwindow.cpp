#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginui.h"

//Template of QMainWindow Based Classes

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Current=this;
    ui->setupUi(this);
}

MainWindow * MainWindow::Current = nullptr;
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setId(QString Id)
{
    QMainWindow::show();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    LoginUi::GetCurrent()->ExitFromSubDialog();
}

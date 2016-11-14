#include "studentui.h"
#include "ui_studentui.h"
#include "loginui.h"

StudentUi::StudentUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentUi)
{
    Current=this;
    ui->setupUi(this);
}

StudentUi * StudentUi::Current = nullptr;
StudentUi::~StudentUi()
{
    delete ui;
}

void StudentUi::setId(QString Id)
{
    QMainWindow::show();
    ui->IdShow->setText(Id);
    setWindowTitle(QString::fromLocal8Bit("»¶Ó­,")+Id);
}

void StudentUi::closeEvent(QCloseEvent * event)
{
    LoginUi::GetCurrent()->ExitFromSubDialog();
}

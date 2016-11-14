#include "teacherui.h"
#include "ui_teacherui.h"
#include "loginui.h"

TeacherUi::TeacherUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherUi)
{
    Current=this;
    ui->setupUi(this);
}

TeacherUi * TeacherUi::Current = nullptr;
TeacherUi::~TeacherUi()
{
    delete ui;
}

void TeacherUi::setId(QString Id)
{
    QMainWindow::show();
    ui->IdShow->setText(Id);
    setWindowTitle(QString::fromLocal8Bit("»¶Ó­,")+Id);
}

void TeacherUi::closeEvent(QCloseEvent * event)
{
    LoginUi::GetCurrent()->ExitFromSubDialog();
}

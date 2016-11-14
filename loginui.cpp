#include "loginui.h"
#include "ui_loginui.h"

LoginUi::LoginUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);
    setFixedSize(284,100);
    QStringList Temp;
    Temp<<QString::fromLocal8Bit("学生")
       <<QString::fromLocal8Bit("教师")
      <<QString::fromLocal8Bit("管理员");
    ui->login_type->addItems(Temp);
}

LoginUi::~LoginUi()
{
    delete ui;
}

#include "loginui.h"
#include "ui_loginui.h"

LoginUi::LoginUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);
    setFixedSize(284,100);
    QStringList Temp;
    Temp<<QString::fromLocal8Bit("ѧ��")
       <<QString::fromLocal8Bit("��ʦ")
      <<QString::fromLocal8Bit("����Ա");
    ui->login_type->addItems(Temp);
}

LoginUi::~LoginUi()
{
    delete ui;
}

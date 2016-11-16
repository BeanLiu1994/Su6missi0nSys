#include "loginui.h"
#include "ui_loginui.h"
#include "adminui.h"
#include "studentui.h"
#include "teacherui.h"


#include "dao/StudentDao.h"
#include "dao/TeacherDao.h"

LoginUi * LoginUi::Current = nullptr;
LoginUi::LoginUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginUi)
{
    Current=this;
    ui->setupUi(this);
    //setFixedSize(284,100);
    QStringList Temp;
    Temp<<QString::fromLocal8Bit("学生")
       <<QString::fromLocal8Bit("教师")
      <<QString::fromLocal8Bit("管理员");
    ui->login_type->addItems(Temp);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->SuccessOrNot->setText(QString::fromLocal8Bit("请选择登陆类型进行登录"));
    connect(ui->login_button,SIGNAL(released()),this,SLOT(LoginProcess()));
}

LoginUi::~LoginUi()
{
    delete ui;
}

void LoginUi::ExitFromSubDialog()
{
    this->show();
    ui->SuccessOrNot->setText(QString::fromLocal8Bit("请选择登陆类型进行登录"));
}

void LoginUi::LoginProcess()
{
    Id=ui->user->text().toLocal8Bit().toStdString();
    Password=ui->password->text().toLocal8Bit().toStdString();
    bool LoginResult=false;
    switch(ui->login_type->currentIndex())
    {
    case 0:LoginResult=StudentLoginProcess();break;
    case 1:LoginResult=TeacherLoginProcess();break;
    case 2:LoginResult=AdminLoginProcess();break;
    default:break;
    }
    if(!LoginResult)
    {
        ui->SuccessOrNot->setText(QString::fromLocal8Bit("登录失败，请检查用户名或密码"));
    }
    else
    {
        ui->password->setText(QString(""));
        this->hide();
    }
    Password = "";
}

bool LoginUi::AdminLoginProcess()
{
    bool result = (Id=="app"&&Password=="visg");
    if(result)
    {
        AdminUI::GetCurrent()->show();
    }
    return result;
}
bool LoginUi::TeacherLoginProcess()
{
    bool result = TeacherDao::find(Id,Password);
    if(result)
    {
        TeacherUi::GetCurrent()->setId(QString::fromLocal8Bit(Id.c_str()));
    }
    return result;
}
bool LoginUi::StudentLoginProcess()
{
    bool result = StudentDao::find(Id,Password);
    if(result)
    {
        StudentUi::GetCurrent()->setId(QString::fromLocal8Bit(Id.c_str()));
    }
    return result;
}

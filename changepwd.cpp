#include "changepwd.h"
#include "ui_changepwd.h"
#include <QMessageBox>
#include "studentui.h"
#include "teacherui.h"
#include "loginui.h"
changepwd::changepwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changepwd)
{
    ui->setupUi(this);
    if(parent!=nullptr)
        connect(parent,SIGNAL(WindowClosed()),this,SLOT(close()));
    ui->lineEditOld->setEchoMode(QLineEdit::Password);
    ui->lineEditNew->setEchoMode(QLineEdit::Password);
    ui->lineEditRpt->setEchoMode(QLineEdit::Password);
    connect(ui->pushButtonOK,SIGNAL(released()),this,SLOT(BtnOK()));
}

changepwd::~changepwd()
{
    delete ui;
}
void changepwd::init(QString Id,UserType type)
{
    show();
    id=Id;
    ui->Info->setText(QString::fromLocal8Bit("正在修改")+id+QString::fromLocal8Bit("的密码"));
    tp=type;
}



void changepwd::closeEvent(QCloseEvent * event)
{
    LoginUi::GetCurrent()->ExitFromSubDialog();
    StudentUi::GetCurrent()->close();
}
void changepwd::BtnOK()
{
    //judge the old pwd
    QMessageBox msg;

    string pwd;
    Student s;
    Teacher t;
    switch(tp)
    {
    case tStudent:
        s=StudentDao::findStudentBySid(id.toLocal8Bit().toStdString());
        pwd = s.getPassword();break;
    case tTeacher:
        t=TeacherDao::findTeacherByTid(id.toLocal8Bit().toStdString());
        pwd = t.getPassword();break;
    default:break;
    }


    QString QOldPwd = ui->lineEditOld->text();
    string oldPwd = string((const char*)QOldPwd.toLocal8Bit());
    if(pwd != oldPwd)
    {
        msg.setText("Old Pwd is wrong");
        msg.exec();
    }
    else
    {
        QString newPwd = ui->lineEditNew->text();
        QString rptPwd = ui->lineEditRpt->text();
        if(newPwd != rptPwd)
        {
            msg.setText("2 new pwd is different!");
            msg.exec();
        }
        else
        {
            string updatePwd = string((const char*)newPwd.toLocal8Bit());
            switch(tp)
            {
            case tStudent:
                StudentDao::updatePassword(s,updatePwd);
                break;
            case tTeacher:
                TeacherDao::updatePassword(t,updatePwd);
                pwd = t.getPassword();break;
            default:break;
            }

            msg.setText("Pwd changed successfully!");
            msg.exec();
            this->close();
        }
    }

}

void changepwd::BtnCancel()
{
    this->close();
}

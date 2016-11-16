#include "studentui.h"
#include "ui_studentui.h"
#include "loginui.h"
#include <QMessageBox>
#include <QDate>
#include "changepwd.h"

StudentUi::StudentUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentUi)
{
    Current=this;
    ui->setupUi(this);
    ui->score->setText(QString(" "));
    connect(ui->comboBoxSub, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onSelSub(const QString&)));
    connect(ui->comboBoxBat, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(onSelBat(const QString&)));
    connect(ui->pushButtonSelect,SIGNAL(released()),this,SLOT(BtnSelect()));
    connect(ui->pushButtonSubmit,SIGNAL(released()),this,SLOT(BtnSubmit()));
    connect(ui->pushButtonCpw,SIGNAL(released()),this,SLOT(BtnChangePwd()));
}

StudentUi * StudentUi::Current = nullptr;
StudentUi::~StudentUi()
{
    delete ui;
}

void StudentUi::setId(QString Id)
{
    show();
    this->id=Id;
    ui->IdShow->setText(Id);
    setWindowTitle(QString::fromLocal8Bit("»¶Ó­,")+Id);

    v = CourseStuDao::findCourseBySid(Id.toLocal8Bit().toStdString());   // add subjects
    for(Course c:v)
    {
        ui->comboBoxSub->addItem(QWidget::tr(c.toString().c_str()));
    }
}

void StudentUi::closeEvent(QCloseEvent * event)
{
    emit WindowClosed();
    LoginUi::GetCurrent()->ExitFromSubDialog();
    id=QString("");
    v.clear();
    w=Work();
    currentwtime="";
    ui->comboBoxSub->clear();
    ui->comboBoxBat->clear();
    ui->textEditAnswer->setText(QString(" "));
    ui->textEditTask->setText(QString(" "));
    ui->score->setText(QString(" "));
}

void StudentUi::onSelSub(const QString& currentText)
{
      if(ui->comboBoxSub->currentIndex()==-1)return;
      int idx = ui->comboBoxSub->currentIndex();
      string cid = v[idx].getId();

      ui->comboBoxBat->clear();
      vector<string> times=WorkDao::findTimesByCid(cid);
      for(string& s:times)
      {
            ui->comboBoxBat->addItem(tr(s.c_str()));
      }
}

void StudentUi::onSelBat(const QString& text)
{
    if(ui->comboBoxBat->currentIndex()==-1)return;
    QString wtime = ui->comboBoxBat->currentText();
    currentwtime = string((const char*)wtime.toLocal8Bit());

}


void StudentUi::BtnChangePwd()
{
    changepwd win(this);
    win.init(id,tStudent);
    win.show();
    win.exec();
}





void StudentUi::BtnSelect()
{
    QMessageBox msg;
    int idx = ui->comboBoxSub->currentIndex();
    string cid = v[idx].getId();

    w= WorkDao::findWorkByCid(cid,currentwtime);

    string time1 = QDate::currentDate().toString("yyyy-MM-dd").toLocal8Bit().toStdString();
    string time2 = w.getDate();
    if(time1>time2)
    {
        msg.setText( QString(QString::fromLocal8Bit("Job submission has expired!")));
        msg.exec();
    }
    else
    {
        QString task = QString(QString::fromLocal8Bit(w.getContent().c_str()));  // show the task
        ui->textEditTask->setText(task);

        Upload u1=UploadDao::findUpload(w.getId(),id.toLocal8Bit().toStdString());
        if((u1.getWid()==w.getId())&&(u1.getSid()==id.toLocal8Bit().toStdString()))       //whether it has been submitted
        {
            QString answer = QString(QString::fromLocal8Bit(u1.getContent().c_str()));  // show the task
            ui->textEditAnswer->setText(answer);

            if(u1.getScore()==-1)
                ui->score->setText(QString::fromLocal8Bit("Î´´ò·Ö"));
            else
                ui->score->setText(QString::number(u1.getScore()));

            msg.setText( QString(QString::fromLocal8Bit("You have submitted! You can update it")));
            msg.exec();

        }
        else
        {
            ui->textEditAnswer->setText(QString(" "));
            msg.setText( QString(QString::fromLocal8Bit("Please answer it")));
            msg.exec();
        }


    }

}

void StudentUi::BtnSubmit()
{
    QMessageBox msg;

    Upload u1=UploadDao::findUpload(w.getId(),id.toLocal8Bit().toStdString());
    if((u1.getWid()==w.getId())&&(u1.getSid()==id.toLocal8Bit().toStdString()))       //whether it has been submitted
    {
        //QString answer = QString(QString::fromLocal8Bit(u1.getContent().c_str()));  // show the task
        //ui.textEditAnswer->setText(answer);

        //msg.setText( QString(QString::fromLocal8Bit("You have submitted! Press Update to update it")));
        //msg.exec();
        BtnUpdate();
    }
    else
    {
        QString getAnswer = ui->textEditAnswer->toPlainText();

        msg.setText( getAnswer);
        msg.exec();
        string answer =  string((const char*)getAnswer.toLocal8Bit());
        Upload u(id.toLocal8Bit().toStdString(),w.getId(),answer);
        bool flag1=UploadDao::insertRecord(u);
        if(flag1)
        {
            QMessageBox msg;
            msg.setText( QString(QString::fromLocal8Bit("submit successfully!")));
            msg.exec();
        }
    }

}

void StudentUi::BtnUpdate()
{
    QString getAnswer = ui->textEditAnswer->toPlainText();
    string answer =  string((const char*)getAnswer.toLocal8Bit());

    //QString QUser = ui.lineEditUser->text();                  //just for test
    //string id = string((const char*)QUser.toLocal8Bit());

    Upload u1=UploadDao::findUpload(w.getId(),id.toLocal8Bit().toStdString());
    bool flag1=UploadDao::updateAns(u1,answer);

    if(flag1)
    {
        QMessageBox msg;
        msg.setText( QString(QString::fromLocal8Bit("update successfully!")));
        msg.exec();
    }
}

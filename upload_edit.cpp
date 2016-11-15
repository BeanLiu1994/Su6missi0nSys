#include "upload_edit.h"
#include "ui_upload_edit.h"

upload_edit::upload_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::upload_edit)
{
    ui->setupUi(this);
    if(parent!=nullptr)
        connect(parent,SIGNAL(WindowClosed()),this,SLOT(close()));
    connect(ui->add_button,SIGNAL(released()),this,SLOT(UploadAdd()));
    connect(ui->delete_button,SIGNAL(released()),this,SLOT(UploadDelete()));
}



upload_edit::~upload_edit()
{
    delete ui;
}
void upload_edit::init()
{
    ui->sid->setReadOnly(false);
    ui->uid->setReadOnly(false);
}
void upload_edit::init(string& uid)
{
    Upload u = UploadDao::findUploadByUid(uid);
    cout<<uid<<endl;
    init(u);
}
void upload_edit::init(string& wid,string& sid)
{
    Upload u = UploadDao::findUpload(wid,sid);
    init(u);
}

void upload_edit::init(Upload& u)
{
    this->uid=u.getId();
    setWindowTitle(QString::fromLocal8Bit(u.getId().c_str()));
    ui->uid->setText(QString::fromLocal8Bit(u.getId().c_str()));
    ui->sid->setText(QString::fromLocal8Bit(u.getSid().c_str()));
    ui->wid->setText(QString::fromLocal8Bit(u.getWid().c_str()));
    ui->uscore->setText(QString::number(u.getScore()));
    ui->content->setPlainText(QString::fromLocal8Bit(u.getContent().c_str()));
}

void upload_edit::UploadAdd()
{
    Upload u;
    uid=ui->uid->text().toLocal8Bit().toStdString();
    u.setContent(ui->content->toPlainText().toLocal8Bit().toStdString());

    u.setId(uid);
    u.setScore(ui->uscore->text().toInt());
    u.setSid(ui->sid->text().toLocal8Bit().toStdString());
    u.setWid(ui->wid->text().toLocal8Bit().toStdString());

    if(UploadDao::findUpload(u.getWid(),u.getSid()).getId().empty())
        UploadDao::insertRecord(u);
    else
        UploadDao::updateAns(u,u.getContent());
    emit uploadChanged();
}
void upload_edit::UploadDelete()
{
     UploadDao::deleteRecord(uid);
     emit uploadChanged();
}

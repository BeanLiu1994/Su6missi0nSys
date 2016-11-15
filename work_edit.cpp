#include "work_edit.h"
#include "ui_work_edit.h"

work_edit::work_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::work_edit)
{
    ui->setupUi(this);
    if(parent!=nullptr)
        connect(parent,SIGNAL(WindowClosed()),this,SLOT(close()));

    connect(ui->work_add_button,SIGNAL(released()),this,SLOT(WorkAdd()));
    connect(ui->work_delete_button,SIGNAL(released()),this,SLOT(WorkDelete()));
}
void work_edit::init()
{
    ui->wid->setReadOnly(false);
    ui->deadline->setDate(QDate::currentDate());
}
void work_edit::init(string& _wid)
{
    wid=_wid;
    Work w_in = WorkDao::findWorkByWid(wid);
    init(w_in);
}
void work_edit::init(string& cid,string& time)
{
    Work w_in = WorkDao::findWorkByCid(cid,time);
    wid=w_in.getId();
    init(w_in);
}
void work_edit::init(Work w_in)
{
    setWindowTitle(QString::fromLocal8Bit(w_in.getId().c_str()));
    ui->wid->setText(QString::fromLocal8Bit(w_in.getId().c_str()));
    ui->wcontent->setPlainText(QString::fromLocal8Bit(w_in.getContent().c_str()));
    ui->wanswer->setPlainText(QString::fromLocal8Bit(w_in.getAnswer().c_str()));
    ui->cid->setText(QString::fromLocal8Bit(w_in.getCourseId().c_str()));
    ui->wtime->setText(QString::fromLocal8Bit(w_in.getTime().c_str()));
    ui->deadline->setDate(QDate::fromString(QString::fromLocal8Bit(w_in.getDate().c_str()),tr("yyyy/MM/dd")));
}

work_edit::~work_edit()
{
    delete ui;
}

void work_edit::WorkAdd()
{
    Work w;
    wid=ui->wid->text().toLocal8Bit().toStdString();
    w.setContent(ui->wcontent->toPlainText().toLocal8Bit().toStdString());
    w.setAnswer(ui->wanswer->toPlainText().toLocal8Bit().toStdString());

    w.setCourseId(ui->cid->text().toLocal8Bit().toStdString());
    w.setTime(ui->wtime->text().toLocal8Bit().toStdString());

    w.setDate(ui->deadline->dateTime().toString(tr("yyyy-MM-dd")).toLocal8Bit().toStdString());
    w.setId(wid);
    if(WorkDao::findWorkByWid(wid).getId().empty())
        WorkDao::insertRecord(w);
    else
        WorkDao::updateRecord(w);
    emit workChanged();
}
void work_edit::WorkDelete()
{
     WorkDao::deleteRecord(wid);
     emit workChanged();
}

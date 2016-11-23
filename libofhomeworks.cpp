#include "libofhomeworks.h"
#include "ui_libofhomeworks.h"
#include <QMessageBox>

string AddYYYYMM_Back(string & str)
{
    return GetStrBeforeDash(str)+"#"+QDate::currentDate().toString("yyyy-MM").toLocal8Bit().toStdString();
}
string GetStrBeforeDash(string & str)
{
    return str.substr(0,str.find_first_of('#'));
}


LibOfHomeworks::LibOfHomeworks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibOfHomeworks)
{
    ui->setupUi(this);
    setWindowTitle(tr("Adding works from lib"));
    if(parent!=nullptr)
        connect(parent,SIGNAL(WindowClosed()),this,SLOT(close()));
    SetTableWidgetStyle(ui->work_table);
    SetTableWidgetStyle(ui->selected_table);
    radiobuttons.addButton(ui->setNewDate,0);
    radiobuttons.addButton(ui->setRelativeDate,1);

    connect(ui->course_select, SIGNAL(currentIndexChanged(QString)), this, SLOT(CourseSelected()));
    connect(ui->SelectAll,SIGNAL(stateChanged(int)),this,SLOT(onHeaderClicked(int)));
    connect(ui->addSelected,SIGNAL(released()),this,SLOT(AddSelected()));
    connect(ui->applyDatesetting,SIGNAL(released()),this,SLOT(UpdateDeadtime()));
    connect(ui->SelectAll_2,SIGNAL(stateChanged(int)),this,SLOT(onHeaderClicked_2(int)));
    connect(ui->SaveWorks,SIGNAL(released()),this,SLOT(AddWorks()));
    connect(ui->Exit,SIGNAL(released()),this,SLOT(close()));

    getCourses();
    SelectedWorksShow();

    ui->dateset->setDate(QDate::currentDate());
}

LibOfHomeworks::~LibOfHomeworks()
{
    delete ui;
}

void LibOfHomeworks::CourseSelected()
{
    int ind=ui->course_select->currentIndex();
    if(ind==0)
        getWorks();
    else
        getWorks(courses[ind-1].getId());
}

void LibOfHomeworks::getCourses()
{
    courses=CourseDao::findAllCourses();
    QVector<QString> content;
    for(auto& m:courses)
    {
        content.push_back(QString::fromLocal8Bit(m.toString().c_str()));
    }
    ui->course_dest->clear();
    ui->course_dest->addItems(QStringList::fromVector(content));
    content.push_front(tr("All"));
    ui->course_select->clear();
    ui->course_select->addItems(QStringList::fromVector(content));
    ui->course_select->setCurrentIndex(0);
}

void LibOfHomeworks::getWorks(string& cid)
{
    if(cid.empty())
    {
        works_on_show=WorkDao::findAllWorks();
    }
    else
    {
        works_on_show=WorkDao::findWorkByCidOnly(cid);
    }
    QStringList header;
    header<<tr("")<<tr("workId")<<tr("CourseId")<<tr("time")<<tr("Content")<<tr("Deadtime");
    ui->work_table->setColumnCount(header.size());
    ui->work_table->setHorizontalHeaderLabels(header);
    ui->work_table->setRowCount((int)works_on_show.size());
    ui->work_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->work_table->setColumnWidth(0,20);
    for(int i=0;i<works_on_show.size();++i)
    {
        Work & m = works_on_show[i];
        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setCheckState(ui->SelectAll->checkState());
        ui->work_table->setItem(i,0,temp);
        ui->work_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
        ui->work_table->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(m.getCourseId().c_str())));
        ui->work_table->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit(m.getTime().c_str())));
        ui->work_table->setItem(i,4,new QTableWidgetItem(QString::fromLocal8Bit(m.getContent().c_str())));
        ui->work_table->setItem(i,5,new QTableWidgetItem(QString::fromLocal8Bit(m.getDate().c_str())));
    }
}
void LibOfHomeworks::onHeaderClicked(int state)
{
    for(int i=0;i<works_on_show.size();++i)
        ui->work_table->item(i,0)->setCheckState(Qt::CheckState(state));
}

void LibOfHomeworks::AddSelected()
{
    for(int i=0;i<works_on_show.size();++i)
        if(ui->work_table->item(i,0)->checkState()!=Qt::Unchecked)
        {
            Work temp = works_on_show[i];
            temp.setId(AddYYYYMM_Back(temp.getId()));
            if(CheckWid(temp.getId(),works_to_be_added))
                works_to_be_added.push_back(temp);
        }
    SelectedWorksShow();
}
void LibOfHomeworks::SelectedWorksShow()
{
    QStringList header;
    header<<tr("")<<tr("workId")<<tr("CourseId")<<tr("time")<<tr("Content")<<tr("Deadtime");
    ui->selected_table->setColumnCount(header.size());
    ui->selected_table->setHorizontalHeaderLabels(header);
    ui->selected_table->setRowCount((int)works_to_be_added.size());
    ui->selected_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->selected_table->setColumnWidth(0,20);
    for(int i=0;i<works_to_be_added.size();++i)
    {
        Work & m = works_to_be_added[i];
        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setCheckState(ui->SelectAll_2->checkState());
        ui->selected_table->setItem(i,0,temp);
        ui->selected_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
        ui->selected_table->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(m.getCourseId().c_str())));
        ui->selected_table->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit(m.getTime().c_str())));
        ui->selected_table->setItem(i,4,new QTableWidgetItem(QString::fromLocal8Bit(m.getContent().c_str())));
        ui->selected_table->setItem(i,5,new QTableWidgetItem(QString::fromLocal8Bit(m.getDate().c_str())));
    }
}

bool LibOfHomeworks::CheckWid(string& wid, vector<Work>& vw)
{
    for(int i=0;i<vw.size();++i)
    {
        if(vw[i].getId()==wid)
            return false;
    }
    return true;
}

void LibOfHomeworks::UpdateDeadtime()
{
    for(int i=0;i<works_to_be_added.size();++i)
        if(ui->selected_table->item(i,0)->checkState()!=Qt::Unchecked)
        {
            Work temp = works_to_be_added[i];
            QDate tempDate = QDate::fromString(QString::fromLocal8Bit(temp.getDate().c_str()),"yyyy/MM/dd");
            switch(radiobuttons.checkedId())
            {
            case 0:
                tempDate = ui->dateset->date();
                break;
            case 1:
                tempDate=tempDate.addDays(ui->datedelta->value());
                break;
            }

            temp.setDate(tempDate.toString(tr("yyyy/MM/dd")).toLocal8Bit().toStdString());

            works_to_be_added.erase(works_to_be_added.begin()+i);
            works_to_be_added.insert(works_to_be_added.begin()+i,temp);
        }
    SelectedWorksShow();
}

void LibOfHomeworks::onHeaderClicked_2(int state)
{
    for(int i=0;i<works_to_be_added.size();++i)
        ui->selected_table->item(i,0)->setCheckState(Qt::CheckState(state));
}

void LibOfHomeworks::AddWorks()
{
    sort(works_to_be_added.begin(),works_to_be_added.end(),
         [](Work&m1, Work&m2)
    {
        return
                QDate::fromString(QString::fromLocal8Bit(m1.getDate().c_str()),"yyyy/MM/dd")
                <
                QDate::fromString(QString::fromLocal8Bit(m2.getDate().c_str()),"yyyy/MM/dd");
    });
    decltype(works_to_be_added) works_error;
    for(int i=0;i<works_to_be_added.size();++i)
    {
        Work temp=works_to_be_added[i];
        string cid=courses[ui->course_dest->currentIndex()].getId();
        temp.setCourseId(cid);
        vector<string> vcwt= WorkDao::findTimesByCid(cid);
        int maxTime=0;
        for(auto& m:vcwt)
        {
            int tempTime=QString::fromLocal8Bit(m.c_str()).toInt();
            if(tempTime>maxTime)
            {
                maxTime=tempTime;
            }
        }
        cout<<maxTime<<endl;
        temp.setTime(QString::number(maxTime+1).toLocal8Bit().toStdString());

        QMessageBox msg;
        msg.setText(tr("insert failed. maybe same id exists."));

        if(!WorkDao::insertRecord(temp))
        {
            works_error.push_back(temp);
            msg.exec();
        }
    }
    emit workChanged();
    works_to_be_added.clear();
    works_to_be_added=works_error;
    getWorks();
    SelectedWorksShow();
}

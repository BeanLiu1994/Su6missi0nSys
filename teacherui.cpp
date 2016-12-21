#include "teacherui.h"
#include "ui_teacherui.h"
#include "loginui.h"
#include <QMessageBox>

TeacherUi::TeacherUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherUi)
{
    Current=this;
    ui->setupUi(this);
    SetTableWidgetStyle(ui->student_table);
    SetTableWidgetStyle(ui->course_table);
    connect(ui->view_course,SIGNAL(released()),this,SLOT(CourseQueryTid()));
    connect(ui->course_table,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(ShowStudent()));
    connect(ui->course_table,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(FillHomework()));
    connect(ui->student_table,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(SelectStudent()));
    connect(ui->student_table,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(ShowAllScores()));
    connect(ui->change_passwd,SIGNAL(released()),this,SLOT(ChangePasswd()));
    connect(ui->select_homework,SIGNAL(currentIndexChanged(int)),this,SLOT(ShowStudent()));
    connect(ui->UseWorkLib,SIGNAL(released()),this,SLOT(WorkLibEnter()));
    connect(ui->AddWork,SIGNAL(released()),this,SLOT(AddWorkEnter()));
    connect(ui->doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(ScoreChanged(double)));
}

TeacherUi * TeacherUi::Current = nullptr;
TeacherUi::~TeacherUi()
{
    delete ui;
}

/*
bool TeacherUi::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->select_course_1) {
        if (event->type() == QEvent::MouseButtonPress)
            FillCourse();
        return false;
    }
    return true;
}
*/
void TeacherUi::ChangePasswd()
{
    changepwd win(this);
    win.init(Id,tTeacher);
    win.show();
    win.exec();
}

void TeacherUi::setId(QString Id)
{
    show();
    setWindowTitle(QString::fromLocal8Bit("»¶Ó­,")+Id);
    this->Id = Id;
    ui->Welcome->setText(tr("Welcome! ")+Id);
    CourseQueryTid();
}

void TeacherUi::closeEvent(QCloseEvent * event)
{
    ui->answer_text->clear();
    ui->course_table->setRowCount(0);
    ui->student_table->setRowCount(0);
    ui->stuanswer_text->clear();
    ui->select_homework->clear();
    LoginUi::GetCurrent()->ExitFromSubDialog();
    emit WindowClosed();
}

void TeacherUi::CourseQueryTid()
{
    courses=CourseDao::findCourseByTid(Id.toLocal8Bit().toStdString());
    //printf("length: %d\n",ts.size());
    QStringList header;
    header<<tr("Name")<<tr("Id")<<tr("TeacherId");
    ui->course_table->setColumnCount(header.size());
    ui->course_table->setHorizontalHeaderLabels(header);
    ui->course_table->setRowCount((int)courses.size());
    ui->course_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<courses.size();++i)
    {
        Course & m = courses[i];
        ui->course_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->course_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
        ui->course_table->setItem(i,2,new QTableWidgetItem(Id));
    }
}

void TeacherUi::ShowStudent(vector<Student> stu)
{
    if(stu.empty())
    {
        int idx = ui->course_table->currentRow();
        if(idx<0)return;
        stu = CourseStuDao::findStudentByCid(courses[idx]);
        students=stu;
    }
    QStringList header;
    header<<tr("Name")<<tr("Id")<<tr("Score");
    ui->student_table->setColumnCount(header.size());
    ui->student_table->setHorizontalHeaderLabels(header);
    ui->student_table->setRowCount((int)stu.size()+1);
    ui->student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    double mean=0;int StuNum=0;
    for(int i=0;i<stu.size();++i)
    {
        Student & m = stu[i];
        ui->student_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->student_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));

        int idx = ui->select_homework->currentIndex();
        if(idx<0)continue;
        Upload u = UploadDao::findUpload(works[idx].getId(),m.getId());
        QString score;
        if(u.getScore()==-1)
            score=tr("No Data");
        else
        {
            score = QString::number(u.getScore());
            ++StuNum;
            mean+=u.getScore();
        }
        ui->student_table->setItem(i,2,new QTableWidgetItem(score));
    }
    if(StuNum!=0)
        mean/=StuNum;
    ui->student_table->setItem(stu.size(),2,new QTableWidgetItem(tr("mean: ")+QString::number(mean)));
}

void TeacherUi::FillHomework() {
    int idx= ui->course_table->currentRow();
    if(idx<0)return;
    works = WorkDao::findWorkByCidOnly(courses[idx].getId());
    ui->select_homework->clear();
    for (int i = 0; i < works.size(); ++i) {
        ui->select_homework->addItem(QString::fromLocal8Bit(works[i].getId().c_str()));
    }
}

void TeacherUi::FillStudent() {
    int idx= ui->course_table->currentRow();
    if(idx<0)return;
    //students = CourseStuDao::findStudentByCid(courses[idx]);
    //ShowStudent(students);
}
void TeacherUi::SelectStudent() {
    int idx = ui->select_homework->currentIndex();
    if(idx<0||idx>=works.size())return;
    int idx_s = ui->student_table->currentRow();
    if(idx_s<0||idx_s>=students.size())return;
    ui->answer_text->setText(QString::fromLocal8Bit(works[idx].getAnswer().c_str()));
    Upload u = UploadDao::findUpload(works[idx].getId(),students[idx_s].getId());
    ui->doubleSpinBox->setEnabled(!u.getId().empty());
    if(!u.getId().empty())
        ui->stuanswer_text->setPlainText(QString::fromLocal8Bit(u.getContent().c_str()));
    else
        ui->stuanswer_text->setPlainText(tr("Not uploaded yet."));
    ui->doubleSpinBox->setValue(u.getScore());
}


void TeacherUi::WorkLibEnter()
{
    LibOfHomeworks worklib(this);
    worklib.SetTid(Id.toLocal8Bit().toStdString());
    connect(&worklib,SIGNAL(workChanged()),this,SLOT(FillHomework()));
    worklib.show();
    worklib.exec();
}

void TeacherUi::AddWorkEnter()
{
    int idx = ui->course_table->currentRow();
    if(idx<0)
    {
        QMessageBox msg;
        msg.setText(tr("Please select a course first."));
        msg.exec();
        return;
    }
    work_edit edt(this);
    connect(&edt,SIGNAL(workChanged()),this,SLOT(FillHomework()));
    edt.init(courses[idx]);
    edt.show();
    edt.exec();
}

void TeacherUi::ScoreChanged(double value)
{
    int idx = ui->select_homework->currentIndex();
    if(idx<0)return;
    int idx_s = ui->student_table->currentRow();
    if(idx_s<0)return;
    ui->answer_text->setText(QString::fromLocal8Bit(works[idx].getAnswer().c_str()));
    Upload u = UploadDao::findUpload(works[idx].getId(),students[idx_s].getId());
    if(!u.getId().empty())
        UploadDao::updateScore(u,value);
}

void TeacherUi::ShowAllScores()
{
    int idx_c = ui->course_table->currentRow();
    if(idx_c<0||idx_c>=courses.size())return;
    Course CurrentCourse=courses[idx_c];
    int idx_s = ui->student_table->currentRow();
    if(idx_s<0||idx_s>=students.size())return;
    Student CurrentStu=students[idx_s];
    QDialog CurrentStuWindow;
    CurrentStuWindow.setWindowTitle(tr("Scores of ")+QString::fromLocal8Bit(CurrentStu.getName().c_str()));
    QTableWidget* p=new QTableWidget();
    SetTableWidgetStyle(p);
    QStringList header;
    header<<tr("WorkId")<<tr("Score");
    p->setColumnCount(header.size());
    p->setHorizontalHeaderLabels(header);
    p->setRowCount((int)works.size());
    p->setEditTriggers(QAbstractItemView::NoEditTriggers);
    double mean=0;int WorkNum=0;
    for(int i=0;i<works.size();++i)
    {
        Work & m = works[i];
        p->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));

        Upload u = UploadDao::findUpload(m.getId(),CurrentStu.getId());
        QString score;
        if(u.getScore()==-1)
        {
            ++WorkNum;
            score=tr("No Data");
        }
        else
        {
            score = QString::number(u.getScore());
            ++WorkNum;
            mean+=u.getScore();
        }
        p->setItem(i,1,new QTableWidgetItem(score));
    }
    if(WorkNum!=0)
        mean/=WorkNum;
    QLabel * info=new QLabel();
    info->setText(tr("Course  --  Name : [")+QString::fromLocal8Bit(CurrentCourse.getName().c_str())+"] ID : ["+QString::fromLocal8Bit(CurrentCourse.getId().c_str())+tr("]\n")+
                  tr("Student --  Name : [")+QString::fromLocal8Bit(CurrentStu.getName().c_str())+"] ID : ["+QString::fromLocal8Bit(CurrentStu.getId().c_str())+tr("]\n")+
                  tr("Average Score    : ")+QString::number(mean)
                  );


    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(info);
    mainLayout->addWidget(p);
    CurrentStuWindow.setLayout(mainLayout);
    CurrentStuWindow.exec();
}

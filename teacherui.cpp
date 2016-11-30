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
    connect(ui->change_passwd,SIGNAL(released()),this,SLOT(ChangePasswd()));
    connect(ui->select_homework,SIGNAL(currentIndexChanged(int)),this,SLOT(FillHomework()));
    connect(ui->UseWorkLib,SIGNAL(released()),this,SLOT(WorkLibEnter()));
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
    header<<tr("Name")<<tr("Id");
    ui->student_table->setColumnCount(header.size());
    ui->student_table->setHorizontalHeaderLabels(header);
    ui->student_table->setRowCount((int)stu.size());
    ui->student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<stu.size();++i)
    {
        Student & m = stu[i];
        ui->student_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->student_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
        //ui->course_table->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(m.getTeacherId().c_str())));
    }
}

void TeacherUi::FillHomework() {
    int idx= ui->course_table->currentRow();
    if(idx<0)return;
    works = WorkDao::findWorkByCidOnly(courses[idx].getId());
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
    if(idx<0)return;
    int idx_s = ui->student_table->currentRow();
    if(idx_s<0)return;
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


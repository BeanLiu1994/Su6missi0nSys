#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->teacher_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->student_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->course_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->teacher_table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->student_table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->course_table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(ui->TeacherRefresh, SIGNAL (released()),this, SLOT (TeacherQuery()));
    connect(ui->StudentRefresh, SIGNAL (released()),this, SLOT (StudentQuery()));
    connect(ui->CourseRefresh, SIGNAL (released()),this, SLOT (CourseQuery()));
    TeacherQuery();
    StudentQuery();
    CourseQuery();
    connect(ui->teacher_add, SIGNAL (released()),this, SLOT (TeacherAdd()));
    connect(ui->student_add, SIGNAL (released()),this, SLOT (StudentAdd()));
    connect(ui->course_add, SIGNAL (released()),this, SLOT (CourseAdd()));

    connect(ui->teacher_table,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(TeacherDoubleClicked(QTableWidgetItem*)));
}
void MainWindow::TeacherDoubleClicked(QTableWidgetItem *item)
{
    string id = ui->teacher_table->item(item->row(),1)->text().toLocal8Bit().toStdString();
    TeacherDao::deleteRecord(id);
    TeacherQuery();
}
void MainWindow::StudentDoubleClicked(QTableWidgetItem *item)
{
    string id = ui->teacher_table->item(item->row(),1)->text().toLocal8Bit().toStdString();
    StudentDao::deleteRecord(id);
    TeacherQuery();
}
void MainWindow::CourseDoubleClicked(QTableWidgetItem *item)
{
    string id = ui->course_table->item(item->row(),1)->text().toLocal8Bit().toStdString();
    CourseDao::deleteRecord(id);
    TeacherQuery();
}
MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::AdminLogin()
{
    //bool Success=QueryForAdminInfo();
    bool Success=true;
    return Success;
}
void MainWindow::TeacherQuery()
{
    vector<Teacher> ts=TeacherDao::findAllTeachers();
    QStringList header;
    header<<tr("Name")<<tr("Id");
    ui->teacher_table->setHorizontalHeaderLabels(header);
    ui->teacher_table->setRowCount(ts.size());
    ui->teacher_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        Teacher & m = ts[i];
        ui->teacher_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->teacher_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
    }
}
void MainWindow::TeacherAdd()
{
    Teacher t;
    t.setId(ui->teacher_id_input->toPlainText().toLocal8Bit().toStdString());
    t.setName(ui->teacher_name_input->toPlainText().toLocal8Bit().toStdString());
    t.setPassword("123456");
    if(!TeacherDao::findTeacherByTid(t.getId()).getId().empty())
    {
        TeacherDao::updatePassword(t,t.getPassword());
        TeacherDao::updateName(t,t.getName());
    }
    else
        TeacherDao::insertRecord(t);
    TeacherQuery();
}

void MainWindow::StudentQuery()
{
    vector<Student> ts=StudentDao::findAllStudents();
    //printf("length: %d\n",ts.size());
    QStringList header;
    header<<tr("Name")<<tr("Id");
    ui->student_table->setHorizontalHeaderLabels(header);
    ui->student_table->setRowCount(ts.size());
    ui->student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        Student & m = ts[i];
        ui->student_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->student_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
    }
}
void MainWindow::StudentAdd()
{
    Student s;
    s.setId(ui->student_id_input->toPlainText().toLocal8Bit().toStdString());
    s.setName(ui->student_name_input->toPlainText().toLocal8Bit().toStdString());
    s.setPassword("123456");
    if(!StudentDao::findStudentBySid(s.getId()).getId().empty())
    {
        StudentDao::updatePassword(s,s.getPassword());
        StudentDao::updateName(s,s.getName());
    }
    else
        StudentDao::insertRecord(s);
    StudentQuery();
}

void MainWindow::CourseQuery()
{
    vector<Course> ts=CourseDao::findAllCourses();
    //printf("length: %d\n",ts.size());
    QStringList header;
    header<<tr("Name")<<tr("Id")<<tr("TeacherId");
    ui->course_table->setHorizontalHeaderLabels(header);
    ui->course_table->setRowCount(ts.size());
    ui->course_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        Course & m = ts[i];
        ui->course_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->course_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
        ui->course_table->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(m.getTeacherId().c_str())));
    }
}
void MainWindow::CourseAdd()
{
    Course s;
    s.setId(ui->course_id_input->toPlainText().toLocal8Bit().toStdString());
    s.setName(ui->course_name_input->toPlainText().toLocal8Bit().toStdString());
    s.setTeacherId(ui->course_tid_input->toPlainText().toStdString());
    if(!CourseDao::findCourseByCid(s.getId()).getId().empty())
    {
        CourseDao::updateTid(s,s.getTeacherId());
        CourseDao::updateName(s,s.getName());
    }
    else
        CourseDao::insertRecord(s);
    CourseQuery();
}


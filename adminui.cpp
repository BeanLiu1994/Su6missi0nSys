#include "adminui.h"
#include "ui_adminui.h"
#include "propertymaker.h"


void SetTableWidgetStyle(QTableWidget* tbw)
{
    tbw->setSelectionBehavior(QAbstractItemView::SelectRows);
    tbw->horizontalHeader()->setHighlightSections(false);
    tbw->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

AdminUI::AdminUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminUI)
{
    ui->setupUi(this);
    SetTableWidgetStyle(ui->teacher_table);
    SetTableWidgetStyle(ui->student_table);
    SetTableWidgetStyle(ui->course_table);
    SetTableWidgetStyle(ui->course_student_table);
    TeacherQuery();
    StudentQuery();
    CourseQuery();
    CourseStudentQuery();

    connect(ui->TeacherRefresh, SIGNAL (released()),this, SLOT (TeacherQuery()));
    connect(ui->StudentRefresh, SIGNAL (released()),this, SLOT (StudentQuery()));
    connect(ui->CourseRefresh, SIGNAL (released()),this, SLOT (CourseQuery()));
    connect(ui->CourseStudentRefresh, SIGNAL (released()),this, SLOT (CourseStudentQuery()));

    connect(ui->teacher_add, SIGNAL (released()),this, SLOT (TeacherAdd()));
    connect(ui->student_add, SIGNAL (released()),this, SLOT (StudentAdd()));
    connect(ui->course_add, SIGNAL (released()),this, SLOT (CourseAdd()));
    connect(ui->course_student_add, SIGNAL (released()),this, SLOT (CourseStudentAdd()));

    connect(ui->teacher_table,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(TeacherDoubleClicked(QTableWidgetItem*)));
    connect(ui->student_table,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(StudentDoubleClicked(QTableWidgetItem*)));
    connect(ui->course_table,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(CourseDoubleClicked(QTableWidgetItem*)));
    connect(ui->course_student_table,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(CourseStudentDoubleClicked(QTableWidgetItem*)));

    connect(ui->teacher_table,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(TeacherIdSelected(QTableWidgetItem*)));
    connect(ui->student_table,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(StudentIdSelected(QTableWidgetItem*)));
    connect(ui->course_table,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(CourseIdSelected(QTableWidgetItem*)));

}

AdminUI::~AdminUI()
{
    delete ui;
}


bool AdminUI::AdminLogin()
{
    //bool Success=QueryForAdminInfo();
    bool Success=true;
    return Success;
}



/* id changes and auto fill */
void AdminUI::CourseIdSelected(QTableWidgetItem *item)
{
    QString id = ui->course_table->item(item->row(),1)->text();
    ui->course_student_cid_input->setText(id);

    CourseStudentQueryCid(id.toLocal8Bit().toStdString());
}

void AdminUI::StudentIdSelected(QTableWidgetItem *item)
{
    QString id = ui->student_table->item(item->row(),1)->text();
    ui->course_student_sid_input->setText(id);

    CourseStudentQuerySid(id.toLocal8Bit().toStdString());
}

void AdminUI::TeacherIdSelected(QTableWidgetItem *item)
{
    QString id = ui->teacher_table->item(item->row(),1)->text();
    ui->course_tid_input->setText(id);

    CourseQueryTid(id.toLocal8Bit().toStdString());
}



/* deleting part */
void AdminUI::TeacherDoubleClicked(QTableWidgetItem *item)
{
    string id = ui->teacher_table->item(item->row(),1)->text().toLocal8Bit().toStdString();
    TeacherDao::deleteRecord(id);
    TeacherQuery();
}
void AdminUI::StudentDoubleClicked(QTableWidgetItem *item)
{
    string id = ui->student_table->item(item->row(),1)->text().toLocal8Bit().toStdString();
    StudentDao::deleteRecord(id);
    StudentQuery();
}
void AdminUI::CourseDoubleClicked(QTableWidgetItem *item)
{
    string id = ui->course_table->item(item->row(),1)->text().toLocal8Bit().toStdString();
    CourseDao::deleteRecord(id);
    CourseQuery();
}
void AdminUI::CourseStudentDoubleClicked(QTableWidgetItem *item)
{
    string sid = ui->course_student_table->item(item->row(),0)->text().toLocal8Bit().toStdString();
    string cid = ui->course_student_table->item(item->row(),1)->text().toLocal8Bit().toStdString();
    CourseStuDao::deleteRecord(cid,sid);
    CourseStudentQuery();
}


/* Teacher refresh and add */
void AdminUI::TeacherQuery()
{
    vector<Teacher> ts=TeacherDao::findAllTeachers();
    QStringList header;
    header<<tr("Name")<<tr("Id");
    ui->course_student_table->setColumnCount(2);
    ui->teacher_table->setHorizontalHeaderLabels(header);
    ui->teacher_table->setRowCount((int)ts.size());
    ui->teacher_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        Teacher & m = ts[i];
        ui->teacher_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->teacher_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
    }
}
void AdminUI::TeacherAdd()
{
    Teacher t;
    t.setId(ui->teacher_id_input->text().toLocal8Bit().toStdString());
    t.setName(ui->teacher_name_input->text().toLocal8Bit().toStdString());
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

/* Student refresh and add */
void AdminUI::StudentQuery()
{
    vector<Student> ts=StudentDao::findAllStudents();
    //printf("length: %d\n",ts.size());
    QStringList header;
    header<<tr("Name")<<tr("Id");
    ui->course_student_table->setColumnCount(2);
    ui->student_table->setHorizontalHeaderLabels(header);
    ui->student_table->setRowCount((int)ts.size());
    ui->student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        Student & m = ts[i];
        ui->student_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->student_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
    }
}
void AdminUI::StudentAdd()
{
    Student s;
    s.setId(ui->student_id_input->text().toLocal8Bit().toStdString());
    s.setName(ui->student_name_input->text().toLocal8Bit().toStdString());
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

/* Course refresh and add */
void AdminUI::CourseQuery()
{
    vector<Course> ts=CourseDao::findAllCourses();
    //printf("length: %d\n",ts.size());
    QStringList header;
    header<<tr("Name")<<tr("Id")<<tr("TeacherId");
    ui->course_student_table->setColumnCount(3);
    ui->course_table->setHorizontalHeaderLabels(header);
    ui->course_table->setRowCount((int)ts.size());
    ui->course_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        Course & m = ts[i];
        ui->course_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->course_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
        ui->course_table->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(m.getTeacherId().c_str())));
    }
}
void AdminUI::CourseQueryTid(string & tid)
{
    vector<Course> ts=CourseDao::findCourseByTid(tid);
    //printf("length: %d\n",ts.size());
    QStringList header;
    header<<tr("Name")<<tr("Id")<<tr("TeacherId");
    ui->course_student_table->setColumnCount(3);
    ui->course_table->setHorizontalHeaderLabels(header);
    ui->course_table->setRowCount((int)ts.size());
    ui->course_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        Course & m = ts[i];
        ui->course_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getName().c_str())));
        ui->course_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
        ui->course_table->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(tid.c_str())));
    }
}
void AdminUI::CourseAdd()
{
    Course s;
    s.setId(ui->course_id_input->text().toLocal8Bit().toStdString());
    s.setName(ui->course_name_input->text().toLocal8Bit().toStdString());
    s.setTeacherId(ui->course_tid_input->text().toStdString());
    if(!CourseDao::findCourseByCid(s.getId()).getId().empty())
    {
        CourseDao::updateTid(s,s.getTeacherId());
        CourseDao::updateName(s,s.getName());
    }
    else
        CourseDao::insertRecord(s);
    CourseQuery();
}

/* CourseStudent refresh and add */
void AdminUI::CourseStudentQuery()
{
    vector<CourseStu> ts=CourseStuDao::findAllCourseStus();
    //printf("length: %d\n",ts.size());
    QStringList header;
    header<<tr("StudentId")<<tr("CourseId");
    ui->course_student_table->setColumnCount(2);
    ui->course_student_table->setHorizontalHeaderLabels(header);
    ui->course_student_table->setRowCount((int)ts.size());
    ui->course_student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        CourseStu & m = ts[i];
        ui->course_student_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getsid().c_str())));
        ui->course_student_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getcid().c_str())));
    }
}
void AdminUI::CourseStudentQuerySid(string &sid)
{
    vector<Course> ts=CourseStuDao::findCourseBySid(sid);
    QStringList header;
    header<<tr("StudentId")<<tr("CourseId");
    ui->course_student_table->setColumnCount(2);
    ui->course_student_table->setHorizontalHeaderLabels(header);
    ui->course_student_table->setRowCount((int)ts.size());
    ui->course_student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        Course & m = ts[i];
        ui->course_student_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(sid.c_str())));
        ui->course_student_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
    }
}
void AdminUI::CourseStudentQueryCid(string &cid)
{
    vector<Student> ts=CourseStuDao::findStudentByCid(cid);
    QStringList header;
    header<<tr("StudentId")<<tr("CourseId");
    ui->course_student_table->setColumnCount(2);
    ui->course_student_table->setHorizontalHeaderLabels(header);
    ui->course_student_table->setRowCount((int)ts.size());
    ui->course_student_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<ts.size();++i)
    {
        Student & m = ts[i];
        ui->course_student_table->setItem(i,0,new QTableWidgetItem(QString::fromLocal8Bit(m.getId().c_str())));
        ui->course_student_table->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(cid.c_str())));
    }
}
void AdminUI::CourseStudentAdd()
{
    string sid = ui->course_student_sid_input->text().toLocal8Bit().toStdString();
    string cid = ui->course_student_cid_input->text().toLocal8Bit().toStdString();
    CourseStuDao::insertRecord(cid,sid);
    CourseStudentQuery();
}


#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL (released()),this, SLOT (TeacherQuery()));
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
    printf("length: %d\n",ts.size());
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

#include "mainwindow.h"
#include "loginui.h"
#include "adminui.h"
#include <QApplication>
#include <QTextCodec>
#include<iostream>
#include<string>
#include "utils/DBUtil.h"
#include "entity/Student.h"
#include "dao/StudentDao.h"
#include "entity/Teacher.h"
#include "dao/TeacherDao.h"
#include "entity/Course.h"
#include "dao/CourseDao.h"
#include "entity/Work.h"
#include "dao/WorkDao.h"
#include "dao/CourseStuDao.h"
#include "entity/Upload.h"
#include "dao/UploadDao.h"
#include "time.h"
using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    AdminUI admUI;

    //w.show();
    LoginUi l;
    l.show();



    return a.exec();
}

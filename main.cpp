#include "mainwindow.h"
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
string getCurTime(){
    const time_t t = time(NULL);
    struct tm* current_time = localtime(&t);
    int year=current_time->tm_year+1900;
    int month=current_time->tm_mon+1;
    int day=current_time->tm_mday;
    char s[20];
    sprintf(s,"%d-%d-%d",year,month,day);
    string s1(s);
    return s1;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}

#ifndef HEADERS_H
#define HEADERS_H


#include <QWidget>
#include <QDialog>
#include <QMenu>
#include <QCloseEvent>
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>


#include "entity/Upload.h"
#include "entity/Work.h"
#include "entity/Course.h"
#include "entity/Teacher.h"
#include "entity/Student.h"
#include "utils/DBUtil.h"
#include "dao/StudentDao.h"
#include "dao/TeacherDao.h"
#include "dao/CourseDao.h"
#include "dao/WorkDao.h"
#include "dao/CourseStuDao.h"
#include "dao/UploadDao.h"
#include "propertymaker.h"


#include <iostream>
using std::string;


#endif // HEADERS_H

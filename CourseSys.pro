#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T16:17:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseSys
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dao/CourseDao.cpp \
    dao/CourseStuDao.cpp \
    dao/StudentDao.cpp \
    dao/TeacherDao.cpp \
    dao/UploadDao.cpp \
    dao/WorkDao.cpp \
    utils/DBUtil.cpp \
    loginui.cpp \
    adminui.cpp \
    studentui.cpp \
    teacherui.cpp

HEADERS  += mainwindow.h \
    dao/CourseDao.h \
    dao/CourseStuDao.h \
    dao/StudentDao.h \
    dao/TeacherDao.h \
    dao/UploadDao.h \
    dao/WorkDao.h \
    entity/Course.h \
    entity/Student.h \
    entity/Teacher.h \
    entity/Upload.h \
    entity/Work.h \
    utils/DBUtil.h \
    propertymaker.h \
    loginui.h \
    adminui.h \
    studentui.h \
    headers.h \
    teacherui.h

FORMS    += mainwindow.ui \
    loginui.ui \
    adminui.ui \
    studentui.ui \
    teacherui.ui

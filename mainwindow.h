#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include "ui_mainwindow.h"
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
#include <QMenu>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool AdminLogin();
public slots:
    void TeacherQuery();
    void CourseQuery();
    void StudentQuery();
    void TeacherAdd();
    void CourseAdd();
    void StudentAdd();
private slots:
    void TeacherDoubleClicked(QTableWidgetItem *item);
    void StudentDoubleClicked(QTableWidgetItem *item);
    void CourseDoubleClicked(QTableWidgetItem *item);
private:

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H

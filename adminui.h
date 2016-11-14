#ifndef ADMINUI_H
#define ADMINUI_H

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

#include <QDialog>

namespace Ui {
class AdminUI;
}

class AdminUI : public QDialog
{
    Q_OBJECT

public:
    explicit AdminUI(QWidget *parent = 0);
    ~AdminUI();

public slots:
    void show();
    void TeacherQuery();
    void TeacherAdd();
    void StudentQuery();
    void StudentAdd();
    void CourseQuery();
    void CourseQueryTid(string &tid);
    void CourseAdd();
    void CourseStudentQuery();
    void CourseStudentQuerySid(string &sid);
    void CourseStudentQueryCid(string &cid);
    void CourseStudentAdd();
private slots:
    void TeacherDoubleClicked(QTableWidgetItem *item);
    void StudentDoubleClicked(QTableWidgetItem *item);
    void CourseDoubleClicked(QTableWidgetItem *item);
    void CourseStudentDoubleClicked(QTableWidgetItem *item);
    void TeacherIdSelected(QTableWidgetItem* item);
    void StudentIdSelected(QTableWidgetItem *item);
    void CourseIdSelected(QTableWidgetItem *item);
private:
    Ui::AdminUI *ui;

protected:
    void closeEvent(QCloseEvent*);

public:
    static AdminUI * GetCurrent()
    {
        if(Current==nullptr)
            new AdminUI();
        return Current;
    }
private:
    static AdminUI * Current;


};

#endif // ADMINUI_H

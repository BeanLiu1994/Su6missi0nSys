#ifndef ADMINUI_H
#define ADMINUI_H

#include "headers.h"
#include "ui_mainwindow.h"

namespace Ui {
class AdminUI;
}

class AdminUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminUI(QWidget *parent = 0);
    ~AdminUI();
signals:
    void WindowClosed(void);

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
    void WorkAdd();
    void WorkQuery();
    void WorkQueryByCid(string &cid);
    void UploadAdd();
    void UploadQuery();
    void UploadQueryByWid(string &wid);
    void UploadQueryBySid(string &sid);
private slots:
    void TeacherDoubleClicked(QTableWidgetItem *item);
    void StudentDoubleClicked(QTableWidgetItem *item);
    void CourseDoubleClicked(QTableWidgetItem *item);
    void CourseStudentDoubleClicked(QTableWidgetItem *item);
    void WorkDoubleClicked(QTableWidgetItem *item);
    void UploadDoubleClicked(QTableWidgetItem *item);

    void TeacherIdSelected(QTableWidgetItem* item);
    void StudentIdSelected(QTableWidgetItem *item);
    void CourseIdSelected(QTableWidgetItem *item);
    void WorkIdSelected(QTableWidgetItem *item);
private:
    Ui::AdminUI *ui;
    vector<QWidget *> windows;
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

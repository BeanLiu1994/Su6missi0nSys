#ifndef TEACHERUI_H
#define TEACHERUI_H

#include "headers.h"

namespace Ui {
class TeacherUi;
}

class TeacherUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherUi(QWidget *parent = 0);
    ~TeacherUi();
    void setId(QString Id);

public slots:
    void CourseQueryTid();
    void ShowStudent(vector<Student> stu=vector<Student>());
    void SelectStudent();
    void FillStudent();
    void FillHomework();
    void ChangePasswd();
    void WorkLibEnter();
    void AddWorkEnter();
    void ShowAllScores();
    void ScoreChanged(double);

signals:
    void WindowClosed();

private:
    Ui::TeacherUi *ui;
    QString Id;
    vector<Course> courses;
    vector<Work> works;
    vector<Upload> uploads;
    vector<Student> students;
    //bool eventFilter(QObject *watched, QEvent *event);
protected:
    void closeEvent(QCloseEvent*);

public:
    static TeacherUi * GetCurrent()
    {
        if(Current==nullptr)
            new TeacherUi();
        return Current;
    }
private:
    static TeacherUi * Current;
};

#endif // TEACHERUI_H

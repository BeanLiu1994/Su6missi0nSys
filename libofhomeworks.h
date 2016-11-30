#ifndef LIBOFHOMEWORKS_H
#define LIBOFHOMEWORKS_H

#include "headers.h"
#include <QButtonGroup>


namespace Ui {
class LibOfHomeworks;
}

class LibOfHomeworks : public QDialog
{
    Q_OBJECT

public:
    explicit LibOfHomeworks(QWidget *parent = 0);
    ~LibOfHomeworks();
public slots:
    void CourseSelected();
    void onHeaderClicked(int);
    void AddSelected();
    void SelectedWorksShow();
    void getCourses();
    void getWorks(string& cid=string(""));
    void UpdateDeadtime();
    void onHeaderClicked_2(int);
    void AddWorks();
    void SetTid(string Tid);
signals:
    void workChanged();

private:
    Ui::LibOfHomeworks *ui;
    vector<Course> courses;
    vector<Work> works_on_show;
    vector<Work> works_to_be_added;
    QButtonGroup radiobuttons;
    string Tid;
    bool CheckWid(string&, vector<Work>&);
};

#endif // LIBOFHOMEWORKS_H

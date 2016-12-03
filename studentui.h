#ifndef STUDENTUI_H
#define STUDENTUI_H

#include "headers.h"

namespace Ui {
class StudentUi;
}

class StudentUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentUi(QWidget *parent = 0);
    ~StudentUi();
    void setId(QString Id);
private slots:
    void onSelSub(const QString& currentText);
    void onSelBat(const QString& text);
    void BtnSubmit();
    void BtnChangePwd();
    void BtnSelect();
    void BtnUpdate();
    void tableDoubleClicked( QTableWidgetItem *rowItem);
signals:
    void WindowClosed();
private:
    Ui::StudentUi *ui;
    QString id;
    vector<Course> v; //course

    string courseId;   //current course
    string currentwtime;  // current batch
    Work w;   //current work

    void setTable();
    void showTaskAns();

protected:
    void closeEvent(QCloseEvent*);

public:
    static StudentUi * GetCurrent()
    {
        if(Current==nullptr)
            new StudentUi();
        return Current;
    }
private:
    static StudentUi * Current;

};

#endif // STUDENTUI_H

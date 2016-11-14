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

private:
    Ui::TeacherUi *ui;

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

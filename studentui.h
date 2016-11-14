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

private:
    Ui::StudentUi *ui;

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

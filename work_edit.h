#ifndef WORK_EDIT_H
#define WORK_EDIT_H

#include "headers.h"

namespace Ui {
class work_edit;
}

class work_edit : public QDialog
{
    Q_OBJECT

public:
    explicit work_edit(QWidget *parent = 0);
    void init(string& wid);
    void init(string& cid,string& time);
    void init(Work w_in);// find by cid and time
    ~work_edit();

private slots:
    void WorkAdd();
    void WorkDelete();

private:
    Ui::work_edit *ui;
    string wid;
};

#endif // WORK_EDIT_H

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
    void init();
    void init(string& wid);
    void init(Course& c);
    void init(Work w_in);// find by cid and time
    ~work_edit();

signals:
    void workChanged();

private slots:
    void WorkAdd();
    void WorkDelete();

private:
    Ui::work_edit *ui;
    string wid;
};

#endif // WORK_EDIT_H

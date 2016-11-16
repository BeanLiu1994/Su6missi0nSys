#ifndef CHANGEPWD_H
#define CHANGEPWD_H

#include "headers.h"
enum UserType
{
    tStudent,tTeacher,tAdmin
};

namespace Ui {
class changepwd;
}

class changepwd : public QDialog
{
    Q_OBJECT

public:
    explicit changepwd(QWidget *parent = 0);
    ~changepwd();
    void init(QString Id,UserType);
private slots:
    void BtnOK();
    void BtnCancel();
private:
    Ui::changepwd *ui;
    QString id;
    UserType tp;

protected:
    void closeEvent(QCloseEvent*);
};

#endif // CHANGEPWD_H

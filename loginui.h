#ifndef LOGINUI_H
#define LOGINUI_H

#include <QDialog>
#include <iostream>
using std::string;

namespace Ui {
class LoginUi;
}

class LoginUi : public QDialog
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = 0);
    ~LoginUi();
    string Id;
    string Password;
signals:
    void TeacherLoggedIn(string Id);
    void AdminLoggedIn(string Id);
    void StudentLoggedIn(string Id);

public slots:
    void ExitFromSubDialog();

private slots:
    void LoginProcess();

private:
    Ui::LoginUi *ui;

    bool AdminLoginProcess();
    bool TeacherLoginProcess();
    bool StudentLoginProcess();

public:
    static LoginUi * GetCurrent()
    {
        if(Current==nullptr)
            new LoginUi();
        return Current;
    }
private:
    static LoginUi * Current;

};

#endif // LOGINUI_H

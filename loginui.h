#ifndef LOGINUI_H
#define LOGINUI_H

#include <QDialog>

namespace Ui {
class LoginUi;
}

class LoginUi : public QDialog
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = 0);
    ~LoginUi();

private:
    Ui::LoginUi *ui;
};

#endif // LOGINUI_H

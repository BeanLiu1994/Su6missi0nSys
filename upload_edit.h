#ifndef UPLOAD_EDIT_H
#define UPLOAD_EDIT_H

#include "headers.h"

namespace Ui {
class upload_edit;
}

class upload_edit : public QDialog
{
    Q_OBJECT

public:
    explicit upload_edit(QWidget *parent = 0);
    ~upload_edit();
    void init();
    void init(string& uid);
    void init(string& wid,string& sid);
    void init(Upload& u);

signals:
    void uploadChanged();

private slots:
    void UploadDelete();
    void UploadAdd();

private:
    Ui::upload_edit *ui;
    string uid;
};

#endif // UPLOAD_EDIT_H

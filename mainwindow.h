#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//Template of QMainWindow Based Classes

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setId(QString Id);

private:
    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent*);

public:
    static MainWindow * GetCurrent()
    {
        if(Current==nullptr)
            new MainWindow();
        return Current;
    }
private:
    static MainWindow * Current;

};

#endif // MAINWINDOW_H

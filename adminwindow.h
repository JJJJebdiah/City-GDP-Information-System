#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT
public:
    User u;
    UserFile uf;
    QStringList l;//表头


public:
    explicit AdminWindow(QWidget *parent = nullptr,User u=0);
    ~AdminWindow();
    void showtable();
    void showtableheader();
    void setheader();
    void setstyle();//设置界面美化

private slots:
    void on_pushButton_clicked();

    void on_btn_search_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H

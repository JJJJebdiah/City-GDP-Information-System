#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "city.h"
#include "user.h"


namespace Ui {
class UserWindow;
}


class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    User u;
    CityFile cf;
    QStringList l;//表头

public:
    explicit UserWindow(QWidget *parent = nullptr,User u=0);
    ~UserWindow();
    void showtable();//显示表
    void showtableheader();//显示表头
    void setheader();//设置表头
    void setstyle();//设置界面美化

private slots:
    void inputdata();//手写输入城市
    void fileinput();//文件输入城市
    void deleteUser();//注销用户
    void updateUser();//修改用户信息

    void on_pushButton_clicked();//退出
    void on_btn_search_clicked();//查找
    void on_pushButton_clear_clicked();//清除城市
    void on_pushButton_add_clicked();//添加城市
    void on_pushButton_delete_clicked();//删除城市
    void on_pushButton_update_clicked();//修改城市
    void on_btn_username_clicked();//打开用户信息界面
    void on_btn_predict_clicked();//预测gdp

private:
    Ui::UserWindow *ui;
};

#endif // USERWINDOW_H

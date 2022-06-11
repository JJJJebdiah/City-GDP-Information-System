#ifndef DIALOGINPUTUSER_H
#define DIALOGINPUTUSER_H

#include <QDialog>
#include"user.h"

namespace Ui {
class DialogInputUser;
}

enum userType
{
    add=0,
    update=1
};

class DialogInputUser : public QDialog
{
    Q_OBJECT

public:
    User& u;
    User copy;
    userType t;

public:
    explicit DialogInputUser(User& u,userType t,QWidget *parent = nullptr);
    ~DialogInputUser();
     void tableheader();//显示表头
     void setstyle();//设置界面美化
private slots:
    void on_btn_cancle_clicked();//取消

    void on_btn_save_clicked();//保存

    void itemchanged(int row, int column);//对元素被修改的响应

private:
    Ui::DialogInputUser *ui;
};

#endif // DIALOGINPUTUSER_H

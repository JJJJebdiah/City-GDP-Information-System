#ifndef DIALOGREVISEUSER_H
#define DIALOGREVISEUSER_H

#include <QDialog>
#include"user.h"

namespace Ui {
class DialogReviseUser;
}

class DialogReviseUser : public QDialog
{
    Q_OBJECT

public:
    User& u;

public:
    explicit DialogReviseUser(User& u,QWidget *parent = nullptr);
    ~DialogReviseUser();
    void setstyle();//设置界面美化

private slots:

    void on_btn_save_clicked();//保存

    void on_pushButton_clicked();//退出

    void on_btn_delete_clicked();//注销


private:
    Ui::DialogReviseUser *ui;

signals:
    void deleteUser();//注销该用户
    void updateUser();//修改该用户



};

#endif // DIALOGREVISEUSER_H

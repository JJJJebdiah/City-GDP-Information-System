#ifndef SIGNWINDOW_H
#define SIGNWINDOW_H

#include <QWidget>
#include"user.h"



QT_BEGIN_NAMESPACE
namespace Ui { class SignWindow; }
QT_END_NAMESPACE

class SignWindow : public QWidget
{
    Q_OBJECT

private:
    UserFile uf;

public:
    SignWindow(QWidget *parent = nullptr);
    ~SignWindow();
    void setstyle();//设置界面美化

private slots:

    void on_pushButtonSignUp_clicked();;//打开注册界面

    void on_pushButtonLogIn_clicked();

private:
    Ui::SignWindow *ui;
};



#endif // SIGNWINDOW_H

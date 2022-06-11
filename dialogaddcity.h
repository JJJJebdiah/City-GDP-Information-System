#ifndef DIALOGADDCITY_H
#define DIALOGADDCITY_H

#include <QDialog>

namespace Ui {
class DialogAddCity;
}

class DialogAddCity : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddCity(QWidget *parent = nullptr);
    ~DialogAddCity();
    void setstyle();//设置界面美化

private slots:

    void on_btn_cancle_clicked();//取消

    void on_btn_input_clicked();//手动输入

    void on_btn_file_clicked();//文件输入

signals:
    void input();//手动输入
    void file();//文件输入

private:
    Ui::DialogAddCity *ui;
};

#endif // DIALOGADDCITY_H

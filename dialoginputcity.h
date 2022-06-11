#ifndef DIALOGINPUTCITY_H
#define DIALOGINPUTCITY_H

#include "city.h"
#include <QDialog>

namespace Ui {
class DialogInputCity;
}

enum Type
{
    add=0,
    update=1
};

class DialogInputCity : public QDialog
{
    Q_OBJECT

public:
    City& c;
    City copy;
    Type t;

public:
    explicit DialogInputCity(City& c,Type t,QWidget *parent = nullptr);
    ~DialogInputCity();
    void tableheader();
    void setstyle();//设置界面美化

private slots:
    void on_btn_cancle_clicked();
    void itemchanged(int row, int column);
    void on_btn_save_clicked();

private:
    Ui::DialogInputCity *ui;


};

#endif // DIALOGINPUTCITY_H

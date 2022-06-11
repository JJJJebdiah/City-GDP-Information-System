#ifndef DIALOGSIGNUP_H
#define DIALOGSIGNUP_H

#include <QDialog>
#include"signwindow.h"
#include"user.h"

namespace Ui {
class DialogSignUp;
}

enum siType
{
    admin=0,
    user
};

class DialogSignUp : public QDialog
{
    Q_OBJECT
public:
    siType t;
    UserFile& uf;

public:
    explicit DialogSignUp(UserFile& uf,siType t,QWidget *parent = nullptr);
    ~DialogSignUp();
    void setstyle();//设置界面美化


private slots:


private:
    Ui::DialogSignUp *ui;

public slots:
    void accept();
};


#endif // DIALOGSIGNUP_H

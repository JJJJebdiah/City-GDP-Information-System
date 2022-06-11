#include "dialogsignup.h"
#include "ui_dialogsignup.h"
#include<QDebug>
#include<QString>
#include<QMessageBox>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
DialogSignUp::DialogSignUp(UserFile& uf,siType t,QWidget *parent) :
    QDialog(parent),t(t),uf(uf),
    ui(new Ui::DialogSignUp)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    if(t==siType::admin)
    {
        ui->lineEdit_username->setText("admin");
        ui->lineEdit_username->setReadOnly(true);
    }
    setstyle();
}

DialogSignUp::~DialogSignUp()
{
    delete ui;
}

void DialogSignUp::setstyle()
{
    QString s=QCoreApplication::applicationDirPath()+"/Mycss/dialogsignupstyle.css";
    QFile file(s);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        return;
    }
    QString m=file.readAll();
    this->setStyleSheet(m);
}

void DialogSignUp::accept()
{

    //检查用户名格式：只能是字母和_
    QString username=ui->lineEdit_username->text();
    if(t==siType::user)
    {
        if(username.size()>11)
        {
            QMessageBox::warning(this,"错误","用户名不规范!");
            return;
        }
        for(auto& i:username)
        {
            if((i>='a'&&i<='z')||(i>='A'&&i<='Z')||i=='_'||(i>='0'&&i<='9'))
            {

            }
            else
            {
                QMessageBox::warning(this,"错误","用户名不规范!");
                return;
            }
        }
    }

    //检查密码格式：不能有空格和逗号
    QString password=ui->lineEdit_password->text();
    if(password.isEmpty()) return;
    for(auto& i:password)
    {
        if(i==' '||i==',')
        {
            QMessageBox::warning(this,"错误","密码格式错误!");
            return;
        }
    }
    //检查再次输入密码
    QString password2=ui->lineEdit_password2->text();
    if(password2.isEmpty()) return;
    if(password2!=password)
    {
        QMessageBox::warning(this,"错误","再次输入密码错误!");
        return;
    }

    QString name=ui->lineEdit_name->text();
    if(name.isEmpty()) return;
    for(auto& i:name)
    {
        if(i==' ')
        {
            QMessageBox::warning(this,"错误","姓名格式错误!");
            return;
        }

    }
    QString phone=ui->lineEdit_phone->text();
    if(phone.isEmpty()) return;
    for(auto& i:phone)
    {
        if(i==' ')
        {
            QMessageBox::warning(this,"错误","电话格式错误!");
            return;
        }

    }
    //存储信息
    User u;
    u.m_username=username;
    u.m_password=password;
    u.m_name=name;
    u.m_phone=phone;
    if(uf.addUser(u))
    {
        QMessageBox::about(this,"注册","注册成功！");
        this->close();
        return;

    }
    else
    {
        QMessageBox::warning(this,"错误","用户名重复!");
        return;
    }


}






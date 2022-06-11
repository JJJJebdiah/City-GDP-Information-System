#include "dialogreviseuser.h"
#include "ui_dialogreviseuser.h"
#include"userwindow.h"
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include <QFile>

DialogReviseUser::DialogReviseUser(User& u,QWidget *parent) :
    QDialog(parent),u(u),
    ui(new Ui::DialogReviseUser)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->lineEdit_username->setText(u.m_username);
    ui->lineEdit_name->setPlaceholderText(u.m_name);
    ui->lineEdit_phone->setPlaceholderText(u.m_phone);
    setstyle();
}

DialogReviseUser::~DialogReviseUser()
{
    delete ui;
}

void DialogReviseUser::setstyle()
{
    QString s=QCoreApplication::applicationDirPath()+"/Mycss/dialogreviseuser.css";
    QFile file(s);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        return;
    }
    QString m=file.readAll();
    this->setStyleSheet(m);
}




void DialogReviseUser::on_btn_save_clicked()
{
    bool is=false;
    QString name=ui->lineEdit_name->text();
    QString phone=ui->lineEdit_phone->text();
    QString password=ui->lineEdit_password->text();
    QString password2=ui->lineEdit_password2->text();
    if(!name.isEmpty())
    {
        for(auto& i:name)
        {
            if(i==' '||i==',')
            {
                QMessageBox::warning(this,"错误","姓名格式错误!");
                return;
            }

        }
        u.m_name=name;
        is=true;
    }
    if(!phone.isEmpty())
    {
        for(auto& i:phone)
        {
            if(i==' '||i==',')
            {
                QMessageBox::warning(this,"错误","电话格式错误!");
                return;
            }

        }
        u.m_phone=phone;
        is=true;
    }
    if(!password.isEmpty())
    {
        for(auto& i:password)
        {
            if(i==' '||i==',')
            {
                QMessageBox::warning(this,"错误","密码格式错误!");
                return;
            }
        }
        if(password2!=password)
        {
            QMessageBox::warning(this,"错误","再次输入密码错误!");
            return;
        }
        u.m_password=password;
        is=true;
    }
    if(is)
    {
        if(QMessageBox::warning(this,"警告","请确认是否更改！",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
        {
            //保存新的信息
            this->close();
            emit updateUser();
        }

    }
    else this->close();
}


void DialogReviseUser::on_pushButton_clicked()
{
    this->close();
}


void DialogReviseUser::on_btn_delete_clicked()
{
    if(QMessageBox::warning(this,"警告","请确认是否注销！注销后所有信息将被清除无法找回！",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        //删除该用户所有信息
        this->close();
        emit deleteUser();
    }
}


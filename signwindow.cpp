#include "signwindow.h"
#include "ui_signwindow.h"
#include"dialogsignup.h"
#include"userwindow.h"
#include"adminwindow.h"
#include<QString>
#include<QDebug>
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>



SignWindow::SignWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    setstyle();
    if(uf.lu.size()==0)//无管理员
    {
        if(QMessageBox::warning(this,"警告","首次登陆需要注册管理员",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Cancel)
        {
            this->close();
            exit(0);
        }
        DialogSignUp* diasu=new DialogSignUp(uf,siType::admin);
        diasu->exec();

    }

}

SignWindow::~SignWindow()
{
    delete ui;
}

void SignWindow::setstyle()
{
    QString s=QCoreApplication::applicationDirPath()+"/Mycss/signwindowstyle.css";
    QFile file(s);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        qDebug()<<s;
        return;
    }
    QString m=file.readAll();
    this->setStyleSheet(m);

}


void SignWindow::on_pushButtonSignUp_clicked()
{
    DialogSignUp* diasu=new DialogSignUp(uf,siType::user);
    diasu->show();
}


void SignWindow::on_pushButtonLogIn_clicked()
{
    //debug
    /*User u;
    u.m_name="debug";
    u.m_username="debug";
    u.m_phone="debug";
    UserWindow* uw=new UserWindow(nullptr,u);
    uw->show();
    this->close();
    return;*/
    //debug
    QString username=ui->lineEdit_username->text();
    QString password=ui->lineEdit_password->text();
    if(username.size()*password.size()==0)
    {
        QMessageBox::about(this,"登陆","账号或密码错误!#1");
        return;
    }
    if(uf.lu[0].m_username==username&&uf.lu[0].m_password==password)
    {
        QMessageBox::about(this,"登陆","管理员登陆成功！");
        //管理员界面
        AdminWindow* aw=new AdminWindow(nullptr,uf.lu[0]);
        aw->show();
        this->close();
        return;
    }
    else if(uf.lu[0].m_username==username)
    {
        QMessageBox::about(this,"登陆","密码错误!#2");
        return;
    }
    if(uf.lu.size()==1)
    {
        QMessageBox::warning(this,"登陆失败","用户名或密码错误！#3");
        return;
    }
    for(int i=1;i<uf.lu.size();++i)
    {
        if(uf.lu[i].m_username==username&&uf.lu[i].m_password==password)
        {
            QMessageBox::about(this,"登陆成功","登陆成功！");
            UserWindow* uw=new UserWindow(nullptr,uf.lu[i]);
            uw->show();
            this->close();
            return;
        }
        else if(uf.lu[i].m_username==username)
        {
            QMessageBox::about(this,"登陆","密码错误!#4");
            return;
        }

    }
    QMessageBox::warning(this,"登陆失败","用户名或密码错误！#5");
    ui->lineEdit_password->clear();
    ui->lineEdit_username->clear();




}





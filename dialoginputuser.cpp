#include "dialoginputuser.h"
#include "ui_dialoginputuser.h"

#include <QFile>
#include <QMessageBox>

DialogInputUser::DialogInputUser(User& u,userType t,QWidget *parent) :
    QDialog(parent),u(u),copy(u),t(t),
    ui(new Ui::DialogInputUser)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    tableheader();
    ui->tableWidget->setRowCount(1);
    if(userType::update==t)
    {
        int colu=0;
        ui->tableWidget->setItem(0,colu++,new QTableWidgetItem(QString(u.m_username)));
        ui->tableWidget->setItem(0,colu++,new QTableWidgetItem(QString(u.m_password)));
        ui->tableWidget->setItem(0,colu++,new QTableWidgetItem(QString(u.m_name)));
        ui->tableWidget->setItem(0,colu++,new QTableWidgetItem(QString(u.m_phone)));
        connect(ui->tableWidget,&QTableWidget::cellChanged,this,&DialogInputUser::itemchanged);
    }
    setstyle();

}

DialogInputUser::~DialogInputUser()
{
    delete ui;
}

void DialogInputUser::tableheader()
{
    QStringList l;
    l<<"用户名";
    l<<"密码";
    l<<"姓名";
    l<<"电话";
    ui->tableWidget->setColumnCount(l.size());
    ui->tableWidget->setHorizontalHeaderLabels(l);
}

void DialogInputUser::setstyle()
{
    QString s=QCoreApplication::applicationDirPath()+"/Mycss/dialoginputuserstyle.css";
    QFile file(s);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        return;
    }
    QString m=file.readAll();
    this->setStyleSheet(m);
}

void DialogInputUser::on_btn_cancle_clicked()
{
    this->close();
}

void DialogInputUser::itemchanged(int row, int column)
{

    QString m=ui->tableWidget->item(row,column)->text();
    if(m.isEmpty())
    {
        QMessageBox::warning(this,"错误","数据不能为空!");
        return;
    }
    for(auto& i:m)
    {
        if(i==' '||i==',')
        {
            QMessageBox::warning(this,"错误","格式错误!");
            return;
        }
    }
    if(0==column)
    {
        //QMessageBox::warning(this,"错误","用户名不能修改!");
        ui->tableWidget->itemAt(0,0)->setText(u.m_username);
        return;

    }
    if(1==column)
    {
        copy.m_password=m;

    }

    if(2==column)
    {
        copy.m_name=m;

    }
    if(3==column)
    {
        copy.m_phone=m;

    }
    copy.ischanged=true;



}

void DialogInputUser::on_btn_save_clicked()
{
    if(userType::update==t)
    {
        if(copy.ischanged)
        {
            u=copy;
            u.ischanged=true;
        }
        this->close();
        return;
    }
    else
    {
        //获取信息
        QString m[4];
        for(int column=0;column<4;++column)
        {
            m[column]=ui->tableWidget->item(0,column)->text();
            if(m[column].isEmpty())
            {
                QMessageBox::warning(this,"错误","数据不能为空!");
                return;
            }
            for(auto& i:m)
            {
                if(i==' '||i==',')
                {
                    QMessageBox::warning(this,"错误","格式错误!");
                    return;
                }
            }

        }
        u.m_username=m[0];
        u.m_password=m[1];
        u.m_name=m[2];
        u.m_phone=m[3];
        u.ischanged=true;
        this->close();


    }

}


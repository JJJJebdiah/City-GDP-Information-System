#include "adminwindow.h"
#include "dialoginputuser.h"
#include "dialogsignup.h"
#include "ui_adminwindow.h"

#include <QFile>
#include <QMessageBox>

AdminWindow::AdminWindow(QWidget *parent,User u) :
    QMainWindow(parent),u(u),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    ui->label_username->setText(u.m_username);
    this->setFixedSize(this->size());
    setstyle();

    //设置自适应列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置只能选单行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    setheader();
    showtable();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
void AdminWindow::setstyle()
{
    QString s=QCoreApplication::applicationDirPath()+"/Mycss/adminwindowstyle.css";
    QFile file(s);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        return;
    }
    QString m=file.readAll();
    this->setStyleSheet(m);


}
void AdminWindow::showtable()
{
    ui->tableWidget->clear();
    showtableheader();
    ui->tableWidget->setRowCount(uf.lu.size()-1);

    for(int i=1;i<uf.lu.size();i++)
    {
        int colu=0;
        ui->tableWidget->setItem(i-1,colu++,new QTableWidgetItem(QString(uf.lu[i].m_username)));
        ui->tableWidget->setItem(i-1,colu++,new QTableWidgetItem(QString(uf.lu[i].m_password)));
        ui->tableWidget->setItem(i-1,colu++,new QTableWidgetItem(QString(uf.lu[i].m_name)));
        ui->tableWidget->setItem(i-1,colu++,new QTableWidgetItem(QString(uf.lu[i].m_phone)));

    };
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void AdminWindow::showtableheader()
{
    ui->tableWidget->setColumnCount(l.size());
    ui->tableWidget->setHorizontalHeaderLabels(l);
}

void AdminWindow::setheader()
{
    l<<"用户名";
    l<<"密码";
    l<<"姓名";
    l<<"电话";
}

void AdminWindow::on_pushButton_clicked()
{
    this->close();
}


void AdminWindow::on_btn_search_clicked()
{
    ui->tableWidget->setCurrentItem(nullptr);
    int row=-1;
    QString username=ui->lineEdit_username->text();
    if(username.isEmpty()) return;
    for(int i=0;i<uf.lu.size();++i)
    {
        if(username==uf.lu[i].m_username)
        {
            row=i;
            break;
        }

    }
    if(-1==row)
    {
        QMessageBox::information(this,"查找","未找到！");
        return;
    }
    for(int i=0;i<l.size();++i)
    {
        ui->tableWidget->setCurrentCell(row,i,QItemSelectionModel::Select);
    }
}


void AdminWindow::on_pushButton_add_clicked()
{
    DialogSignUp* dsu=new  DialogSignUp(uf,siType::user);
    dsu->exec();
    showtable();
}


void AdminWindow::on_pushButton_update_clicked()
{
    int i=ui->tableWidget->currentRow()+1;
    if(0==i) return;
    DialogInputUser* diu=new  DialogInputUser(uf.lu[i],userType::update);
    diu->exec();
    if(uf.lu[i].ischanged)
    {
        if(uf.udtUser(uf.lu[i]))
        {
            QMessageBox::information(this,"修改","修改成功");
            showtable();
        }
        else
        {
            QMessageBox::information(this,"修改","修改失败");
        }
        uf.lu[i].ischanged=false;
    }
}


void AdminWindow::on_pushButton_delete_clicked()
{
    int i=ui->tableWidget->currentRow();
    if(-1==i) return;
    if(QMessageBox::warning(this,"警告","请确认是否删除！删除后信息将无法找回！",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        QTableWidgetItem* twi=ui->tableWidget->item(i,0);//获得用户名
        if(uf.delUser(twi->text()))
        {
            QMessageBox::information(this,"删除","删除成功");
            showtable();
        }
        else QMessageBox::information(this,"删除","删除失败");
    }
}


void AdminWindow::on_pushButton_clear_clicked()
{
    if(QMessageBox::warning(this,"警告","请确认是否清空！清空后所有信息将无法找回！",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        uf.clearUser();
        showtable();

    }
}


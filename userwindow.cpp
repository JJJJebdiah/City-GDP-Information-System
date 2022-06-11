#include "userwindow.h"
#include "ui_userwindow.h"
#include"dialogreviseuser.h"
#include"dialogaddcity.h"
#include"dialoginputcity.h"
#include "linearregression.h"
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<QDebug>
#include<QStringList>

UserWindow::UserWindow(QWidget *parent,User u) :
    QMainWindow(parent),
    u(u),cf(u.m_username),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    ui->btn_username->setText(u.m_username);
    this->setMinimumSize(900,680);
    ui->spinBox->hide();    
    setheader();
    showtable();
    setstyle();//美化

    //设置自适应列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //设置只能选单行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::showtable()
{
    ui->tableWidget->clear();
    showtableheader();
    ui->tableWidget->setRowCount(cf.lc.size());

    for(int i=0;i<cf.lc.size();i++)
    {
        int colu=0;
        int a=0,b=0;
        ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].cityname)));
        ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].gdp[a++])));
        ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].gdp[a++])));
        for(;b<7;)
        {
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].p[b].min)));
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].p[b].max)));
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].p[b].ave)));
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].p[b++].v)));
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].gdp[a++])));
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].gdp[a++])));
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].gdp[a++])));
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].gdp[a++])));
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].gdp[a++])));
          ui->tableWidget->setItem(i,colu++,new QTableWidgetItem(QString(cf.lc[i].gdp[a++])));
        }

    };
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void UserWindow::showtableheader()
{

    ui->tableWidget->setColumnCount(l.size());
    ui->tableWidget->setHorizontalHeaderLabels(l);

}

void UserWindow::setheader()
{
    l<<"城市名";
    l<<"2021下";
    l<<"2021上";
    l<<"2018-2020最低";
    l<<"2018-2020最高";
    l<<"2018-2020平均";
    l<<"2018-2020增速";
    l<<"2020下";
    l<<"2020上";
    l<<"2019下";
    l<<"2019上";
    l<<"2018下";
    l<<"2018上";
    l<<"2015-2017最低";
    l<<"2015-2017最高";
    l<<"2015-2017平均";
    l<<"2015-2017增速";
    l<<"2017下";
    l<<"2017上";
    l<<"2016下";
    l<<"2016上";
    l<<"2015下";
    l<<"2015上";
    l<<"2012-2014最低";
    l<<"2012-2014最高";
    l<<"2012-2014平均";
    l<<"2012-2014增速";
    l<<"2014下";
    l<<"2014上";
    l<<"2013下";
    l<<"2013上";
    l<<"2012下";
    l<<"2012上";
    l<<"2009-2011最低";
    l<<"2009-2011最高";
    l<<"2009-2011平均";
    l<<"2009-2011增速";
    l<<"2011下";
    l<<"2011上";
    l<<"2010下";
    l<<"2010上";
    l<<"2009下";
    l<<"2009上";
    l<<"2006-2008最低";
    l<<"2006-2008最高";
    l<<"2006-2008平均";
    l<<"2006-2008增速";
    l<<"2008下";
    l<<"2008上";
    l<<"2007下";
    l<<"2007上";
    l<<"2006下";
    l<<"2006上";
    l<<"2003-2005最低";
    l<<"2003-2005最高";
    l<<"2003-2005平均";
    l<<"2003-2005增速";
    l<<"2005下";
    l<<"2005上";
    l<<"2004下";
    l<<"2004上";
    l<<"2003下";
    l<<"2003上";
    l<<"2000-2002最低";
    l<<"2000-2002最高";
    l<<"2000-2002平均";
    l<<"2000-2002增速";
    l<<"2002下";
    l<<"2002上";
    l<<"2001下";
    l<<"2001上";
    l<<"2000下";
    l<<"2000上";
}

void UserWindow::setstyle()
{
    QString s=QCoreApplication::applicationDirPath()+"/Mycss/userwindowstyle.css";
    QFile file(s);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        return;
    }
    QString m=file.readAll();
    this->setStyleSheet(m);



}



void UserWindow::on_pushButton_clicked()
{
    this->close();
}

void UserWindow::on_pushButton_clear_clicked()
{
    if(QMessageBox::warning(this,"警告","请确认是否清空！清空后所有信息将无法找回！",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        cf.clearCity();
        showtable();

    }
}


void UserWindow::on_pushButton_add_clicked()
{
    if(cf.lc.size()==cf.capacity)
    {
        QMessageBox::information(this,"添加失败","城市个数已满！");
        return;
    }
    DialogAddCity* dac=new DialogAddCity;
    connect(dac,&DialogAddCity::input,this,&UserWindow::inputdata);
    connect(dac,&DialogAddCity::file,this,&UserWindow::fileinput);
    dac->exec();

}


void UserWindow::on_pushButton_delete_clicked()
{
    int i=ui->tableWidget->currentRow();
    if(-1==i) return;
    if(QMessageBox::warning(this,"警告","请确认是否删除！删除后信息将无法找回！",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        QTableWidgetItem* twi=ui->tableWidget->item(i,0);//获得城市名
        if(cf.delCity(twi->text()))
        {
            QMessageBox::information(this,"删除","删除成功");
            showtable();
        }
        else QMessageBox::information(this,"删除","删除失败");
    }

}


void UserWindow::on_pushButton_update_clicked()
{
    int i=ui->tableWidget->currentRow();
    if(-1==i) return;
    DialogInputCity* dic = new DialogInputCity(cf.lc[i],Type::update);
    dic->exec();
    if(cf.lc[i].ischanged)
    {
        if(cf.udtCity(cf.lc[i]))
        {
            QMessageBox::information(this,"修改","修改成功");
            showtable();
        }
        else
        {
            QMessageBox::information(this,"修改","修改失败,城市名重复");
        }
        cf.lc[i].ischanged=false;
    }

}

void UserWindow::inputdata()
{

    City c;
    DialogInputCity* dic = new DialogInputCity(c,Type::add);
    dic->exec();
    if(c.ischanged)
    {
        if(cf.addCity(c))
        {
            QMessageBox::information(this,"添加","添加成功");
            showtable();
        }
        else QMessageBox::information(this,"添加","添加失败,已存在该城市");
        cf.lc.back().ischanged=false;
    }

}

void UserWindow::fileinput()
{
    QString filename=QFileDialog::getOpenFileName(nullptr,"open file",QCoreApplication::applicationDirPath(),"TEXT(*.txt)");
    if(filename.isEmpty()) return;
    QFile file(filename);
    if(!file.open(QIODeviceBase::ReadOnly))
        return;
    QTextStream fin(&file);
    QString content;
    fin>>content;
    content.replace(',',' ');
    QTextStream sin(&content);
    City c;
    sin>>c.cityname;
    for(int i=0;i<44;i++)
    {
        sin>>c.gdp[i];
        for(auto& x:c.gdp[i])
            if(x>'9'||x<'0')
            {
                QMessageBox::critical(this,"","输入数据有误！添加失败");
                return;
            }
        if((i-1)%6==0&&i>1)
        {
            int num[3];
            num[0]=c.gdp[i].toInt()+c.gdp[i-1].toInt();
            num[1]=c.gdp[i-2].toInt()+c.gdp[i-3].toInt();
            num[2]=c.gdp[i-4].toInt()+c.gdp[i-5].toInt();
            c.p[(i-2)/6]=c.calculate(num[0],num[1],num[2]);
        }
    }

    if(cf.addCity(c))
    {
        QMessageBox::information(this,"添加","添加成功");
        showtable();
    }
    else QMessageBox::information(this,"添加","添加失败,已存在该城市");



}



void UserWindow::deleteUser()
{
    cf.clearCity();
    UserFile uf;
    uf.delUser(u.m_username);
    this->close();
}

void UserWindow::updateUser()
{
    UserFile uf;
   if(uf.udtUser(u))
    QMessageBox::information(this,"修改","修改成功");
   else
       QMessageBox::information(this,"修改","修改失败");

}


void UserWindow::on_btn_username_clicked()
{
    DialogReviseUser* dru=new DialogReviseUser(u,this);
    connect(dru,&DialogReviseUser::deleteUser,this,&UserWindow::deleteUser);
    connect(dru,&DialogReviseUser::updateUser,this,&UserWindow::updateUser);
    dru->exec();
}


void UserWindow::on_btn_search_clicked()
{
    ui->tableWidget->setCurrentItem(nullptr);
    int row=-1,col=-1,col1=-1;;
    QString cityname=ui->lineEdit_cityname->text();
    QString year=ui->lineEdit_year->text();
    if(cityname.isEmpty()&&year.isEmpty()) return;
    if(!cityname.isEmpty())
    {
        for(int i=0;i<cf.lc.size();++i)
        {
            if(cityname==cf.lc[i].cityname)
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
    }
    if(!year.isEmpty())
    {
        for(int i=0;i<l.size();i++)
        {
            if(year==l[i])
            {
                col=i;
                break;
            }
            else if(year.size()==4&&l[i].size()==5&&year[0]==l[i][0]&&year[1]==l[i][1]&&year[2]==l[i][2]&&year[3]==l[i][3])
            {
                col=i;
                col1=i+1;
                break;
            }
        }
        if(-1==col)
        {
            QMessageBox::information(this,"查找","未找到！");
            return;
        }
    }
    if(-1!=row&&-1!=col)
    {
        if(-1==col1)
        {
            ui->tableWidget->setCurrentCell(row,col,QItemSelectionModel::Select);
        }
        else
        {
            ui->tableWidget->setCurrentCell(row,col,QItemSelectionModel::Select);
            ui->tableWidget->setCurrentCell(row,col1,QItemSelectionModel::Select);
        }
        return;
    }
    if(-1==row&&-1!=col)
    {
        if(-1==col1)
        {
            for(int i=0;i<cf.lc.size();i++)
            {
                ui->tableWidget->setCurrentCell(i,col,QItemSelectionModel::Select);
            }

        }
        else
        {
            for(int i=0;i<cf.lc.size();i++)
            {
                ui->tableWidget->setCurrentCell(i,col,QItemSelectionModel::Select);
                ui->tableWidget->setCurrentCell(i,col1,QItemSelectionModel::Select);
            }

        }
        return;
    }
    if(-1!=row&&-1==col)
    {
        for(int i=l.size()-1;i>=0;++i)
        {
            ui->tableWidget->setCurrentCell(row,i,QItemSelectionModel::Select);
        }
        return;
    }

}

void UserWindow::on_btn_predict_clicked()
{
    static bool ischoose=false;
    int row=ui->tableWidget->currentRow();
    if(-1==row) return;
    if(!ischoose)
    {
        QMessageBox::information(this,"预测","请选择参考gdp个数");
        ui->spinBox->show();
        ischoose=true;
        return;
    }
    if(ischoose)
    {
        int n=ui->spinBox->value();
        //预测
        QList<double> x;
        QList<double> y;
        for(int i=0;i<n;++i)
        {
            x.push_back(i);
            y.push_back(cf.lc[row].gdp[i].toFloat());
        }
        LeastSquare ls(x,y);
        int num=ls.getY(-1);
        QMessageBox::information(this,"预测","预测"+cf.lc[row].cityname+"2022上半年GDP为"+QString::number(num)+"亿元");

        ui->spinBox->hide();
        ischoose=false;
        return;

    }

}


#include "dialoginputcity.h"
#include "ui_dialoginputcity.h"
#include <QFile>
#include <QMessageBox>

DialogInputCity::DialogInputCity(City& c,Type t,QWidget *parent) :
    QDialog(parent),c(c),copy(c),t(t),
    ui(new Ui::DialogInputCity)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    tableheader();
    ui->tableWidget->setRowCount(1);

    if(Type::update==t)
    {
        ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString(c.cityname)));
        for(int i=0;i<44;i++)
        {
            ui->tableWidget->setItem(0,i+1,new QTableWidgetItem(QString(c.gdp[i])));
        }

        connect(ui->tableWidget,&QTableWidget::cellChanged,this,&DialogInputCity::itemchanged);
    }
    setstyle();

}

DialogInputCity::~DialogInputCity()
{
    delete ui;
}

void DialogInputCity::tableheader()
{

    QStringList l;
    l<<"城市名";
    l<<"2021下";
    l<<"2021上";


    l<<"2020下";
    l<<"2020上";
    l<<"2019下";
    l<<"2019上";
    l<<"2018下";
    l<<"2018上";


    l<<"2017下";
    l<<"2017上";
    l<<"2016下";
    l<<"2016上";
    l<<"2015下";
    l<<"2015上";


    l<<"2014下";
    l<<"2014上";
    l<<"2013下";
    l<<"2013上";
    l<<"2012下";
    l<<"2012上";


    l<<"2011下";
    l<<"2011上";
    l<<"2010下";
    l<<"2010上";
    l<<"2009下";
    l<<"2009上";

    l<<"2008下";
    l<<"2008上";
    l<<"2007下";
    l<<"2007上";
    l<<"2006下";
    l<<"2006上";

    l<<"2005下";
    l<<"2005上";
    l<<"2004下";
    l<<"2004上";
    l<<"2003下";
    l<<"2003上";

    l<<"2002下";
    l<<"2002上";
    l<<"2001下";
    l<<"2001上";
    l<<"2000下";
    l<<"2000上";
    ui->tableWidget->setColumnCount(l.size());
    ui->tableWidget->setHorizontalHeaderLabels(l);

}

void DialogInputCity::setstyle()
{
    QString s=QCoreApplication::applicationDirPath()+"/Mycss/dialoginputcitystyle.css";
    QFile file(s);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        return;
    }
    QString m=file.readAll();
    this->setStyleSheet(m);
}

void DialogInputCity::on_btn_cancle_clicked()
{
    this->close();
}

void DialogInputCity::itemchanged(int row, int column)
{

    QString m=ui->tableWidget->item(row,column)->text();
    if(m.isEmpty())
    {
        QMessageBox::warning(this,"错误","数据不能为空!");
        return;
    }
    if(0==column)
    {
        copy.cityname=m;
        copy.ischanged=true;
        return;
    }
    for(auto& i:m)
    {
        if(i>'9'||i<'0')
        {
            QMessageBox::warning(this,"错误","输入数据错误!");
            return;
        }
    }


    if(column<=2)
    {
        copy.gdp[column-1]=m;
        copy.ischanged=true;
        return;
    }
    //需要更新统计值
    copy.gdp[column-1]=m;
    int num[3];
    int x=(column-3)/6*6+2;
    num[2]=copy.gdp[x].toInt()+copy.gdp[x+1].toInt();
    num[1]=copy.gdp[x+2].toInt()+copy.gdp[x+3].toInt();
    num[0]=copy.gdp[x+4].toInt()+copy.gdp[x+5].toInt();
    copy.p[(column-3)/6]=copy.calculate(num[0],num[1],num[2]);
    copy.ischanged=true;


}


void DialogInputCity::on_btn_save_clicked()
{
    if(Type::update==t)
    {
        if(copy.ischanged)
        {
            c=copy;
            c.ischanged=true;
        }
        this->close();
        return;
    }
    else
    {
        //获取信息
        int a;
        for(int column=44;column>=0;--column)
        {
            a=column-1;
            QString m=ui->tableWidget->item(0,column)->text();
            if(m.isEmpty())
            {
                QMessageBox::warning(this,"错误","数据不能为空!");
                return;
            }
            if(0==column)
            {
                c.cityname=m;
                continue;
            }
            for(auto& i:m)
            {
                if(i>'9'||i<'0')
                {
                    QMessageBox::warning(this,"错误","输入数据错误!");
                    return;
                }
            }

            c.gdp[a]=m;
            if((a-2)%6==0)
            {
                int num[3];
                num[0]=c.gdp[a+5].toInt()+c.gdp[a+4].toInt();
                num[1]=c.gdp[a+3].toInt()+c.gdp[a+2].toInt();
                num[2]=c.gdp[a+1].toInt()+c.gdp[a].toInt();
                c.p[(a-2)/6]=c.calculate(num[0],num[1],num[2]);

            }

        }
        c.ischanged=true;
        this->close();


    }

}


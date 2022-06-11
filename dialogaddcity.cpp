#include "dialogaddcity.h"
#include "ui_dialogaddcity.h"

#include <QFile>

DialogAddCity::DialogAddCity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddCity)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    setstyle();

}

DialogAddCity::~DialogAddCity()
{
    delete ui;
}

void DialogAddCity::setstyle()
{
    QString s=QCoreApplication::applicationDirPath()+"/Mycss/dialogaddcitystyle.css";
    QFile file(s);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        return;
    }
    QString m=file.readAll();
    this->setStyleSheet(m);
}


void DialogAddCity::on_btn_cancle_clicked()
{
    this->close();
}


void DialogAddCity::on_btn_input_clicked()
{
    this->close();
    emit input();

}


void DialogAddCity::on_btn_file_clicked()
{
    this->close();
    emit file();

}


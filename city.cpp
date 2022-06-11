#include "city.h"
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QCoreApplication>

City::City():ischanged(false)
{

}

Per3y City::calculate(int a1, int a2, int a3)
{
    qint32 b1=a1;
    qint32 b2=a2;
    qint32 b3=a3;
    qint32 ave=(b1+b2+b3)/3;
    qint32 v=((double)b3-(double)b1)/(double)b3*100;
    qint32 max=b1;
    qint32 min=b1;
    if(b2>max) max=b2;
    if(b2<min) min=b2;
    if(b3>max) max=b3;
    if(b3<min) min=b3;
    return Per3y(QString::number(ave),QString::number(max),QString::number(min),QString::number(v)+"%");
}

CityFile::CityFile(QString username):capacity(10)
{
    filepath=QCoreApplication::applicationDirPath()+QString("/data/%1.dat").arg(username);
    init();

}

void CityFile::print()
{
    QFile file(filepath);
    file.open(QIODeviceBase::WriteOnly);
    QTextStream fout(&file);
    QString city;
    for(int n=0;n<lc.size();++n)
    {
        int i=0,j=0;
        city=QString(CITYDATA).arg(lc[n].cityname)
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].p[j].min).arg(lc[n].p[j].max).arg(lc[n].p[j].ave).arg(lc[n].p[j++].v)
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].p[j].min).arg(lc[n].p[j].max).arg(lc[n].p[j].ave).arg(lc[n].p[j++].v)
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].p[j].min).arg(lc[n].p[j].max).arg(lc[n].p[j].ave).arg(lc[n].p[j++].v)
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].p[j].min).arg(lc[n].p[j].max).arg(lc[n].p[j].ave).arg(lc[n].p[j++].v)
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].p[j].min).arg(lc[n].p[j].max).arg(lc[n].p[j].ave).arg(lc[n].p[j++].v)
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].p[j].min).arg(lc[n].p[j].max).arg(lc[n].p[j].ave).arg(lc[n].p[j++].v)
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].p[j].min).arg(lc[n].p[j].max).arg(lc[n].p[j].ave).arg(lc[n].p[j++].v)
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++])
                .arg(lc[n].gdp[i++]).arg(lc[n].gdp[i++]);
        fout<<city<<"\n";
    }

    file.close();
}

void CityFile::init()
{
    lc.clear();
    QFile file(filepath);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        file.open(QIODeviceBase::WriteOnly);
        return;
    }
    QTextStream fin(&file);
    City c;
    QString content;
    int i=0;
    int j=0;
    while(!fin.atEnd())
    {
        fin>>content;
        if(content.isEmpty()) continue;
        content.replace(',',' ');
        QTextStream sin(&content);
        i=0;
        j=0;
        sin>>c.cityname;
        sin>>c.gdp[i++]>>c.gdp[i++];
        for(;j<7;)
        {
            sin>>c.p[j].min>>c.p[j].max>>c.p[j].ave>>c.p[j++].v;
            sin>>c.gdp[i++]>>c.gdp[i++];
            sin>>c.gdp[i++]>>c.gdp[i++];
            sin>>c.gdp[i++]>>c.gdp[i++];
        }
        lc.push_back(c);
    }
    file.close();

}



bool CityFile::addCity(City &c)
{
    if(isExist(c.cityname))
        return false;
    QFile file(filepath);
    if(!file.open(QIODeviceBase::WriteOnly|QIODeviceBase::Append))
    {
        return false;
    }
    QTextStream fout(&file);
    int i=0;
    int j=0;
    QString content=QString(CITYDATA).arg(c.cityname)
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.p[j].min).arg(c.p[j].max).arg(c.p[j].ave).arg(c.p[j++].v)
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.p[j].min).arg(c.p[j].max).arg(c.p[j].ave).arg(c.p[j++].v)
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.p[j].min).arg(c.p[j].max).arg(c.p[j].ave).arg(c.p[j++].v)
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.p[j].min).arg(c.p[j].max).arg(c.p[j].ave).arg(c.p[j++].v)
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.p[j].min).arg(c.p[j].max).arg(c.p[j].ave).arg(c.p[j++].v)
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.p[j].min).arg(c.p[j].max).arg(c.p[j].ave).arg(c.p[j++].v)
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.p[j].min).arg(c.p[j].max).arg(c.p[j].ave).arg(c.p[j++].v)
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++])
            .arg(c.gdp[i++]).arg(c.gdp[i++]);
    fout<<content<<"\n";
    lc.push_back(c);
    file.close();
    return true;

}

bool CityFile::udtCity(City& c)
{

    int num=0;
    for(auto& i:lc)
    {
        if(i.cityname==c.cityname)
            num++;
    }

    if(num>1)
    {
        init();
        return false;
    }
    print();
    init();
    return true;

}

bool CityFile::delCity(QString id)
{
    bool isdel=false;
    int i=0;
    for(;i<lc.size();++i)
    {
        if(lc[i].cityname==id)
        {
            lc.removeAt(i);
            isdel=true;
            break;
        }
    }
    if(!isdel) return false;
    print();
    return true;
}

bool CityFile::isExist(QString id)
{
    for(int i=0;i<lc.size();i++)
    {
        if(id==lc[i].cityname)
            return true;
    }
    return false;
}

bool CityFile::clearCity()
{
    QFile file(filepath);
    file.open(QIODeviceBase::WriteOnly);
    lc.clear();
    return true;
}

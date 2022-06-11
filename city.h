#ifndef CITY_H
#define CITY_H
#include<QString>
#include<QList>

//const QString CITYFILENAME="E:\\coding\\qt\\GDP_Information_System\\data\\city\\%1.dat";

const QString CITYDATA="%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24,%25,%26,%27,%28,%29,%30,%31,%32,%33,%34,%35,%36,%37,%38,%39,%40,%41,%42,%43,%44,%45,%46,%47,%48,%49,%50,%51,%52,%53,%54,%55,%56,%57,%58,%59,%60,%61,%62,%63,%64,%65,%66,%67,%68,%69,%70,%71,%72,%73,%74";

struct Per3y
{
    QString ave,max,min,v;
    Per3y(QString a1="",QString a2="",QString a3="",QString a4=""):
        ave(a1),max(a2),min(a3),v(a4){}
};





class City
{
public:
    QString cityname;
    QString gdp[44];
    Per3y p[7];
    bool ischanged;
public:
    City();
    //计算每三年的GDP
    Per3y calculate(int a1,int a2,int a3);
};

class CityFile
{
public:
    QList<City> lc;
    quint32 capacity;
    QString filepath;
private:
    void print();
    //获取所有数据
    void init();
public:
    CityFile(QString username);



    //GDP预测

    //添加城市
    bool addCity(City& c);

    //修改城市
    bool udtCity(City &c);

    //删除城市
    bool delCity(QString id);

    //城市是否已存在
    bool isExist(QString id);

    //清空城市
    bool clearCity();
};

#endif // CITY_H

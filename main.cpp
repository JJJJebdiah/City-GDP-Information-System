#include "signwindow.h"
#include"city.h"
#include "user.h"
#include <QApplication>
#include<QFile>
#include<QString>
#include<string>
#include<QTextStream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SignWindow w;
    w.show();
    City c;
    //CityFile cf("xiaoming123");
    for(auto& a:c.gdp)
        a="x";
    c.cityname="浙江";
    for(auto& b:c.p)
    {
        b.ave="x";
        b.max="b";
        b.min="c";
        b.v="d";
    }
//    cf.addCity(c);
//    c.cityname="徐州";
//    cf.addCity(c);
//    c.cityname="武汉";
//    cf.addCity(c);
    User u;
    u.m_username="debug";
    u.m_name="debug";
    u.m_password="bug";
    u.m_phone="debug";
    UserFile uf;
    //uf.addUser(u);
    //uf.delUser("xiaoming123");
    //uf.udtUser(u);

    return a.exec();
}

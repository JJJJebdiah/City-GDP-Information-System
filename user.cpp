#include "user.h"
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QCoreApplication>
User::User():m_username(""),m_password(""),m_name(""),m_phone(""),ischanged(false)
{

}

User::User(int ):ischanged(false)
{

}

User User::operator=(int)
{
    return *this;
}



UserFile::UserFile()
{
    filepath=QCoreApplication::applicationDirPath()+"/data/users.dat";
    QFile file(filepath);
    if(!file.open(QIODeviceBase::ReadOnly))//若不存在，新建一个，并且注册管理员
    {
        file.open(QIODeviceBase::WriteOnly);
        exit(0);
    }
    init();
}

void UserFile::init()
{
    lu.clear();
    QFile file(filepath);
    if(!file.open(QIODeviceBase::ReadOnly))
    {
        return;
    }
    QTextStream fin(&file);
    User u;
    QString content;
    while(!fin.atEnd())
    {
        fin>>content;
        if(content.isEmpty()) continue;
        content.replace(',',' ');
        QTextStream sin(&content);
        sin>>u.m_username>>u.m_password>>u.m_name>>u.m_phone;
        lu.push_back(u);
    }
    file.close();
}

void UserFile::print()
{
    QFile file(filepath);
    file.open(QIODeviceBase::WriteOnly);
    QTextStream fout(&file);
    QString user;
    for(int n=0;n<lu.size();++n)
    {
        user=QString(USERDATA).arg(lu[n].m_username)
                .arg(lu[n].m_password).arg(lu[n].m_name)
                .arg(lu[n].m_phone);
        fout<<user<<"\n";
    }
    file.close();
}

bool UserFile::addUser(User &u)
{
    if(isExist(u.m_username))
        return false;
    QFile file(filepath);
    if(!file.open(QIODeviceBase::WriteOnly|QIODeviceBase::Append))
    {
        return false;
    }
    QTextStream fout(&file);
    QString content=QString(USERDATA).arg(u.m_username).arg(u.m_password)
            .arg(u.m_name).arg(u.m_phone);
    fout<<content<<"\n";
    lu.push_back(u);
    file.close();
    return true;

}

bool UserFile::udtUser(User &u)
{
    int i;
    for(i=0;i<lu.size();++i)
    {
        if(lu[i].m_username==u.m_username)
        {
            lu[i]=u;
            break;
        }
    }
    if(i==lu.size()) return false;
    print();
    init();
    return true;
}



bool UserFile::delUser(QString username)
{
    int i;
    bool isdel=false;
    for(i=0;i<lu.size();++i)
    {
        if(lu[i].m_username==username)
        {
            lu.removeAt(i);
            isdel=true;
            break;
        }
    }
    if(!isdel) return false;
    print();
    return true;


}

bool UserFile::clearUser()
{
    QFile file(filepath);
    if(!file.open(QIODeviceBase::WriteOnly))
    {
        return false;
    }
    QTextStream fout(&file);
    QString content=QString(USERDATA).arg(lu[0].m_username).arg(lu[0].m_password)
            .arg(lu[0].m_name).arg(lu[0].m_phone);
    fout<<content<<"\n";
    while(lu.size()>1)
    {
        lu.pop_back();
    }
    return true;
}

bool UserFile::isExist(QString username)
{
    for(auto& i:lu)
    {
        if(i.m_username==username)
            return true;
    }
    return false;
}

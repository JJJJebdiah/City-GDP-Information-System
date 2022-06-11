#ifndef USER_H
#define USER_H

#include<QString>
#include<QList>

const QString USERFILENAME="E:\\coding\\qt\\GDP_Information_System\\data\\users.dat";
const QString USERDATA="%1,%2,%3,%4";
class User
{
public:
    QString m_username,m_password,m_name,m_phone;
    bool ischanged;
public:
    User();
    User(int i);
    User operator=(int);

};

class UserFile
{
public:
    QList<User> lu;
    QString filepath;

private:
    void init();
    void print();
public:
    UserFile();

    //添加用户
    bool addUser(User& u);

    //修改用户
    bool udtUser(User& u);

    //删除用户
    bool delUser(QString username);

    //清空所有用户
    bool clearUser();

    //查询用户名是否存在
    bool isExist(QString username);
};



#endif // USER_H

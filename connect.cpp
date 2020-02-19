#include "connect.h"
#include <QDebug>

Connect::Connect()
{
    Connect("localhost");
}

Connect::Connect(QString ip)
{
    dbName="android";
    userName="Android";
    password="Android";
    hostName=ip;

    dbconn=QSqlDatabase::addDatabase("QMYSQL");
    dbconn.setHostName(hostName);
    dbconn.setUserName(userName);
    dbconn.setPassword(password);
    dbconn.setDatabaseName(dbName);


    if(dbconn.open()){
        qDebug() << "open ok!" << endl;
        linksuccessflag=true;
    }else{
        qDebug() << "open no ok!" << endl;
        linksuccessflag=false;
    }
}

bool Connect::right(){
    return linksuccessflag;
}

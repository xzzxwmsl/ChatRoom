#ifndef CONNECT_H
#define CONNECT_H

#include <QSqlDatabase>
#include <QString>



class Connect
{
public:
    Connect();
    Connect(QString ip="");
    bool right();
private:
    QString hostName;
    QString dbName;
    QString userName;
    QString password;
    QSqlDatabase dbconn;
    bool linksuccessflag;

};

#endif // CONNECT_H

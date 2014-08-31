#ifndef CONNECTTODATABASE_H
#define CONNECTTODATABASE_H

#include <QObject>
#include <QSettings>
#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QTimer>
#include <QDebug>
class ConnectToDatabase : public QObject
{
    Q_OBJECT
public:
    ConnectToDatabase(QSettings &set);
    ConnectToDatabase(QString Host, QString _DatabaseName, QString _user, QString _pass, int _port);
    void SetHost(QString _Host);
    void SetDatabaseName(QString _DatabaseName);
    void SetUserName(QString _UserName);
    void SetPassword(QString _Password);
    void SetPort(int _Port);
    void Connect();
    bool isConnected();

private:
    QSqlDatabase db;
    QString HostName;
    QString DatabaseName;
    QString UserName;
    QString Password;
    int Port;
public slots:
   void Reconect();
};

#endif // CONNECTTODATABASE_H

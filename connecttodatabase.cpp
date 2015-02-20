#include "connecttodatabase.h"

ConnectToDatabase::ConnectToDatabase(QSettings &set)
{
}

ConnectToDatabase::ConnectToDatabase(QString _Host, QString _DatabaseName, QString _user, QString _pass, int _port)
{

    HostName = _Host;
    DatabaseName = _DatabaseName;
    UserName = _user;
    Password = _pass;
    Port =  _port;
//    QTimer *timer = new QTimer(this);
//    QObject::connect(timer, SIGNAL(timeout()),this,  SLOT(Reconect()));
//    timer->start(10000);
//    Reconect();
}

void ConnectToDatabase::SetHost(QString _Host)
{
    HostName = _Host;
}

void ConnectToDatabase::SetDatabaseName(QString _DatabaseName)
{
    DatabaseName = _DatabaseName;
}

void ConnectToDatabase::SetUserName(QString _UserName)
{
    UserName = _UserName;

}

void ConnectToDatabase::SetPassword(QString _Password)
{
    Password = _Password;
}

void ConnectToDatabase::SetPort(int _Port)
{
    Port = _Port;
}

void ConnectToDatabase::Connect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setConnectOptions("MYSQL_OPT_RECONNECT=1;CLIENT_INTERACTIVE=1;");
    db.setHostName(HostName);
    db.setDatabaseName(DatabaseName);
    db.setUserName(UserName);
    db.setPort(Port);

    db.setPassword(Password);
    if (!db.open())
    {
        //        qDebug() << "Error: " << db.lastError();
        QMessageBox msgBox;
        msgBox.setText("Помилка!");
        msgBox.setInformativeText(db.lastError().text());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
    }


}

bool ConnectToDatabase::isConnected()
{
    return db.open()?true:false;
}

void ConnectToDatabase::Reconect()
{
    if(db.isOpen()){

        qDebug() <<"was open";
    }else{
        Connect();
        qDebug()<<"isOpen!!!";
    }
}

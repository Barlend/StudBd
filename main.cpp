#include "mainwindow.h"
#include "loginform.h"
#include "registerform.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSettings>
#include <QTextCodec>




static bool connect_to_database(QString Host, QString DatabaseeName, QString user, QString pass, int port) //подключаем баззу данных
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(Host);
    db.setDatabaseName(DatabaseeName);
    db.setUserName(user);
    db.setPort(port);
    db.setPassword(pass);
    if (!db.open())
    {

        qDebug() << "Error: " << db.lastError();
        return false;
    }
    qDebug() << "OK!!!!!";
    return true;

}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setOrganizationName("Belfegor");
    a.setOrganizationDomain("qtmpp.tk");
    a.setApplicationName("StudBd");
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QSettings *set= new QSettings(qApp->applicationDirPath()+"/config.ini", QSettings::IniFormat);
    set->setIniCodec(codec);
    set->beginGroup("database");
    qDebug()<<set->fileName();
    connect_to_database(set->value("HostName").toString(), set->value("DatabaseName").toString(),set->value("UserName").toString(), set->value("Password").toString(), set->value("Port").toInt() );
    LoginForm w;
    w.show();

    return a.exec();
}

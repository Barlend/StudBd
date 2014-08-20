#include "mainwindow.h"
#include "loginform.h"
#include "registerform.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
static bool connect_to_database() //подключаем баззу данных
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("StudBd1");
    db.setUserName("root");
    db.setPassword("");
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
        connect_to_database();
    QApplication a(argc, argv);
    LoginForm w;
    w.show();

    return a.exec();
}

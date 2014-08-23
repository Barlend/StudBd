#include "connecttodatabase.h"
#include "ui_connecttodatabase.h"
#include <QSqlError>
ConnectToDatabase::ConnectToDatabase(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectToDatabase)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Connect()));
}

ConnectToDatabase::~ConnectToDatabase()
{
    delete ui;
}

void ConnectToDatabase::Connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ui->hostnamelineEdit->text());
    db.setDatabaseName(ui->databasenamelineEdit->text());
    db.setUserName(ui->loginlineEdit->text());
    db.setPassword(ui->passwordlineEdit->text());
    if(ui->portlineEdit->text()!=""){db.setPort(ui->portlineEdit->text().toInt());}

    if (!db.open())
    {
        QMessageBox::critical(this, "Помилка!!!", db.lastError().text(),QMessageBox::Ok);
        //        qDebug() << "Error: " << db.lastError();

    }else{

        QMessageBox::critical(this, "Все прошло успішно!", "Ви успішно підєдналися до бази",QMessageBox::Ok);
    }
}

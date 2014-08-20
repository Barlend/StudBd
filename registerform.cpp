#include "registerform.h"
#include "ui_registerform.h"

RegisterForm::RegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
    setWindowTitle("Форма реєстрації");

}

RegisterForm::~RegisterForm()
{
    delete ui;
}

void RegisterForm::on_RegisterButton_clicked()
{
    int ID;
    QSqlQuery queryforid("SELECT id FROM StudBd1.Users");
    while (queryforid.next()) {
        QString id = queryforid.value(0).toString();
        ID = id.toInt();
    }

    if(ui->firstPassword->text() == ui->secondPassword->text()){
        QSqlQuery query;
        query.prepare("insert into StudBd1.Users (id, login, password, accesslevel) "
                      "VALUES (?, ?, ?, ?)");
        ID++;
        query.addBindValue(ID);
        query.addBindValue(ui->LoginlineEdit->text());
        query.addBindValue(ui->firstPassword->text());
        query.addBindValue("reg");
        query.exec();

        ui->StatusLabel->setText("Користувача "+ ui->LoginlineEdit->text() + " успішно зареєстровано");
        ui->LoginlineEdit->clear();
        ui->firstPassword->clear();
        ui->secondPassword->clear();
    }
    else{
        ui->StatusLabel->setText("Паролі не співпадають");
    }
}

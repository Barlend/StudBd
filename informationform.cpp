#include "informationform.h"
#include "ui_informationform.h"

InformationForm::InformationForm(QString name, QString firstname, QString lastname, QString lvl, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InformationForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Студент "+name + " " + firstname + " " + lastname);
//    ui->label->setText(lvl);
    QSqlQuery firstquery;
    firstquery.prepare("select * from StudBd1.Students where name = ? and firstname = ? and lastname = ?");
            firstquery.bindValue(0, name);
            firstquery.bindValue(1, firstname);
            firstquery.bindValue(2, lastname);
            firstquery.exec();
            while(firstquery.next()){
                QString Name = firstquery.value(1).toString();
                ui->namelineedit->setText(Name);
                ///////////
                QString FirstName = firstquery.value(2).toString();
                ui->firstnamelineedit->setText(FirstName);
                /////////
                QString LastName = firstquery.value(3).toString();
                ui->lastnamelineedit->setText(LastName);
                //////////////
                QString NumberOfGroup = firstquery.value(4).toString();
                ui->numberofgroup->setText(NumberOfGroup);
                ///////////////
                QString Telephone = firstquery.value(9).toString();
                ui->studenttelephonelineedit->setText(Telephone);
            }
}

InformationForm::~InformationForm()
{
    delete ui;
}

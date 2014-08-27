#include "informationform.h"
#include "ui_informationform.h"

InformationForm::InformationForm(QString name, QString firstname, QString lastname, QString lvl, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InformationForm)
{
    ui->setupUi(this);
    QString fac, dep;
    this->setWindowTitle("Студент "+name + " " + firstname + " " + lastname);
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
        QString DateOfBirth = firstquery.value(8).toString();
        ui->studentdateofbirdthlineedit->setText(DateOfBirth);
        QString Date_Of_Entry = firstquery.value(10).toString();
        ui->Date_Of_Entry->setText(Date_Of_Entry);
        ///////
        QString End_Date = firstquery.value(11).toString();
        ui->End_Date->setText(End_Date);

        idOfFaculties = firstquery.value(6).toInt();
        idOfDepartment = firstquery.value(5).toInt();
    }

    qDebug() <<" id of department" <<idOfDepartment;
    qDebug() <<" id of idOfFaculties" <<idOfFaculties;

    //select f.NameOfFaculties, d.nameOfDepartment from Faculties f, Departments d where f.id =1 and d.id =1
    QSqlQuery seconquery;
    seconquery.prepare("select d.nameOfDepartment, f.NameOfFaculties from Departments d, Faculties f where d.id = ? and f.id = ?");
    seconquery.addBindValue(idOfDepartment);
    seconquery.addBindValue(idOfFaculties);
    qDebug() <<" id of department" <<idOfDepartment;
    qDebug() <<" id of idOfFaculties" <<idOfFaculties;
    seconquery.exec();
    while(seconquery.next()){
        qDebug () <<"-----------------------";
        qDebug() <<" id of department" <<idOfDepartment;
        qDebug() <<" id of idOfFaculties" <<idOfFaculties;
        fac = seconquery.value(1).toString();
        qDebug()<<"fac = " << fac;
        dep  = seconquery.value(0).toString();
        qDebug() << "dep = " << dep;
    }
    ui->facultieslineedit->setText(fac);
    ui->departmentfileedit->setText(dep);
}

InformationForm::~InformationForm()
{
    delete ui;
}

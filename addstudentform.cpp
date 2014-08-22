#include "addstudentform.h"
#include "ui_addstudentform.h"

AddStudentForm::AddStudentForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddStudentForm)
{
    ui->setupUi(this);


    //////////////////////////
    QSqlQuery queryForFacultiesBox1("SELECT NameOfFaculties  FROM StudBd1.Faculties");

    while(queryForFacultiesBox1.next()){
        tempforfacultites.push_back(queryForFacultiesBox1.value(0).toString());
    }
    ui->FacultiescomboBox->addItems(tempforfacultites);

    ///////////////////






}

AddStudentForm::~AddStudentForm()
{
    delete ui;
}



void AddStudentForm::on_AddSudentButton_clicked()
{
    QSqlQuery addStudentQuery;
    addStudentQuery.prepare("insert into StudBd1.Students (Name, FirstName, LastName, NumberOfGroup, IdOfFaculties, IdOfDepartment, Telephone, MotherName,FatherName, ParentsPhone)"
                            "values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    addStudentQuery.addBindValue(ui->nameLabel->text());
    addStudentQuery.addBindValue(ui->firstName->text());
    addStudentQuery.addBindValue(ui->lasNameLineEdit->text());
    addStudentQuery.addBindValue(ui->GroupNumderLineEdit->text());
    addStudentQuery.addBindValue(ui->FacultiescomboBox->currentIndex() + 1);
    addStudentQuery.addBindValue(ui->DepartmentscomboBox->currentIndex() + 1);
    addStudentQuery.addBindValue(ui->TelephoneOfStudent->text());
    addStudentQuery.addBindValue(ui->MotherNameLineEdit->text());
    addStudentQuery.addBindValue(ui->FatherNameLineEdit->text());
    addStudentQuery.addBindValue(ui->ParentsTelefonNumber->text());
    addStudentQuery.exec();
    if(addStudentQuery.isValid()){
        qDebug () <<"Yes";
    }/*else{
//        qDebug()<< addStudentQuery.lastError();
    }*/
}

void AddStudentForm::on_FacultiescomboBox_currentIndexChanged(int index)
{
    ui->DepartmentscomboBox->clear();
    QStringList temp;
    QSqlQuery queryForDepartmentcombobox;
    queryForDepartmentcombobox.prepare("SELECT f.id, d.nameOfDepartment, d.IdForFaculties FROM Faculties f, Departments d WHERE f.id = d.IdForFaculties AND f.id = ?");
    queryForDepartmentcombobox.bindValue(0, index + 1);
    queryForDepartmentcombobox.exec();
    while(queryForDepartmentcombobox.next()){
        QString department = queryForDepartmentcombobox.value(1).toString();
        temp.push_back(department);
    }
    ui->DepartmentscomboBox->addItems(temp);
}










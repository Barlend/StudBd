#include "addstudentform.h"
#include "ui_addstudentform.h"

AddStudentForm::AddStudentForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddStudentForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Додавання нового студента");

    //////////////////////////
    QSqlQuery queryForFacultiesBox1("SELECT NameOfFaculties  FROM StudBd1.Faculties");

    while(queryForFacultiesBox1.next()){
        tempforfacultites.push_back(queryForFacultiesBox1.value(0).toString());
    }
    ui->FacultiescomboBox->addItems(tempforfacultites);
}

AddStudentForm::~AddStudentForm()
{
    delete ui;
}



void AddStudentForm::on_AddSudentButton_clicked()
{
    int Id_Of_Department;
    //////////////////
    /// \brief Department_and_fac_index
    /// вибирається айдішник кафедри для запису
    //////////////////
    QSqlQuery Department_and_fac_index;
    Department_and_fac_index.prepare("select id from Departments d where nameOfDepartment = ?");
    Department_and_fac_index.bindValue(0, ui->DepartmentscomboBox->currentText());
    Department_and_fac_index.exec();
    while(Department_and_fac_index.next()){
        Id_Of_Department = Department_and_fac_index.value(0).toInt();
    }


    QSqlQuery addStudentQuery;
    addStudentQuery.prepare("insert into StudBd1.Students (Name, FirstName, LastName, NumberOfGroup, IdOfFaculties, IdOfDepartment, Telephone, MotherName, FatherName, ParentsPhone, DateOfBirth, DateOfEntry, EndDate)"
                            "values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    addStudentQuery.addBindValue(ui->nameLabel->text());
    addStudentQuery.addBindValue(ui->firstName->text());
    addStudentQuery.addBindValue(ui->lasNameLineEdit->text());
    addStudentQuery.addBindValue(ui->GroupNumderLineEdit->text());
    addStudentQuery.addBindValue(ui->FacultiescomboBox->currentIndex() + 1);
    addStudentQuery.addBindValue(Id_Of_Department);
    addStudentQuery.addBindValue(ui->TelephoneOfStudent->text());
    addStudentQuery.addBindValue(ui->MotherNameLineEdit->text());
    addStudentQuery.addBindValue(ui->FatherNameLineEdit->text());
    addStudentQuery.addBindValue(ui->ParentsTelefonNumber->text());
    ////////////
    /// \brief date_Of_Birthday
    /// дата народження
    /////////////
    QString date_Of_Birthday = ui->Birth_Day_date->date().toString("dd.MM.yyyy");
    addStudentQuery.addBindValue(date_Of_Birthday);
    /////////////////////////
    /// \brief Date_Of_Entry
    /// дата вступу та дата закінчення +4 роки
    /////////////////////////
    QString Date_Of_Entry = ui->Date_OfEntry->date().toString("dd.MM.yyyy");
    addStudentQuery.addBindValue(Date_Of_Entry);
    QDate dayEnteredTemp = ui->Date_OfEntry->date();
    QDate t = dayEnteredTemp.addYears(ui->Years_of_Schooling->value());
    ui->label_12->setText(t.toString("dd.MM.yyyy"));
    QString dayEnteredTemp_STring = t.toString("dd.MM.yyyy");
    addStudentQuery.addBindValue(dayEnteredTemp_STring);
    addStudentQuery.exec();
    ui->statusbar->showMessage("Студента  ->   "+ ui->firstName->text()+ " " + ui->nameLabel->text() +" " + ui->lasNameLineEdit->text() +" додано до бази", 5000);
    ui->nameLabel->clear();
    ui->firstName->clear();
    ui->lasNameLineEdit->clear();
    ui->GroupNumderLineEdit->clear();
    //        ui->FacultiescomboBox->clear();
    ui->TelephoneOfStudent->clear();
    ui->MotherNameLineEdit->clear();
    ui->FatherNameLineEdit->clear();
    ui->ParentsTelefonNumber->clear();
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










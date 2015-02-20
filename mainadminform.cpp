#include "mainadminform.h"
#include "ui_mainadminform.h"

mainAdminForm::mainAdminForm(QStringList data, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainAdminForm)
{
    ui->setupUi(this);
    setWindowTitle("Admin mode");
    QSqlQuery queryForFacultiesBox1("SELECT NameOfFaculties  FROM StudBd1.Faculties");

    while(queryForFacultiesBox1.next()){
        tempforfacultites.push_back(queryForFacultiesBox1.value(0).toString());
    }
    ui->FacultiescomboBox->addItems(tempforfacultites);
    ui->FacultiescomboBox_add->addItems(tempforfacultites);
    ui->Direction_comboBox->addItems(tempforfacultites);


    users();
    FacultiesViev();


}

mainAdminForm::~mainAdminForm()
{
    delete modelusers;
    delete ui;
}

void mainAdminForm::users()
{

    modelusers = new QSqlTableModel;

    modelusers->setTable("Users");
    modelusers->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelusers->select();
    ui->tableView_users->setModel(modelusers);
    ui->tableView_users->resizeRowsToContents();
    ui->tableView_users->resizeColumnsToContents();
    ui->tableView_users->show();
}

int mainAdminForm::GetId(QString name)
{
    int id;
    QSqlQuery GetIdDep;
    GetIdDep.prepare("SELECT f.id FROM Faculties f where f.NameOfFaculties = ?");
    GetIdDep.addBindValue(name);
    GetIdDep.exec();
    while (GetIdDep.next()){
        id = GetIdDep.value(0).toInt();
    }
    return id;
}

void mainAdminForm::FacultiesViev()
{
    facultiesmodel = new QSqlTableModel;
    facultiesmodel->setTable("Faculties");
    facultiesmodel->setEditStrategy(QSqlTableModel::OnFieldChange);
    facultiesmodel->select();
    ui->Faculties_->setModel(modelusers);
    ui->Faculties_->resizeRowsToContents();
    ui->Faculties_->resizeColumnsToContents();
    ui->Faculties_->show();

}

void mainAdminForm::on_FacultiescomboBox_currentIndexChanged(int index)
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

void mainAdminForm::on_DepartmentscomboBox_currentIndexChanged(int index)
{
    //    int Id_Of_Department;
    //    //////////////////
    //    /// \brief Department_and_fac_index
    //    /// вибирається айдішник спеціальності для запису
    //    //////////////////
    //    QSqlQuery Department_and_fac_index;
    //    Department_and_fac_index.prepare("SELECT e.StartDate, e.EndDate, e.idOfFaculties, e.idOfDepartment FROM Exams e, Departments d WHERE e.id = d.id AND d.nameOfDepartment = ?");
    //    Department_and_fac_index.bindValue(0, ui->DepartmentscomboBox->currentText());
    //    Department_and_fac_index.exec();
    //    while(Department_and_fac_index.next()){
    //        Id_Of_Department = Department_and_fac_index.value(0).toInt();
    //    }
    //QSqlQuery::value: not positioned on a valid record
    //    QSqlQuery GetIdDep;
    //    GetIdDep.prepare("SELECT f.id FROM Faculties f where f.NameOfFaculties = ?");
    //    GetIdDep.addBindValue(ui->FacultiescomboBox->currentText());
    //    GetIdDep.exec();
    //    int id = GetIdDep.value(0).toInt();




    QSqlTableModel *model = new QSqlTableModel;

    //    QSqlQueryModel *model = new QSqlQueryModel;
    //    model->
    //    EditableSqlModel *model = new EditableSqlModel(ui->FacultiescomboBox->currentText());//my
    //    model->flags(Qt::ItemIsEditable);
    //    QString temp1 = "SELECT e.StartDate, e.EndDate, e.idOfFaculties, e.idOfDepartment FROM Exams e, Departments d WHERE e.id = d.id AND d.nameOfDepartment = "+ui->DepartmentscomboBox->currentText();
    //    QSqlQuery q("SELECT e.StartDate, e.EndDate, e.idOfFaculties, e.idOfDepartment FROM Exams e, Departments d WHERE e.id = d.id AND d.nameOfDepartment = '"+ui->DepartmentscomboBox->currentText()+"'");
    QSqlQuery query;
    query.prepare("SELECT f.id FROM Faculties f where f.NameOfFaculties = '"+ui->FacultiescomboBox->currentText()+"'");

    //    query.prepare("SELECT e.StartDate, e.EndDate FROM Exams e, Departments d WHERE e.id = d.id AND d.nameOfDepartment = ?");
    query.addBindValue(ui->DepartmentscomboBox->currentText());
    query.exec();
    //    model->setQuery(query);
    model->setTable("Exams");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();

    QSqlQuery QueryForids;
    int fId, dId;
    QueryForids.prepare("SELECT f.id, d.id FROM Departments d, Faculties f WHERE d.nameOfDepartment = ? AND f.NameOfFaculties = ?");
    QueryForids.addBindValue(ui->DepartmentscomboBox->currentText());
    QueryForids.addBindValue(ui->FacultiescomboBox->currentText());
    QueryForids.exec();
    while(QueryForids.next()){
        ui->facid->setText("id "+QueryForids.value(0).toString());
        ui->depid->setText("id "+QueryForids.value(1).toString());
        //        dId = QueryForids.value(1).toInt();
    }
}

void mainAdminForm::on_FacultiescomboBox_add_currentIndexChanged(int index)
{
    ui->DepartmentscomboBox_add->clear();
    QStringList temp;
    QSqlQuery queryForDepartmentcombobox_add;
    queryForDepartmentcombobox_add.prepare("SELECT f.id, d.nameOfDepartment, d.IdForFaculties FROM Faculties f, Departments d WHERE f.id = d.IdForFaculties AND f.id = ?");
    queryForDepartmentcombobox_add.bindValue(0, index + 1);
    queryForDepartmentcombobox_add.exec();
    while(queryForDepartmentcombobox_add.next()){
        QString department = queryForDepartmentcombobox_add.value(1).toString();
        temp.push_back(department);
    }
    ui->DepartmentscomboBox_add->addItems(temp);
}

void mainAdminForm::on_pushButton_clicked()
{
    QSqlQuery QueryForids;
    int fId, dId;
    QueryForids.prepare("SELECT f.id, d.id FROM Departments d, Faculties f WHERE d.nameOfDepartment = ? AND f.NameOfFaculties = ?");
    QueryForids.addBindValue(ui->DepartmentscomboBox_add->currentText());
    QueryForids.addBindValue(ui->FacultiescomboBox_add->currentText());
    QueryForids.exec();
    while(QueryForids.next()){
        fId = QueryForids.value(0).toInt();
        dId = QueryForids.value(1).toInt();
    }
    qDebug() <<"fId = " << fId << " dId = " << dId;
    qDebug() <<"datetext " << ui->dateEdit->text();
    QSqlQuery addQuery;
    addQuery.prepare("INSERT INTO Exams (StartDate, EndDate, idOfFaculties, idOfDepartment) VALUES (?, ?, ?, ?)");
    addQuery.addBindValue(ui->dateEdit->text());
    addQuery.addBindValue(ui->dateEdit_2->text());
    addQuery.addBindValue(fId);
    addQuery.addBindValue(dId);
    if(addQuery.exec());

    //        qDebug() << addQuery.exec();
    //    }

}



void mainAdminForm::on_addDirectionButton_clicked()
{


    QSqlQuery QueryForAdd;
    QueryForAdd.prepare("insert into Departments(nameOfDepartment, IdForFaculties) values(:nameOfDepartment, :IdForFaculties)");
    QueryForAdd.bindValue(":nameOfDepartment", ui->NameDirection->text());
    QueryForAdd.bindValue(":IdForFaculties", GetId(ui->Direction_comboBox->currentText()));

    QMessageBox msgBox;
    msgBox.setText("Додати?");
    msgBox.setInformativeText("Ви впевнені що бажаєте додати?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
        // Save was clicked
        QueryForAdd.exec();
        //            this->showMessage("Вітаємо! Зміни збережено!", 5000);
        break;

    default:
        // should never be reached
        //            this->showMessage("Зміни до облікового запису не внесені!", 5000);
        break;
    }

}



void mainAdminForm::on_AddFacultiesButton_clicked()
{

    QSqlQuery QueryForAddFaculties;
    QueryForAddFaculties.prepare("insert into Faculties(NameOfFaculties, Adress, Tel) values(:NameOfFaculties, :Adress, :Tel)");
    QueryForAddFaculties.bindValue(":NameOfFaculties", ui->NameOfFacultieslineEdit->text());
    QueryForAddFaculties.bindValue(":Adress",ui->AdressOfFaculties->text() );
    QueryForAddFaculties.bindValue(":Tel", ui->TelephonLFaculties->text());
    QMessageBox msgBox;
    msgBox.setText("Додати?");
    msgBox.setInformativeText("Ви впевнені що бажаєте додати?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Save:
        // Save was clicked
        if(ui->NameOfFacultieslineEdit->text()!="" && ui->AdressOfFaculties->text()!="" && ui->TelephonLFaculties->text()!="")
            QueryForAddFaculties.exec();
        break;

    default:
        break;
    }

}

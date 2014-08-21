#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlTableModel;
    model->setTable("Students");

    model->select();
    model->setHeaderData(0, Qt::Horizontal, "Прізвище");
    model->setHeaderData(1, Qt::Horizontal, "Ім'я");
    model->setHeaderData(2, Qt::Horizontal, "По-батькові");
    model->setHeaderData(3, Qt::Horizontal, "Номер групи");
    tableView = new QTableView;
    model->removeColumn(0);

    ui->tableView->hideColumn(0);
    ui->tableView->setModel(model);
    //    tableView->setEnabled(false);

    ui->tableView->show();



    //    ui->tableWidget->setRowCount(5);
    //    ui->tableWidget->setColumnCount(5);
    ///////////////////////////////////////////////////////////////////////////
    /// \brief queryForFacultiesBox1
    /// додавання списку факультетів до комбобоксу вибору
    /// зі збереженням у tempforfacultites
    //////////////////////////////////////////////////////////////////////////
    QSqlQuery queryForFacultiesBox1("SELECT NameOfFaculties  FROM StudBd1.Faculties");

    while(queryForFacultiesBox1.next()){

        //        tempforfacultites <<queryForFacultiesBox1.value(0).toString() ;
        //        ui->FacultiescomboBox->addItem(queryForFacultiesBox.value(0).toString(), queryForFacultiesBox.value(1).toString());
        tempforfacultites.push_back(queryForFacultiesBox1.value(0).toString());
    }


    ///////////////////////////////////////////////////////////////////////////



    ///////////////////////////////////////////////////////////////////////////
    /// \brief queryForFacultiesBox
    /// додавання до спискау факультетів/інститутів - інститутів
    /// зі збереженням у tempforinstitutes
    /// FTH must be fix!!!!!!!!!!!
    //////////////////////////////////////////////////////////////////////////

    //    QSqlQuery queryForFacultiesBox("SELECT NameOfInstitut FROM  StudBd1.Institutes");
    //    while(queryForFacultiesBox.next()){

    //        //        tempforinstitutes << queryForFacultiesBox.value(0).toString();
    //        tempforinstitutes.push_back(queryForFacultiesBox.value(0).toString());
    //        //        ui->FacultiescomboBox->addItem(queryForFacultiesBox.value(0).toString(), queryForFacultiesBox.value(1).toString());

    //    }
    ////////////////////////////
    ///пул у комбобокс
    ////////////////////////////
    ui->FacultiescomboBox->addItems(tempforfacultites);
    //    ui->FacultiescomboBox->addItems(tempforinstitutes);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recieveaccesslevl(QStringList lvl)
{
    int ID;

    AcountAccessLevl = lvl.at(1);

    QSqlQuery queryforid("SELECT id FROM StudBd1.LigingActions");
    while (queryforid.next()) {
        QString id = queryforid.value(0).toString();
        ID = id.toInt();
    }
    //////////////////////////////////////////////
    // дата цієї машни для логу
    /////////////////////////
    data = QDateTime::currentDateTime();
    QString Tdata = data.toString("hh:mm:ss-dd.MM.yyyy");
    ///////////////////////////////////
    /// \brief query
    /// логування у вигляді /логін/дата входу
    ///
    QSqlQuery query;
    query.prepare("insert into StudBd1.LigingActions (id, login, accesslevl, datatime) "
                  "VALUES (?, ?, ?, ?)");
    ID++;
    query.addBindValue(ID);
    query.addBindValue(lvl.at(0));
    query.addBindValue(lvl.at(1));
    query.addBindValue(Tdata);
    query.exec();

    ui->label->setText(AcountAccessLevl);
}

void MainWindow::FacultitesQuery()
{

}

void MainWindow::on_FacultiescomboBox_currentTextChanged(const QString &arg1)
{
    ui->statusBar->showMessage("Ви обрали "+ui->FacultiescomboBox->currentText(), 7000);

}





void MainWindow::on_FacultiescomboBox_currentIndexChanged(const QString &arg1)
{
    //    QStringList temp;
    ////    QSqlQuery queryForDepartmentcombobox("SELECT StudBd1.Departments.nameOfDepartment IF(StudBd1.Faculties.id = StudBd1.Departments.IdForFaculties , StudBd1.Departments.nameOfDepartment ,SELECT  )");
    ////    queryForDepartmentcombobox
    ////     QSqlQuery queryForDepartmentcombobox("SELECT IF(StudBd1.Faculties.id = StudBd1.Departments.IdForFaculties, SELECT StudBd1.Department.nameOfDepartment FROM StudBd1.Departments,0 )");
    //     QSqlQuery queryForDepartmentcombobox("SELECT StudBd1.Departments.nameOfDepatment FROM StudBd1.Departments WHERE " + arg1 +"= StudBd1.Faculties.NameOfFaculties AND StudBd1.Departments.IdForFaculties = StudBd1.Faculties.id");

    //    while(queryForDepartmentcombobox.next()){
    //        QString department = queryForDepartmentcombobox.value(0).toString();
    //        temp.append(department);
    //    }
    //    ui->DepartmentscomboBox->addItems(temp);

    //    QString temp1="SELECT StudBd1.Departments.nameOfDepatment FROM StudBd1.Departments WHERE StudBd1.Faculties.NameOfFaculties = " + arg1 ;

}


void MainWindow::on_FacultiescomboBox_currentIndexChanged(int index)
{

    ui->DepartmentscomboBox->clear();
    QStringList temp;
    //    QString r = ui->FacultiescomboBox->currentText();
    //    QString t = "SELECT f.id, d.nameOfDepartment, d.IdForFaculties FROM Faculties f, Departments d WHERE f.id = d.IdForFaculties AND f.id = '" +QString::number(index+1)+ "'";

    QSqlQuery queryForDepartmentcombobox;
    queryForDepartmentcombobox.prepare("SELECT f.id, d.nameOfDepartment, d.IdForFaculties FROM Faculties f, Departments d WHERE f.id = d.IdForFaculties AND f.id = ?");
    queryForDepartmentcombobox.bindValue(0, index+1);
    queryForDepartmentcombobox.exec();
    while(queryForDepartmentcombobox.next()){
        QString department = queryForDepartmentcombobox.value(1).toString();
        temp.push_back(department);
    }
    ui->DepartmentscomboBox->addItems(temp);




    //    ui->DepartmentscomboBox->clear();
    //    QStringList temp;
    //    QString r = ui->FacultiescomboBox->currentText();
    //    QString t = "SELECT f.id, d.nameOfDepartment, d.IdForFaculties FROM Faculties f, Departments d WHERE f.id = d.IdForFaculties AND f.id = '" +QString::number(index+1)+ "'";

    //   QSqlQuery queryForDepartmentcombobox(t);

    //  while(queryForDepartmentcombobox.next()){
    //      QString department = queryForDepartmentcombobox.value(1).toString();
    //      temp.push_back(department);
    //  }
    //  ui->DepartmentscomboBox->addItems(temp);


    ////////////////////////////////////////

    //  QStringList temp1;
    ////  QString r = ui->FacultiescomboBox->currentText();
    //  QString t = "SELECT f.id, d.nameOfDepartment, d.IdForFaculties FROM Faculties f, Departments d WHERE f.id = d.IdForFaculties AND f.id = '" +QString::number(index+1)+ "'";

    // QSqlQuery queryForDepartmentcombobox1(t);

    //while(queryForDepartmentcombobox1.next()){
    //    QString department = queryForDepartmentcombobox1.value(1).toString();
    //    temp1.push_back(department);
    //}
    //ui->DepartmentscomboBox->addItems(temp1);


}

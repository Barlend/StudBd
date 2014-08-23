#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("База студентів");
    AddstudForm = new AddStudentForm;
    model = new QSqlTableModel;
    model->setTable("Students");
    model->setHeaderData(0, Qt::Horizontal, "Прізвище");
    model->setHeaderData(1, Qt::Horizontal, "Ім'я");
    model->setHeaderData(2, Qt::Horizontal, "По-батькові");
    model->setHeaderData(3, Qt::Horizontal, "Номер групи");
    model->select();

    tableView = new QTableView;
    model->removeColumn(0);

    ui->tableView->hideColumn(0);
    ui->tableView->setModel(model);
    //    tableView->setEnabled(false);

    ui->tableView->show();
    qm = new QSqlQueryModel;

    qm->setHeaderData(0, Qt::Horizontal, "Прізвище");
    qm->setHeaderData(1, Qt::Horizontal, "Ім'я");
    qm->setHeaderData(2, Qt::Horizontal, "По-батькові");

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
    delete AddstudForm;
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

    //////////////////////////////////




}

void MainWindow::on_pushButton_clicked()
{
    AddstudForm->show();
}

void MainWindow::on_FacultiescomboBox_activated(int index)
{
    QSqlQuery QueryForFaculties("select s.Name, s.FirstName, s.LastName from StudBd1.Students s, StudBd1.Faculties f where f.id = s.IdOfFaculties and f.id = '" + QString::number(ui->FacultiescomboBox->currentIndex() + 1) +"'");
    qDebug() << ui->FacultiescomboBox->currentIndex()+1 <<" - is index";

    qm->setHeaderData(0, Qt::Horizontal, "Прізвище");
    qm->setHeaderData(1, Qt::Horizontal, "Ім'я");
    qm->setHeaderData(2, Qt::Horizontal, "По-батькові");
    qm->setQuery(QueryForFaculties);

    //    model->setQuery(QSqlQuery(QueryForFaculties));
    ui->tableView->setModel(qm);


}

void MainWindow::on_DepartmentscomboBox_currentIndexChanged(int index)
{
    QSqlQuery QueryForFaculties("select s.Name, s.FirstName, s.LastName from StudBd1.Students s, StudBd1.Departments d, StudBd1.Faculties f where s.IdOfDepartment = d.id and s.IdOfFaculties = f.id and s.IdOfDepartment = '"+QString::number(ui->DepartmentscomboBox->currentIndex()+1) + "' and s.IdOfFaculties  = '"+QString::number(ui->FacultiescomboBox->currentIndex()+1) +"'");

    //    QueryForFaculties("");
    //    QueryForFaculties.bindValue(0, ui->FacultiescomboBox->currentIndex() +2);
    //    QueryForFaculties.exec();
    qDebug() <<"ui->FacultiescomboBox->currentIndex()+1 ----" <<ui->FacultiescomboBox->currentIndex()+1 <<" - is index";


    qm->setQuery(QueryForFaculties);

    //    model->setQuery(QSqlQuery(QueryForFaculties));
    ui->tableView->setModel(qm);



    //        select s.Name, s.FirstName, s.LastName from StudBd1.Students s, StudBd1.Departments d, StudBd1.Faculties f where f.id = 1 	and d.IdForFaculties = f.id	and d.IdForFaculties =
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug()<< index;
}

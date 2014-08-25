#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("База студентів");
    AddstudForm = new AddStudentForm;

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QSqlQuery QueryForFaculties("select s.Name, s.FirstName, s.LastName from StudBd1.Students s");

    /////////////

    QueryForFaculties.exec();
    ui-> tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Прізвище"<<"Ім'я"<< "По-батькові");
    while(QueryForFaculties.next()){
        ui->  tableWidget->insertRow(0);
        ui-> tableWidget->setItem(0,0, new QTableWidgetItem(QueryForFaculties.value(0).toString()));
        ui->tableWidget->setItem(0,1, new QTableWidgetItem(QueryForFaculties.value(1).toString()));
        ui-> tableWidget->setItem(0,2, new QTableWidgetItem(QueryForFaculties.value(2).toString()));
        ui-> tableWidget->setRowHeight(0,20);
    }

    ui->tableWidget->show();


    ////////////////////////////////

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
    delete infoform;
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





void MainWindow::on_FacultiescomboBox_currentIndexChanged(int index)
{

    ui->DepartmentscomboBox->clear();
    QStringList temp;
    QSqlQuery queryForDepartmentcombobox;
    queryForDepartmentcombobox.prepare("SELECT f.id, d.nameOfDepartment, d.IdForFaculties FROM Faculties f, Departments d WHERE f.id = d.IdForFaculties AND f.id = ?");
    queryForDepartmentcombobox.bindValue(0, index+1);
    queryForDepartmentcombobox.exec();
    while(queryForDepartmentcombobox.next()){
        QString department = queryForDepartmentcombobox.value(1).toString();
        temp.push_back(department);
    }
    ui->DepartmentscomboBox->addItems(temp);
}



void MainWindow::on_FacultiescomboBox_activated(int index)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QSqlQuery QueryForFaculties("select s.Name, s.FirstName, s.LastName from StudBd1.Students s, StudBd1.Faculties f where f.id = s.IdOfFaculties and f.id = '" + QString::number(ui->FacultiescomboBox->currentIndex() + 1) +"'");
    QueryForFaculties.exec();
    qDebug() << ui->FacultiescomboBox->currentIndex()+1 <<" - is index";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Прізвище"<<"Ім'я"<< "По-батькові");
    while(QueryForFaculties.next()){
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0, new QTableWidgetItem(QueryForFaculties.value(0).toString()));
        ui->tableWidget->setItem(0,1, new QTableWidgetItem(QueryForFaculties.value(1).toString()));
        ui->tableWidget->setItem(0,2, new QTableWidgetItem(QueryForFaculties.value(2).toString()));
        ui->tableWidget->setRowHeight(0,20);
    }


}




void MainWindow::on_DepartmentscomboBox_activated(int index)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QSqlQuery QueryForFaculties("select s.Name, s.FirstName, s.LastName from StudBd1.Students s, StudBd1.Departments d, StudBd1.Faculties f where s.IdOfDepartment = d.id and s.IdOfFaculties = f.id and s.IdOfDepartment = '"+QString::number(ui->DepartmentscomboBox->currentIndex()+1) + "' and s.IdOfFaculties  = '"+QString::number(ui->FacultiescomboBox->currentIndex()+1) +"'");

    /////////////

    QueryForFaculties.exec();
    qDebug() << ui->FacultiescomboBox->currentIndex()+1 <<" - is index";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Прізвище"<<"Ім'я"<< "По-батькові");
    while(QueryForFaculties.next()){
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0, new QTableWidgetItem(QueryForFaculties.value(0).toString()));
        ui->tableWidget->setItem(0,1, new QTableWidgetItem(QueryForFaculties.value(1).toString()));
        ui->tableWidget->setItem(0,2, new QTableWidgetItem(QueryForFaculties.value(2).toString()));
        ui->tableWidget->setRowHeight(0,20);
    }

}






void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString temp1,temp2,temp3;
    if(column == 0){
        qDebug() <<"row is - " << row << "           columd is -- " << column;
        QTableWidgetItem *item = ui->tableWidget->item(row, column);
        temp1 = item->text();
        qDebug() <<"temp " <<temp1;
        /////////
        QTableWidgetItem *item1 = ui->tableWidget->item(row, column+1);
        temp2 = item1->text();
        qDebug() <<"temp " <<temp2;
        /////////

        QTableWidgetItem *item2 = ui->tableWidget->item(row, column + 2);
        temp3 = item2->text();
        qDebug() <<"temp " <<temp3;
    }
    if(column == 1){
        qDebug() <<"row is - " << row << "           columd is -- " << column;
        QTableWidgetItem *item = ui->tableWidget->item(row, column-1);
        temp1 = item->text();
        qDebug() <<"temp " <<temp1;
        /////////
        QTableWidgetItem *item1 = ui->tableWidget->item(row, column);
        temp2 = item1->text();
        qDebug() <<"temp " <<temp2;
        /////////

        QTableWidgetItem *item2 = ui->tableWidget->item(row, column + 1);
        temp3 = item2->text();
        qDebug() <<"temp " <<temp3;
    }
    if(column == 2){
        qDebug() <<"row is - " << row << "           columd is -- " << column;
        QTableWidgetItem *item = ui->tableWidget->item(row, column-2);
        temp1 = item->text();
        qDebug() <<"temp " <<temp1;
        /////////
        QTableWidgetItem *item1 = ui->tableWidget->item(row, column-1);
        temp2 = item1->text();
        qDebug() <<"temp " <<temp2;
        /////////

        QTableWidgetItem *item2 = ui->tableWidget->item(row, column );
        temp3 = item2->text();
        qDebug() <<"temp " << temp3;
    }

    infoform = new InformationForm(temp1, temp2, temp3, AcountAccessLevl);
    infoform->show();
}

void MainWindow::on_Add_Student_pushButton_clicked()
{
    AddstudForm->show();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("База студентів");
    ///////////////////
    //////////////////
    ///
    ///
    connect(ui->action, SIGNAL(triggered()), this, SLOT(on_Add_Student_pushButton_clicked()));//меню -> додати студента
    //    connect(infoform, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(Update_After_Close_Info()));
    //    connect(AddstudForm, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(Update_After_Close_Info()));
    connect(ui->action_2, SIGNAL(triggered()), this, SLOT(adminMainShow()));//адмінка

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QSqlQuery QueryForFaculties("select s.Name, s.FirstName, s.LastName, s.NumberOfGroup from Students s");

    /////////////

    QueryForFaculties.exec();
    ui-> tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Прізвище"<<"Ім'я"<< "По-батькові" << "Група");
    while(QueryForFaculties.next()){
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0, new QTableWidgetItem(QueryForFaculties.value(0).toString()));
        ui->tableWidget->setItem(0,1, new QTableWidgetItem(QueryForFaculties.value(1).toString()));
        ui->tableWidget->setItem(0,2, new QTableWidgetItem(QueryForFaculties.value(2).toString()));
         ui->tableWidget->setItem(0,3, new QTableWidgetItem(QueryForFaculties.value(3).toString()));
        ui->tableWidget->setRowHeight(0,20);
    }

    ui->tableWidget->show();


    ////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief queryForFacultiesBox1
    /// додавання списку факультетів до комбобоксу вибору
    /// зі збереженням у tempforfacultites
    //////////////////////////////////////////////////////////////////////////
    QSqlQuery queryForFacultiesBox1("SELECT NameOfFaculties  FROM Faculties");

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
//    delete adm;
}

void MainWindow::recieveaccesslevl(QStringList lvl)
{
    forAdminForm = lvl;
    int ID;
    ui->action_2->setVisible((lvl.at(1) == "superuser" || lvl.at(1) == "admin")?true:false);
    ui->Add_Student_pushButton->setVisible((lvl.at(1) == "superuser" || lvl.at(1) == "admin")?true:false);
    ui->action->setVisible((lvl.at(1) == "superuser" || lvl.at(1) == "admin")?true:false);
    ui->nononoact->setVisible((lvl.at(1) == "superuser" || lvl.at(1) == "admin")?false:true);
    ui->nononoact->setEnabled(false);
    AcountAccessLevl = lvl.at(1);
    QSqlQuery queryforid("SELECT id FROM LigingActions");
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
    query.prepare("insert into LigingActions (id, login, accesslevl, datatime) "
                  "VALUES (?, ?, ?, ?)");
    ID++;
    query.addBindValue(ID);
    query.addBindValue(lvl.at(0));
    query.addBindValue(lvl.at(1));
    query.addBindValue(Tdata);
    query.exec();

    //    ui->label->setText(AcountAccessLevl);
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
    QSqlQuery QueryForFaculties("select s.Name, s.FirstName, s.LastName s.NumberOfGroup from Students s, Faculties f where f.id = s.IdOfFaculties and f.id = '" + QString::number(ui->FacultiescomboBox->currentIndex() + 1) +"'");
    QueryForFaculties.exec();
    qDebug() << ui->FacultiescomboBox->currentIndex()+1 <<" - is index";
    ui->tableWidget->setColumnCount(4);
      ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Прізвище"<<"Ім'я"<< "По-батькові" << "Група");
    while(QueryForFaculties.next()){
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QueryForFaculties.value(0).toString()));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QueryForFaculties.value(1).toString()));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QueryForFaculties.value(2).toString()));
        ui->tableWidget->setItem(0,3, new QTableWidgetItem(QueryForFaculties.value(3).toString()));
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

    if(column == 3){
        qDebug() <<"row is - " << row << "           columd is -- " << column;
        QTableWidgetItem *item = ui->tableWidget->item(row, column-3);
        temp1 = item->text();
        qDebug() <<"temp " <<temp1;
        /////////
        QTableWidgetItem *item1 = ui->tableWidget->item(row, column-2);
        temp2 = item1->text();
        qDebug() <<"temp " <<temp2;
        /////////

        QTableWidgetItem *item2 = ui->tableWidget->item(row, column-1 );
        temp3 = item2->text();
        qDebug() <<"temp " << temp3;
    }


    infoform = new InformationForm(temp1, temp2, temp3, AcountAccessLevl);
    connect(infoform, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(Update_After_Close_Info()));
    connect(infoform, SIGNAL(closeEvent(QCloseEvent*)), infoform, SLOT(Del()));//test erase memorry
    infoform->show();
}

void MainWindow::on_Add_Student_pushButton_clicked()
{
    AddstudForm = new AddStudentForm;
    connect(AddstudForm, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(Update_After_Close_Info()));
    connect(AddstudForm, SIGNAL(closeEvent(QCloseEvent*)), AddstudForm, SLOT(Del()));// erase memorry
    AddstudForm->show();
}

void MainWindow::Update_After_Close_Info()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    QSqlQuery QueryForFaculties("select s.Name, s.FirstName, s.LastName, s.NumberOfGroup from Students s");

    /////////////

    QueryForFaculties.exec();
    ui-> tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Прізвище"<<"Ім'я"<< "По-батькові" << "Група");
    while(QueryForFaculties.next()){
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0, new QTableWidgetItem(QueryForFaculties.value(0).toString()));
        ui->tableWidget->setItem(0,1, new QTableWidgetItem(QueryForFaculties.value(1).toString()));
        ui->tableWidget->setItem(0,2, new QTableWidgetItem(QueryForFaculties.value(2).toString()));
        ui->tableWidget->setItem(0,3, new QTableWidgetItem(QueryForFaculties.value(3).toString()));
        ui->tableWidget->setRowHeight(0,20);
    }

    ui->tableWidget->show();
}
///////////////////////
/// \brief MainWindow::on_DepartmentscomboBox_currentIndexChanged
/// \param arg1
///
///
///
////////////////////////


void MainWindow::on_DepartmentscomboBox_activated(const QString &arg1)
{
    int Id_Of_Department;
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    //////////////////
    /// \brief Department_and_fac_index
    /// вибирається айдішник кафедри для запису
    //////////////////
    QSqlQuery Department_and_fac_index;
    Department_and_fac_index.prepare("select id from Departments d where nameOfDepartment = ?");
    Department_and_fac_index.bindValue(0, arg1);
    Department_and_fac_index.exec();
    while(Department_and_fac_index.next()){
        Id_Of_Department = Department_and_fac_index.value(0).toInt();
    }
    QSqlQuery Update_Dep;
    Update_Dep.prepare("select s.Name, s.FirstName, s.LastName from Students s where s.IdOfDepartment = ?");
    Update_Dep.addBindValue(Id_Of_Department);
    Update_Dep.exec();
    ///////////

    ui-> tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Прізвище"<<"Ім'я"<< "По-батькові");
    while(Update_Dep.next()){
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(Update_Dep.value(0).toString()));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(Update_Dep.value(1).toString()));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(Update_Dep.value(2).toString()));
        ui->tableWidget->setRowHeight(0,25);
    }

    ui->tableWidget->show();
}

void MainWindow::on_action_triggered()
{

}
///////////////////////
/// \brief MainWindow::adminMainShow
//////////////////////
void MainWindow::adminMainShow()
{
    mainAdminForm *adm = new mainAdminForm(forAdminForm);
    adm->show();
}

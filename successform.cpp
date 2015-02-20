#include "successform.h"
#include "ui_successform.h"

successform::successform(int IDStudent_, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::successform)
{
    ui->setupUi(this);
    /////////////////
    /// \brief queryForName
    /// в заголовок групу і ім'я студента оцінки якого виводяться
    ////////////////
    QSqlQuery queryForName;
    queryForName.prepare("SELECT s.NumberOfGroup, s.Name, s.FirstName, s.LastName FROM Students s WHERE s.id = ?");
    queryForName.addBindValue(IDStudent_);
    queryForName.exec();
    while(queryForName.next()){
        setWindowTitle("Оцінки студента " + queryForName.value(0).toString() + " групи, "+ queryForName.value(1).toString() + " " + queryForName.value(2).toString());
    }
    IDSTUDENT_ = IDStudent_;
    ui-> tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Назва дисципліни"<<"Дата отримання оцінки"<< "Оцінка");
    ////////////////
    /////////
    ///
    ui->tableWidget->setColumnWidth(0, 250);//шинира назви дисципліни
    ui->tableWidget->setColumnWidth(1, 160);//ширина дати оцінки
    ui->tableWidget->setColumnWidth(2, 50);//ширина оцінки
    ui->tableWidget->setRowHeight(1, 70);

    ///////////////////
    /// \brief ComboBoxQuery
    ///
    QSqlQuery ComboBoxQuery;
    //    ComboBoxQuery.prepare("select e.id, CONCAT(e.StartDate," - ",e.EndDate) as DATE_, e.idOfFaculties, e.idOfDepartment from Exams e");
    QString temp;
    //= ("select e.id, CONCAT(e.StartDate," + "-" + ",e.EndDate) as DATE_, e.idOfFaculties, e.idOfDepartment from Exams e");
    temp.append("select e.id, CONCAT(e.StartDate,");
    temp.append(" ' - ' ");
    temp.append(",e.EndDate) as DATE_, e.idOfFaculties, e.idOfDepartment from Exams e");
    qDebug ()<< temp;
    ComboBoxQuery.exec(temp);
    ////////////////
    ///////////////
    while(ComboBoxQuery.next()){
        int ID = ComboBoxQuery.value(0).toInt();
        ListForNameOfExams.append(ComboBoxQuery.value(1).toString());
        int IDFacultiet = ComboBoxQuery.value(2).toInt();
        int IDDepartment = ComboBoxQuery.value(3).toInt();
    }
    ui->examsCombobox->addItems(ListForNameOfExams);

    qDebug() << IDStudent_;
}

successform::~successform()
{
    delete ui;
}

void successform::on_examsCombobox_currentIndexChanged(int index)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Назва дисципліни"<<"Дата отримання оцінки"<< "Оцінка");
    ///////////////////////
    /// \brief QueryForChengeExam
    ///////////////////////
    QSqlQuery QueryForChengeExam;
    QueryForChengeExam.prepare("SELECT DISTINCT d.NameOfDiscipline, m.Date, m.Mark FROM Discipline d, Exams e, Marks m WHERE d.id = m.idDiscipline AND m.idExam = ? AND m.idStudent = ?");
    QueryForChengeExam.addBindValue(index + 1);
    QueryForChengeExam.addBindValue(IDSTUDENT_);
    if(QueryForChengeExam.exec()){
        while(QueryForChengeExam.next()){
            ui->tableWidget->insertRow(0);
            ui->tableWidget->setItem(0,0, new QTableWidgetItem(QueryForChengeExam.value(0).toString()));
            ui->tableWidget->setItem(0,1, new QTableWidgetItem(QueryForChengeExam.value(1).toString()));
            ui->tableWidget->setItem(0,2, new QTableWidgetItem(QueryForChengeExam.value(2).toString()));
        }
    }
    ui->tableWidget->show();
}

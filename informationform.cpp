#include "informationform.h"
#include "ui_informationform.h"

InformationForm::InformationForm(QString name, QString firstname, QString lastname, QString lvl, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InformationForm)
{
    ui->setupUi(this);
    connect(ui->save_button, SIGNAL(clicked()), this, SLOT(on_Chenges__triggered()));
    qDebug()<<"lvl = " << lvl;
    ///////
    ////////
    /// редагування данних
    /// ///
    connect(ui->exitbutton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->successact, SIGNAL(triggered()), this, SLOT(on_success_button_clicked()));
    connect(ui->closeact, SIGNAL(triggered()), this, SLOT(close()));
    ui->save_button->setVisible((lvl == "superuser" || lvl == "admin")?true:false);//кнопка зберегання змін
    ui->delete_button->setVisible((lvl == "superuser" || lvl == "admin")?true:false);//кнопка відрахування студента
    ui->Chenges_->setVisible((lvl == "superuser" || lvl == "admin")?true:false);//менюшка збереження змін
    ui->delact->setVisible((lvl == "superuser" || lvl == "admin")?true:false);
    ui->Chenges_->setEnabled(lvl == "superuser" || lvl == "admin" ? true:false);//24
    ui->statusbar->showMessage(lvl == "superuser" || lvl == "admin" ? "Ви маєте право редагувати данні":"Ваш рівень доступу не дозволяє змінювати дані", 15000);
    QString fac, dep;
    this->setWindowTitle("Студент "+name + " " + firstname + " " + lastname);
    QSqlQuery firstquery;
    firstquery.prepare("select * from Students where name = ? and firstname = ? and lastname = ?");
    firstquery.bindValue(0, name);
    firstquery.bindValue(1, firstname);
    firstquery.bindValue(2, lastname);
    firstquery.exec();
    while(firstquery.next()){
        idStudent = firstquery.value(0).toInt();
        qDebug() << "firstquery.value(0).toInt()" << idStudent;
        QString Name = firstquery.value(1).toString();
        ui -> namelineedit -> setText(Name);
        ///////////
        /// \brief FirstName
        ///////////
        QString FirstName = firstquery.value(2).toString();
        ui->firstnamelineedit->setText(FirstName);
        /////////
        /// \brief LastName
        /////////
        QString LastName = firstquery.value(3).toString();
        ui->lastnamelineedit->setText(LastName);
        //////////////
        /// \brief NumberOfGroup
        ///////////////
        QString NumberOfGroup = firstquery.value(4).toString();
        ui->numberofgroup->setText(NumberOfGroup);
        ///////////////
        /// \brief Telephone
        /// телефон студента
        ////////////////////
        QString Telephone = firstquery.value(9).toString();
        ui->studenttelephonelineedit->setText(Telephone);
        ////////////////
        /// \brief DateOfBirth
        ////////////////
        QString DateOfBirth = firstquery.value(8).toString();
        ui->studentdateofbirdthlineedit->setText(DateOfBirth);
        /////////////////
        /// \brief Date_Of_Entry
        ////////////////////
        QString Date_Of_Entry = firstquery.value(10).toString();
        ui->Date_Of_Entry->setText(Date_Of_Entry);
        /////////////////
        /// \brief End_Date
        ////////////////
        QString End_Date = firstquery.value(11).toString();
        ui->End_Date->setText(End_Date);
        ///////////////////////////
        /// \brief Father_name
        ///////////////////////////
        QString Father_name = firstquery.value(13).toString();
        ui->fathernalelineedit->setText(Father_name);
        ///////////////////
        /// \brief Mother_name
        /////////////////
        QString Mother_name = firstquery.value(14).toString();
        ui->mothernamelineedit->setText(Mother_name);
        ////////////////////////
        /// \brief Parents_Telaphone
        ///
        QString Parents_Telaphone = firstquery.value(15).toString();
        ui->parentsphonelineedit->setText(Parents_Telaphone);
        /////////////////////

        idOfFaculties = firstquery.value(6).toInt();
        idOfDepartment = firstquery.value(5).toInt();
    }

    qDebug() <<" id of department" <<idOfDepartment;
    qDebug() <<" id of idOfFaculties" <<idOfFaculties;
    /////////////
    /// \brief seconquery
    /// вивід факультету та інституту
    /// айдішники отримуються з попереднього запиту
    /////////////
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


//void InformationForm::Del(){
//    delete this;
//}


void InformationForm::on_Chenges__triggered()
{
    qDebug ()<<"on_Chenges__triggered";


    if(ui->namelineedit->text()!="" && ui->firstnamelineedit->text()!="" && ui->lastnamelineedit->text()!="" && ui->numberofgroup->text()!=""){
        QSqlQuery updateQuery;
        //    QString tempq = ("UPDATE Students SET Name = '"+ui->namelineedit->text()+"', FirstName = '"+ui->firstnamelineedit->text()+"', LastName = '"+ui->lastnamelineedit->text()+"', NumberOfGroup = '"+ui->numberofgroup->text()+"' DateOfBirth = '"+ui->studentdateofbirdthlineedit->text()+"', Telephone = '"+ui->studenttelephonelineedit->text()+"', DateOfEntry = '"+ui->Date_Of_Entry->text()+"', EndDate = '"+ui->End_Date->text()+"', FatherName = '"+ui->fathernalelineedit->text()+"', MotherName = '"+ui->mothernamelineedit->text()+"', ParentsPhone ='"+ui->parentsphonelineedit->text()+"' WHERE id = "+idStudent+"");
        //    updateQuery.prepare("UPDATE Students SET Name = ?, FirstName = ?, LastName = ?, NumberOfGroup = ? DateOfBirth = ?, Telephone = ?, DateOfEntry = ?, EndDate = ?, FatherName = ?, MotherName =?, ParentsPhone =? WHERE id = ?");
        //    updateQuery.prepare("UPDATE Students SET Name = '"+ui->namelineedit->text()+"', FirstName = '"+ui->firstnamelineedit->text()+"', LastName = '"+ui->lastnamelineedit->text()+"', NumberOfGroup = '"+ui->numberofgroup->text()+"' DateOfBirth = '"+ui->studentdateofbirdthlineedit->text()+"', Telephone = '"+ui->studenttelephonelineedit->text()+"', DateOfEntry = '"+ui->Date_Of_Entry->text()+"', EndDate = '"+ui->End_Date->text()+"', FatherName = '"+ui->fathernalelineedit->text()+"', MotherName = '"+ui->mothernamelineedit->text()+"', ParentsPhone ='"+ui->parentsphonelineedit->text()+"' WHERE id = '"+idStudent+"'");
        //        updateQuery.prepare("UPDATE Students s SET Name = :Name, FirstName = ?, LastName = ?, NumberOfGroup = ? DateOfBirth = ?, Telephone = ?, DateOfEntry = ?, EndDate = ?, FatherName = ?, MotherName =?, ParentsPhone =? WHERE id = ?"););
        updateQuery.prepare("UPDATE Students s SET s.Name = :Name, s.FirstName = :FirstName, s.LastName = :LastName, s.NumberOfGroup = :NumberOfGroup, s.DateOfBirth = :DateOfBirth, s.Telephone = :Telephone, s.DateOfEntry = :DateOfEntry, s.EndDate = :EndDate, s.FatherName = :FatherName, s.MotherName =:MotherName, s.ParentsPhone = :ParentsPhone WHERE s.id = :id");






        updateQuery.bindValue(":Name" ,ui->namelineedit->text());
        updateQuery.bindValue(":FirstName", ui->firstnamelineedit->text());
        updateQuery.bindValue(":LastName", ui->lastnamelineedit->text());
        updateQuery.bindValue(":NumberOfGroup", ui->numberofgroup->text());
        updateQuery.bindValue(":DateOfBirth", ui->studentdateofbirdthlineedit->text());
        updateQuery.bindValue(":Telephone", ui->studenttelephonelineedit->text());
        updateQuery.bindValue(":DateOfEntry", ui->Date_Of_Entry->text());
        updateQuery.bindValue(":EndDate", ui->End_Date->text());
        updateQuery.bindValue(":FatherName", ui->fathernalelineedit->text());
        updateQuery.bindValue(":MotherName", ui->mothernamelineedit->text());
        updateQuery.bindValue(":ParentsPhone" , ui->parentsphonelineedit->text());
        updateQuery.bindValue(":id", idStudent);



        QMessageBox msgBox;
        msgBox.setText("У обліковий запис внесені зміни");
        msgBox.setInformativeText("Ви впевнені що бажаєте зберегти зміни?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Save:
            // Save was clicked

            updateQuery.exec();
            ui->statusbar->showMessage("Вітаємо! Зміни збережено!", 5000);
            break;

        default:
            // should never be reached
            ui->statusbar->showMessage("Зміни до облікового запису не внесені!", 5000);
            break;
        }
    }
    else{
        QMessageBox msgeErase;
        //        msgeErase.setText("Заповніть обов'язкові поля");
        msgeErase.setInformativeText("Заповніть обов'язкові поля");
        msgeErase.setStandardButtons(QMessageBox::Ok);
        msgeErase.setDefaultButton(QMessageBox::Ok);
        int ret = msgeErase.exec();
    }
}





void InformationForm::on_success_button_clicked()
{
    successform *suForm = new successform(idStudent);
    suForm->show();
}

void InformationForm::Del()
{
    delete this;
}

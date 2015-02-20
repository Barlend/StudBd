#ifndef INFORMATIONFORM_H
#define INFORMATIONFORM_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDateEdit>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include "successform.h"
namespace Ui {
class InformationForm;
}

class InformationForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit InformationForm(QString name,QString firsname, QString lastname, QString lvl, QWidget *parent = 0);
    ~InformationForm();
signals:
    void closeEvent(QCloseEvent *e);


    //protected:
    //    void closeEventt(QCloseEvent *e){
    //        delete this;
    //    }

private slots:
    void on_Chenges__triggered();

    void on_success_button_clicked();
    void Del();

private:
    Ui::InformationForm *ui;
    int idOfFaculties, idOfDepartment, idStudent;
};

#endif // INFORMATIONFORM_H

#ifndef INFORMATIONFORM_H
#define INFORMATIONFORM_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDateEdit>
#include <QDate>
#include <QDebug>
namespace Ui {
class InformationForm;
}

class InformationForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit InformationForm(QString name,QString firsname, QString lastname, QString lvl, QWidget *parent = 0);
    ~InformationForm();

private:
    Ui::InformationForm *ui;
    int idOfFaculties, idOfDepartment;
};

#endif // INFORMATIONFORM_H

#ifndef INFORMATIONFORM_H
#define INFORMATIONFORM_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDateEdit>
#include <QDate>

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
};

#endif // INFORMATIONFORM_H

#ifndef ADDSTUDENTFORM_H
#define ADDSTUDENTFORM_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QDateEdit>
namespace Ui {
class AddStudentForm;
}

class AddStudentForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddStudentForm(QWidget *parent = 0);
    ~AddStudentForm();

private slots:

    void on_AddSudentButton_clicked();
void Del(){
    delete this;
}
    void on_FacultiescomboBox_currentIndexChanged(int index);
signals:
   void closeEvent(QCloseEvent *e);
private:
    Ui::AddStudentForm *ui;
    QStringList tempforfacultites;
};

#endif // ADDSTUDENTFORM_H

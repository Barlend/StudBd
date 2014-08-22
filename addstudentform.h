#ifndef ADDSTUDENTFORM_H
#define ADDSTUDENTFORM_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSqlQuery>
#include <QDebug>
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

    void on_FacultiescomboBox_currentIndexChanged(int index);

private:
    Ui::AddStudentForm *ui;
    QStringList tempforfacultites;
};

#endif // ADDSTUDENTFORM_H

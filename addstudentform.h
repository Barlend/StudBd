#ifndef ADDSTUDENTFORM_H
#define ADDSTUDENTFORM_H

#include <QMainWindow>
#include <QLineEdit>

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

private:
    Ui::AddStudentForm *ui;
};

#endif // ADDSTUDENTFORM_H

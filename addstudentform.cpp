#include "addstudentform.h"
#include "ui_addstudentform.h"

AddStudentForm::AddStudentForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddStudentForm)
{
    ui->setupUi(this);
}

AddStudentForm::~AddStudentForm()
{
    delete ui;
}

#include "informationform.h"
#include "ui_informationform.h"

InformationForm::InformationForm(QString name, QString firsname, QString lastname, QString lvl, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InformationForm)
{
    ui->setupUi(this);
    ui->label->setText(lvl);
}

InformationForm::~InformationForm()
{
    delete ui;
}

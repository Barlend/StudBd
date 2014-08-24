#include "informationform.h"
#include "ui_informationform.h"

InformationForm::InformationForm(QString id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InformationForm)
{
    ui->setupUi(this);
    ui->label->setText(id);
}

InformationForm::~InformationForm()
{
    delete ui;
}

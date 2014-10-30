#include "successform.h"
#include "ui_successform.h"

successform::successform(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::successform)
{
    ui->setupUi(this);
}

successform::~successform()
{
    delete ui;
}

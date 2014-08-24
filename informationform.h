#ifndef INFORMATIONFORM_H
#define INFORMATIONFORM_H

#include <QMainWindow>

namespace Ui {
class InformationForm;
}

class InformationForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit InformationForm(QString id, QWidget *parent = 0);
    ~InformationForm();

private:
    Ui::InformationForm *ui;
};

#endif // INFORMATIONFORM_H

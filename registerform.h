#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = 0);
    ~RegisterForm();

private slots:
    void on_RegisterButton_clicked();
signals:
   void closeEvent(QCloseEvent *e);

//        this->close();
//    }

private:
    Ui::RegisterForm *ui;
};

#endif // REGISTERFORM_H

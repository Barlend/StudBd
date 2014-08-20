#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QSqlQuery>
#include "mainwindow.h"
#include "registerform.h"
#include <QStringList>
namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private slots:
    void on_pushButton_clicked();

    void on_SingInButton_clicked();
signals:
    void sendaccesslevel(QStringList lvl);
private:
    Ui::LoginForm *ui;
    RegisterForm *regForm;
    MainWindow *mainForm;
    QString accesslevel;
    QStringList Listforauth;
};

#endif // LOGINFORM_H

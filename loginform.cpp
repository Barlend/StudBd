#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    setWindowTitle("Вітаємо у базі даних студентів");
    setWindowFlags(Qt::Window
                   | Qt::WindowMinimizeButtonHint
                   | Qt::WindowCloseButtonHint
                   | Qt::CustomizeWindowHint);
    regForm = new RegisterForm;
    connect(regForm, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(show()));

    mainForm = new MainWindow;
    connect(this, SIGNAL(sendaccesslevel(QStringList)), mainForm, SLOT(recieveaccesslevl(QStringList)));
}

LoginForm::~LoginForm()
{
    delete ui;
    delete regForm;
    delete mainForm;
}

void LoginForm::on_pushButton_clicked()
{

    this->hide();
    regForm->show();


}

void LoginForm::on_SingInButton_clicked()
{
    QSqlQuery query;
    query.exec("select login, password, accesslevel from StudBd1.Users");
    while (query.next()) {
        QString user = query.value(0).toString();
        QString password = query.value(1).toString();
        accesslevel = query.value(2).toString();
        if(ui->LoginlineEdit->text() == user && ui->PasswordlineEdit->text() == password){
            Listforauth << user << accesslevel;
            emit(sendaccesslevel(Listforauth));
            this->close();

            mainForm->show();
        }
    }
    ui->StatusLabel->setText("Облікових даних не знайдено");
}





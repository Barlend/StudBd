#ifndef SUCCESSFORM_H
#define SUCCESSFORM_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDateEdit>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>
#include <QTableWidget>
#include <QStringList>
#include <QDebug>
#include <QCloseEvent>
namespace Ui {
class successform;
}

class successform : public QMainWindow
{
    Q_OBJECT

public:
    explicit successform(int IDStudent_ ,QWidget *parent = 0);
    ~successform();
protected:
    void closeEvent(QCloseEvent *){
        delete this;
    }

private slots:
    void on_examsCombobox_currentIndexChanged(int index);

private:
    Ui::successform *ui;
    QStringList ListForNameOfExams;
    int IDSTUDENT_;
};

#endif // SUCCESSFORM_H

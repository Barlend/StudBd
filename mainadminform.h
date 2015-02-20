#ifndef MAINADMINFORM_H
#define MAINADMINFORM_H

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
#include <QLabel>
#include <QStringList>
#include <QSqlTableModel>
//#include "editablesqlmodel.h"
#include <QMessageBox>

namespace Ui {
class mainAdminForm;
}

class mainAdminForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainAdminForm(QStringList data, QWidget *parent = 0);
    ~mainAdminForm();

private slots:
    void on_FacultiescomboBox_currentIndexChanged(int index);

    void on_DepartmentscomboBox_currentIndexChanged(int index);

    void on_FacultiescomboBox_add_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_addDirectionButton_clicked();

    void on_AddFacultiesButton_clicked();

private:
    Ui::mainAdminForm *ui;
    QStringList data_;
    QStringList tempforfacultites;
    QSqlTableModel *modelusers, *facultiesmodel;
    void users();
    int GetId(QString name);
    void FacultiesViev();
};

#endif // MAINADMINFORM_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDateTime>
#include <QComboBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "informationform.h"
#include "addstudentform.h"
#include "mainadminform.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void recieveaccesslevl(QStringList lvl);
private slots:
    void on_FacultiescomboBox_currentTextChanged(const QString &arg1);

    void on_FacultiescomboBox_currentIndexChanged(int index);

    void on_FacultiescomboBox_activated(int index);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_Add_Student_pushButton_clicked();

    void Update_After_Close_Info();

    void on_DepartmentscomboBox_activated(const QString &arg1);

    void on_action_triggered();
    void adminMainShow();
private:
    void FacultitesQuery();
    Ui::MainWindow *ui;
    QString AcountAccessLevl;
    QDateTime data;
    QStringList tempforfacultites,tempforinstitutes, forAdminForm;
    AddStudentForm *AddstudForm;
    InformationForm *infoform;
};

#endif // MAINWINDOW_H

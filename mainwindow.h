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

    void on_FacultiescomboBox_currentIndexChanged(const QString &arg1);

//    void on_FacultiescomboBox_activated(const QString &arg1);

    void on_FacultiescomboBox_currentIndexChanged(int index);

private:
    void FacultitesQuery();
    Ui::MainWindow *ui;
    QString AcountAccessLevl;
    QDateTime data;
    QStringList tempforfacultites,tempforinstitutes;
    QSqlTableModel *model;
    QTableView *tableView;
};

#endif // MAINWINDOW_H

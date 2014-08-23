#ifndef CONNECTTODATABASE_H
#define CONNECTTODATABASE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
namespace Ui {
class ConnectToDatabase;
}

class ConnectToDatabase : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectToDatabase(QWidget *parent = 0);
    ~ConnectToDatabase();
private slots:
    void Connect();
signals:
   void closeEvent(QCloseEvent *e);
private:
    Ui::ConnectToDatabase *ui;

};

#endif // CONNECTTODATABASE_H

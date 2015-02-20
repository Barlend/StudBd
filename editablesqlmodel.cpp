#include <QtSql>
#include <QDebug>
#include "editablesqlmodel.h"

EditableSqlModel::EditableSqlModel(QString fac, QObject *parent)
    : QSqlQueryModel(parent)
{
    Fac = fac;
    QSqlQuery GetIdDep;
    GetIdDep.prepare("SELECT f.id FROM Faculties f where f.NameOfFaculties = ?");
    GetIdDep.addBindValue(Fac);
    GetIdDep.exec();
    id = GetIdDep.value(0).toInt();

}

Qt::ItemFlags EditableSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 0 ||index.column() == 1 || index.column() == 2)
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool EditableSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() < 0 || index.column() > 2){
        qDebug() << "false";
        return false;
    }
    qDebug() << "setData ----- true";
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int id = data(primaryKeyIndex).toInt();
qDebug ()<<id  << " id";
    clear();

    bool ok;
    if (index.column() == 1) {
        ok = setStart(id, value.toString());
    } else {
        ok = setEnd(id, value.toString());
    }
    refresh();
    return ok;
}

void EditableSqlModel::refresh()
{
    //    setQuery("select * from person");
    //"SELECT e.StartDate, e.EndDate, e.idOfFaculties, e.idOfDepartment FROM Exams e, Departments d WHERE e.id = d.id AND d.nameOfDepartment = '"+ui->DepartmentscomboBox->currentText()+"'"
    setQuery("SELECT e.StartDate, e.EndDate FROM Exams e, Departments d WHERE e.id = d.id AND d.nameOfDepartment = '"+Fac+"'"); // WORK!
//    setQuery("SELECT f.id FROM Faculties f where f.NameOfFaculties = '"+QString::number(id)+"'");
    //    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    setHeaderData(1, Qt::Horizontal, QObject::tr(""));
//    setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}

bool EditableSqlModel::setStart(int personId, const QString &start)
{
    QSqlQuery query;
    query.prepare("update Exams set StartDate = ? where id = ?");
    query.addBindValue(start);
    query.addBindValue(personId);
    return query.exec();
}

bool EditableSqlModel::setEnd(int personId, const QString &end)
{
    QSqlQuery query;
    query.prepare("update Exams set EndDate = ? where id = ?");
    query.addBindValue(end);
    query.addBindValue(personId);
    return query.exec();
}

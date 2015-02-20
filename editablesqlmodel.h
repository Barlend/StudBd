#ifndef EDITABLESQLMODEL_H
#define EDITABLESQLMODEL_H

#include <QSqlQueryModel>
#include <QSqlQuery>
class EditableSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    EditableSqlModel(QObject *parent = 0);
//    EditableSqlModel(QString Dep, QObjec*parent = 0);
    EditableSqlModel(QString fac, QObject *parent = 0);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    bool setStart(int personId, const QString &start);
    bool setEnd(int personId, const QString &end);
    void refresh();
protected:
    QString Fac;
    int id;
};

#endif

#ifndef SUCCESSFORM_H
#define SUCCESSFORM_H

#include <QMainWindow>

namespace Ui {
class successform;
}

class successform : public QMainWindow
{
    Q_OBJECT

public:
    explicit successform(QWidget *parent = 0);
    ~successform();

private:
    Ui::successform *ui;
};

#endif // SUCCESSFORM_H

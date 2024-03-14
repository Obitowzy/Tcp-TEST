#ifndef BIANBI_H
#define BIANBI_H

#include <QDialog>
#include "qfloat16.h"
#include <QPushButton>
namespace Ui {
class bianbi;
}

class bianbi : public QDialog
{
    Q_OBJECT

public:
    explicit bianbi(QWidget *parent = nullptr);
    ~bianbi();

    qfloat16 cal();


private:
    Ui::bianbi *ui;
    QString Name;
    QString num1;
    QString num2;
};

#endif // BIANBI_H

#ifndef FENLIANG3_H
#define FENLIANG3_H

#include <QMessageBox>
#include <QWidget>
#include <iostream>
#include <math.h>
#include <QComboBox>
#include "fenliang2.h"
namespace Ui {
class fenliang3;
}


class fenliang3 : public QWidget
{
    Q_OBJECT

public:
    explicit fenliang3(QWidget *parent = nullptr);
    ~fenliang3();
public:
    void refresh3(QWidget* w,int s, int a,int b,int c);
    void refreshall3(QWidget*,QWidget*);
private:
    Ui::fenliang3 *ui;

};

#endif // FENLIANG3_H

#ifndef GONGLV_H
#define GONGLV_H

#include <QWidget>
#include <fenliang2.h>
#include <math.h>
namespace Ui {
class gonglv;
}

class gonglv : public QWidget
{
    Q_OBJECT

public:
    explicit gonglv(QWidget *parent = nullptr);
    ~gonglv();
public:
    void refreshallg(QWidget*,QWidget*);

private:
    Ui::gonglv *ui;

};

#endif // GONGLV_H

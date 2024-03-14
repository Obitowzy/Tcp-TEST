#ifndef FENLIANG1_H
#define FENLIANG1_H


#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QComboBox>
namespace Ui {
class fenliang1;
}

class fenliang1 : public QWidget
{
    Q_OBJECT

public:
    explicit fenliang1(QWidget *parent = nullptr);
    ~fenliang1();
public:
    void refresh1(QWidget* ,int s, int a,int b,int c);
    void refreshall1(QWidget*,QWidget*);


private:
    Ui::fenliang1 *ui;

};

#endif // FENLIANG1_H

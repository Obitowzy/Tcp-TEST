#ifndef MAINUI_H
#define MAINUI_H
#include "mainwindow.h"
#include <QMainWindow>

namespace Ui {
class mainUI;
}

class mainUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainUI(QWidget *parent = nullptr);
    ~mainUI();

private:
    Ui::mainUI *ui;
    QWidget* CentralWidget1;
    QWidget* CentralWidget2;
    MainWindow* m;
    void loadStyleFile();
};

#endif // MAINUI_H

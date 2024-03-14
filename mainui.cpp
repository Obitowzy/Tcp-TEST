#include "mainui.h"
#include "ui_mainui.h"
#include <QTableWidget>
#include <QGridLayout>
#include "mainwindow.h"
#include "signal_ui.h"
mainUI::mainUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainUI)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("自动化测试系统"));
    this->setWindowIcon(QIcon(":/new/prefix1/myappico.ico"));
    ui->menubar->hide();
    this->setCentralWidget(ui->tabWidget);
    loadStyleFile();
    ui->tab_1->setContentsMargins(0, 0, 0, 0);


    // 创建一个中央窗口部件
    CentralWidget1 = new QWidget(ui->tab_1);
    ui->tab_1->setGeometry(-10, -10, 950, 770);
    CentralWidget2 = new QWidget(ui->tab_2);
    ui->tab_1->setGeometry(-10, -10, 950, 770);

    // 创建一个布局管理器
    QGridLayout* centralLayout = new QGridLayout(CentralWidget1);
    centralLayout->setSpacing(0);
    QGridLayout* centralLayout1 = new QGridLayout(CentralWidget2);
    centralLayout->setSpacing(0);

    if (ui->tabWidget->currentIndex() == 0)
    {

        // 创建主窗口部件
        MainWindow* m = new MainWindow();
        // 添加主窗口部件到布局管理器中
        centralLayout->addWidget(m, 0, 0);
        // 设置布局管理器
        ui->tab_1->setLayout(centralLayout);
    }

        signal_ui* s = new signal_ui();
        centralLayout1->addWidget(s,0,0);
        ui->tab_2->setLayout(centralLayout1);



}

mainUI::~mainUI()
{
    delete ui;
}
void mainUI::loadStyleFile() {
    QFile file(":/new/prefix1/QSS.git/trunk/MacOS.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    this->setStyleSheet(styleSheet);
    file.close();
}

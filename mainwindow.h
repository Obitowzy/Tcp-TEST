#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidget>
#include <QAction>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHostInfo>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTcpSocket>
#include "tcplist.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    QPlainTextEdit* back1(){
        return m_pPlainText;
    }
    QTcpSocket* back2(){
        return tcp.m_pTcpClient;
    }

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    //工具栏按钮
    void slotActConnectTriggered();
    void slotActDisConnectTriggered();
    void slotActClearTriggered();
    void slotActQuitTriggered();

    //界面按钮
    void slotBtnSendClicked();

    //自定义槽函数
    void slotConnected();
    void slotDisconnected();
    void slotSocketStateChange(QAbstractSocket::SocketState socketState);
    void slotSocketReadyRead(QTcpSocket* t);
    QTcpSocket* reTcpback(QTableWidgetItem*I );
    QTcpSocket* reTcpback1(QTableWidgetItem*I );
    QTcpSocket* reTcpback2(int row );
    QTcpSocket* reTcpback3(int row );
//    QTcpSocket* reTcpbackauto(int c);

public slots:
    void connectTcp(QTcpSocket* t);
    void slotsetzore(int row);
    void slotsetone(int row);
    void slotsettriggered(int row);
    void onItemClicked(QTableWidgetItem* item);
    void onCellChanged(int row, int col);

    void ItemClicked(QTableWidgetItem*);
    void inittabtrip();
    void inittabset();
    void DeleteProgram(QTableWidgetItem* item);
    void Addline();


private:
    Ui::MainWindow* ui;
    QTcpSocket* N;
    QAction* m_pActConnectServer;
    QAction* m_pActDisconnect;
    QAction* m_pActClear;
    QAction* m_pActQuit;

    QWidget* CentralWidget;
    QWidget* m_pCentralWidget;
    QWidget* m_pCentralWidget1;

    QLabel* m_pLabel1;
    QLabel* m_pLabel2;
    QLineEdit* m_pLineEditIP;
    QSpinBox* m_pSpinBoxPort;
    QLineEdit* m_pLineEdit;
    QPushButton* m_pBtnSend;
    QPlainTextEdit* m_pPlainText;
    QLabel* m_pLabSocketState;

    QTableWidget *table;
    QTableWidget *table_1;
    TCPL tcp;


    QString getLocalIP();
    void loadStyleFile();

};

#endif  // MAINWINDOW_H

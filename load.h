#ifndef LOAD_H
#define LOAD_H

#include <QWidget>
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
namespace Ui {
class load;
}

class load : public QWidget
{
    Q_OBJECT

public:
    explicit load(QWidget *parent = nullptr);
    ~load();
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
    void slotSocketReadyRead();

private:
    Ui::load* ui;

    QAction* m_pActConnectServer;
    QAction* m_pActDisconnect;
    QAction* m_pActClear;
    QAction* m_pActQuit;
    QWidget* m_pCentralWidget;
    QLabel* m_pLabel1;
    QLabel* m_pLabel2;
    QLineEdit* m_pLineEditIP;
    QSpinBox* m_pSpinBoxPort;
    QLineEdit* m_pLineEdit;
    QPushButton* m_pBtnSend;
    QPlainTextEdit* m_pPlainText;
    QLabel* m_pLabSocketState;
    QTcpSocket* m_pTcpClient;

    QString getLocalIP();
    void loadStyleFile();
};

#endif // LOAD_H

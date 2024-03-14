#ifndef SIGNAL_UI_H
#define SIGNAL_UI_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTableWidget>
#include <QAction>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHostInfo>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTcpSocket>
#include <QComboBox>

#include "fenliang1.h"
#include "fenliang2.h"
#include "fenliang3.h"
#include "gonglv.h"
#include "bianbi.h"
namespace Ui {
class signal_ui;
}

class signal_ui : public QMainWindow
{
    Q_OBJECT

public:
    explicit signal_ui(QWidget *parent = nullptr);
    void initedit();

    ~signal_ui();

    QString tohex(const QString &input);
    qfloat16 transrat(int index);
    void swicha(const int i,QString& amplitude,QString& phase,int& n,QString &num);
    QPlainTextEdit* m_pPlainText;
    QTcpSocket* m_pTcpClient11;
    void conSandL();
    int flag;



protected:
    void closeEvent11(QCloseEvent* event);
private slots:
    void slotActConnectTriggered11();
    void slotActDisConnectTriggered11();
    void slotConnected11();

    void slotDisconnected11();
    void slotActQuitTriggered11();
    void slotSocketStateChange11(QAbstractSocket::SocketState socketState);
    void slotSocketReadyRead();
    //
    void slotssignal();
    void begain();
    void stop();
    void saveConfigToFile(const QString& filePath, const QString& comboBoxText, const QString& lineEditText1,const QString& lineEditText2, int lineNumber);
    void loadConfigFromFile(const QString& filePath, QComboBox* comboBox, QLineEdit* lineEdit1,QLineEdit* lineEdit2, int lineNumber);
    void SwitchCo(int );
    void connectall();
    void showbianbi();

    //    void pisave();
//    void piload();
private:

    Ui::signal_ui *ui;

    fenliang1* f1 ;
    fenliang2* f2;
    fenliang3* f3;
    gonglv* gl;
    bianbi* bb;

    QLabel* m_pLabSocketState11;
    QAction* m_pActConnectServer11;
    QAction* m_pActDisconnect11;
    QAction* m_pActClea11r;
    QAction* m_pActQuit11;
    QAction* m_pActSavecon;
    QAction* m_pActLoadcon;
    QTimer* m_pCommandTimer;
    QTimer* t;
    QLabel* m_pLabel1;
    QLabel* m_pLabel2;
    QLineEdit* m_pLineEditIP;
    QSpinBox* m_pSpinBoxPort;
    QComboBox* m_pComBox;

    qfloat16 *Spare1 ;
    qfloat16 *Spare2 ;
    qfloat16 *Spare3 ;
    qfloat16 *Spare4 ;
    qfloat16 *Spare5 ;







};

#endif // SIGNAL_UI_H


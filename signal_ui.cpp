#include "signal_ui.h"
#include "ui_signal_ui.h"
#include <QRegExp>
#include <QString>
#include <QTimer>
#include "ui_signal_ui.h"
#include <QThread>
#include <qfloat16.h>
#include <math.h>
#include <QObject>

signal_ui::signal_ui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::signal_ui)
{

    ui->setupUi(this);
    initedit();
    //  设置可填参数范围
    //  myButton = ui->loadwave;
//    ui->widget_2->hide();
    ui->bar1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->bar1->setMinimumHeight(50);
    m_pActConnectServer11 = new QAction(QIcon(":/new/prefix1/QSS_IMG/object-select-symbolic.symbolic.png"), QStringLiteral("连接服务器"), this);
    m_pActDisconnect11 = new QAction(QIcon(":/new/prefix1/res/断开链接.png"), QStringLiteral("断开连接"), this);
    //  m_pActClear = new QAction(QIcon(":/new/prefix1/res/清空数据.png"), QStringLiteral("清空文本框"), this);
    m_pActQuit11 = new QAction(QIcon(":/new/prefix1/res/退出.png"), QStringLiteral("退出"), this);
    m_pActSavecon = new QAction(QIcon(":/new/prefix1/res/保存.png"),QStringLiteral("保存配置"), this);
    m_pActLoadcon = new QAction(QIcon(":/new/prefix1/res/读取.png"),QStringLiteral("读取配置"), this);

    ui->bar1->addAction(m_pActConnectServer11);
    ui->bar1->addAction(m_pActDisconnect11);
    ui->bar1->addSeparator();
    ui->bar1->addAction(m_pActSavecon);
    ui->bar1->addAction(m_pActLoadcon);
    ui->bar1->addSeparator();
//    ui->bar1->addAction(m_pActQuit11);

    ui->CentralWidgeta->setGeometry(0,50,800,150);

    m_pLabel1 = new QLabel(QStringLiteral("服务器地址"), ui->CentralWidgeta);
    m_pLabel2 = new QLabel(QStringLiteral("端口"), ui->CentralWidgeta);
    m_pLineEditIP = new QLineEdit(ui->CentralWidgeta);
    m_pSpinBoxPort = new QSpinBox(ui->CentralWidgeta);
    m_pSpinBoxPort->setMinimum(1);
    m_pSpinBoxPort->setMaximum(65535);
    m_pLineEditIP->setText("192.168.15.4");
    m_pSpinBoxPort->setValue(5000);

    QHBoxLayout* HLay1 = new QHBoxLayout();
    HLay1->addWidget(m_pLabel1, 2);
    HLay1->addWidget(m_pLineEditIP, 6);
    HLay1->addWidget(m_pLabel2, 2, Qt::AlignRight);
    HLay1->addWidget(m_pSpinBoxPort, 3);


    //状态栏
    m_pLabSocketState11 = new QLabel(this);
    m_pLabSocketState11->setText(QStringLiteral("socket状态："));
    ui->statusBar->addWidget(m_pLabSocketState11);
    m_pLabSocketState11->setMinimumWidth(150);
    //    aboutqcustomplot* wave = new aboutqcustomplot();

    //    ui->gridLayout_2->setRowStretch(0,)
    m_pPlainText = new  QPlainTextEdit(ui->CentralWidgeta);
    QGridLayout* centralLayout = new QGridLayout(ui->CentralWidgeta);
    QVBoxLayout * HLay2 = new QVBoxLayout ();
    HLay2->addWidget(ui->widget_3,1);
    HLay2->addWidget(ui->widget_4,5);

    QHBoxLayout *HLay3 = new QHBoxLayout();
    HLay3->addWidget(ui->widget_1,20);
    HLay3->addLayout(HLay2,15);
    HLay3->setAlignment(Qt::AlignTop);


    centralLayout->addLayout(HLay1 , 0, 0);
    //    centralLayout->addWidget(new QWidget(), 1, 0);  // 占位符行
    centralLayout->addLayout(HLay3, 1, 0);
    //    centralLayout->addLayout(HLay2, 2, 1);  // 添加到下一行
    centralLayout->addWidget(m_pPlainText,2,0);

    centralLayout->setRowStretch(0,1);
    //    centralLayout->setRowStretch(1,1);
    centralLayout->setRowStretch(1,30);
    centralLayout->setRowStretch(2,2);

    //    centralLayout->setColumnStretch(0,10);
    //    centralLayout->setColumnStretch(1,5);
    ui->CentralWidgeta->setLayout(centralLayout);
    conSandL();
    //参数计算
    bb = new bianbi(ui->CentralWidgeta);
    bb->hide();
    f1 = new fenliang1(ui->widget);
    f2 = new fenliang2(ui->widget);
    f3 = new fenliang3(ui->widget);
    gl = new gonglv(ui->widget);
    //f1->hide();
    f2->hide();
    f3->hide();
    gl->hide();
    ui->checkBox_1->setCheckState(Qt::Checked);
    ui->checkBox_2->setCheckState(Qt::Checked);
    ui->checkBox_3->setCheckState(Qt::Checked);
    ui->checkBox_4->setCheckState(Qt::Checked);
    ui->checkBox_5->setCheckState(Qt::Checked);


    //下发参数按键
    m_pCommandTimer = new QTimer(this);
    t = new QTimer();
    m_pComBox = ui->comboBox;
    m_pTcpClient11 = new QTcpSocket(this);
    connectall();
}

signal_ui::~signal_ui()
{
    delete ui;
}

void signal_ui::connectall(){
    connect(ui->sendwave,&QPushButton::clicked,this,&signal_ui::slotssignal);
    connect(m_pCommandTimer, &QTimer::timeout, this, &signal_ui::slotssignal);
    //开始停止按键
    connect(t,&QTimer::timeout,this,&signal_ui::begain);
    connect(ui->loadwave,&QPushButton::clicked,this,&signal_ui::stop);
    connect(m_pActConnectServer11, &QAction::triggered, this, &signal_ui::slotActConnectTriggered11);
    connect(m_pActDisconnect11, &QAction::triggered, this, &signal_ui::slotActDisConnectTriggered11);
    connect(m_pActQuit11, &QAction::triggered, this, &signal_ui::slotActQuitTriggered11);
    connect(m_pComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SwitchCo(int)));
    connect(m_pTcpClient11, &QTcpSocket::connected, this, &signal_ui::slotConnected11);
    connect(m_pTcpClient11, &QTcpSocket::disconnected, this, &signal_ui::slotDisconnected11);
    connect(m_pTcpClient11, &QTcpSocket::stateChanged, this, &signal_ui::slotSocketStateChange11);
    connect(m_pTcpClient11, &QTcpSocket::readyRead, this, &signal_ui::slotSocketReadyRead);
    connect(ui->bianbi,&QPushButton::clicked,this,&signal_ui::showbianbi);






    const int rowCount =16;
    const int columnCount =2;

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            QString lineEditName = QString("lineEdit_%1_%2").arg(i + 1).arg(j + 1);
            QLineEdit* lineEdit = ui->widget_1_1->findChild<QLineEdit*>(lineEditName);

            if (lineEdit) {
                connect(lineEdit, &QLineEdit::textChanged, [=](){
                    f1->refreshall1(ui->widget_1_1,ui->widget_3);
                    f2->refreshall2(ui->widget_1_1,ui->widget_3);
                    gl->refreshallg(ui->widget_1_1,ui->widget_3);
                });
            }
        }

}

for (int j = 1;j<=5; j++) {
    QString ComboBoxEditName1 = QString("comboBox_%1A").arg(j);
    QString ComboBoxEditName2 = QString("comboBox_%1B").arg(j);
    QString ComboBoxEditName3 = QString("comboBox_%1C").arg(j);
    QString CheckBoxEditName = QString("checkBox_%1").arg(j);

    QComboBox * C1 = ui->widget_3->findChild<QComboBox*>(ComboBoxEditName1);
    QComboBox * C2 = ui->widget_3->findChild<QComboBox*>(ComboBoxEditName2);
    QComboBox * C3 = ui->widget_3->findChild<QComboBox*>(ComboBoxEditName3);
    QCheckBox * C4 = ui->widget_4->findChild<QCheckBox*>(CheckBoxEditName);

    connect(C4, &QCheckBox::toggled, [=]() {
        // 在 lambda 表达式中使用捕获的指针
        //        QMessageBox::warning(nullptr, "警告", "connect YES!: ");
        int a,b,c;
        a = C1->currentIndex();
        b = C2->currentIndex();
        c = C3->currentIndex();
        f1->refresh1(ui->widget_1_1, j, a, b, c);
        f3->refresh3(ui->widget_1_1, j, a, b, c);
        if(j!=5){
            f2->refresh2(ui->widget_1_1, j, a, b, c);
        }
    });

}


//    connect(ui->checkBox_1, &QCheckBox::toggled, [=]() {
//        // 在 lambda 表达式中使用捕获的指针
////        QMessageBox::warning(nullptr, "警告", "connect YES!: ");
//        int a,b,c;
//        a = ui->comboBox_1A->currentIndex();
//        b = ui->comboBox_1B->currentIndex();
//        c = ui->comboBox_1C->currentIndex();
//        f1->refresh1(ui->widget_1_1, 1, a, b, c);


//    });
//    connect(ui->checkBox_2, &QCheckBox::toggled, [=]() {
//        // 在 lambda 表达式中使用捕获的指针
//        int a,b,c;
//        a = ui->comboBox_2A->currentIndex();
//        b = ui->comboBox_2B->currentIndex();
//        c = ui->comboBox_2C->currentIndex();
//        f1->refresh1(ui->widget_1_1, 2, a, b, c);


//    });
//    connect(ui->checkBox_3, &QCheckBox::toggled, [=]() {
//        // 在 lambda 表达式中使用捕获的指针
//        int a,b,c;
//        a = ui->comboBox_3A->currentIndex();
//        b = ui->comboBox_3B->currentIndex();
//        c = ui->comboBox_3C->currentIndex();
//        f1->refresh1(ui->widget_1_1, 3, a, b, c);


//    });
//    connect(ui->checkBox_4, &QCheckBox::toggled, [=]() {
//        // 在 lambda 表达式中使用捕获的指针
//        int a,b,c;
//        a = ui->comboBox_4A->currentIndex();
//        b = ui->comboBox_4B->currentIndex();
//        c = ui->comboBox_4C->currentIndex();
//        f1->refresh1(ui->widget_1_1, 4, a, b, c);


//    });
//    connect(ui->checkBox_5, &QCheckBox::toggled, [=]() {
//        // 在 lambda 表达式中使用捕获的指针
//        int a,b,c;
//        a = ui->comboBox_5A->currentIndex();
//        b = ui->comboBox_5B->currentIndex();
//        c = ui->comboBox_5C->currentIndex();
//        f1->refresh1(ui->widget_1_1, 5, a, b, c);



//    });





}
void signal_ui::slotSocketReadyRead() {

    QByteArray receivedData = m_pTcpClient11->readAll() ;
    QString receivedString = QString(receivedData.trimmed().toHex(' '));
    m_pPlainText->appendPlainText("[in]: " + receivedString);
}

void signal_ui::closeEvent11(QCloseEvent* event) {
    // 关闭之前断开连接
    if (m_pTcpClient11->state() == QAbstractSocket::ConnectedState)
        m_pTcpClient11->disconnectFromHost();
    QMessageBox::StandardButton button = QMessageBox::question(this, QStringLiteral(""), "是否退出?");
    if (button == QMessageBox::StandardButton::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void signal_ui::slotActConnectTriggered11() {
    //  连接到服务器按钮

    QString addr = m_pLineEditIP->text();
    int port1 = m_pSpinBoxPort->value();
    quint16 port = quint16(port1);
    m_pTcpClient11->connectToHost(addr, port);
}



void signal_ui::slotActDisConnectTriggered11() {
    // 断开连接按钮
    if (m_pTcpClient11->state() == QAbstractSocket::ConnectedState) {
        m_pTcpClient11->disconnectFromHost();
        m_pTcpClient11->waitForConnected(2000);

    }
}


void signal_ui::slotActQuitTriggered11() { this->close(); }
void signal_ui::slotConnected11() {

    m_pPlainText->appendPlainText("**已连接到服务器");
    m_pPlainText->appendPlainText("**peer address: " + m_pTcpClient11->peerAddress().toString());
    m_pPlainText->appendPlainText("**peer port: " + QString::number(m_pTcpClient11->peerPort()));
    m_pActConnectServer11->setEnabled(false);
    m_pActDisconnect11->setEnabled(true);

}

void signal_ui::slotDisconnected11() {

    //    Disconnected()信号槽函数
    m_pPlainText->appendPlainText("**已断开与服务器的连接");
    m_pActConnectServer11->setEnabled(true);
    m_pActDisconnect11->setEnabled(false);
}

void signal_ui::slotSocketStateChange11(QAbstractSocket::SocketState socketState) {
    switch (socketState) {
    case QAbstractSocket::UnconnectedState:
        m_pLabSocketState11->setText("socket状态：UnconnectedSate");
        break;
    case QAbstractSocket::HostLookupState:
        m_pLabSocketState11->setText("socket状态：HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        m_pLabSocketState11->setText("socket状态：ConnectingState");
        break;
    case QAbstractSocket::ConnectedState:
        m_pLabSocketState11->setText("socket状态：ConnectedState");
        break;
    case QAbstractSocket::BoundState:
        m_pLabSocketState11->setText("socket状态：BoundState");
        break;
    case QAbstractSocket::ClosingState:
        m_pLabSocketState11->setText("socket状态：ClosingState");
        break;
    case QAbstractSocket::ListeningState:
        m_pLabSocketState11->setText("socket状态：ListeningState");
        break;
    }
}

void signal_ui::begain(){

    QString message11 = "f1 02 1f";
    QByteArray sendData11 = QByteArray::fromHex(message11.toUtf8());
    m_pTcpClient11->write(sendData11);
    m_pPlainText->appendPlainText("[out]: 开始输出");
    t->stop();

}

void signal_ui::stop(){

    QString message = "f1 01 1f";
    m_pPlainText->appendPlainText("[out]: 停止输出");
    QByteArray sendData = QByteArray::fromHex(message.toUtf8());
    m_pTcpClient11->write(sendData);
    ui->loadwave->setEnabled(0);

}

void signal_ui::initedit(){
    for (int i = 1; i <= 16; ++i) {
        QString lineEditName = QString("lineEdit1_%1").arg(i);
        QLineEdit *currentLineEdit = findChild<QLineEdit *>(lineEditName);

        if (currentLineEdit) {
            currentLineEdit->setStyleSheet("QLineEdit { background-color: #ececec; border: none; }");
        }
        // 可以根据需要添加其他样式设置
    }

    ui->frequency->setText("50");

    QLineEdit* currentLineEdit1 = ui->frequency;
    QDoubleValidator* validator = new QDoubleValidator(0, 100.0, 3, currentLineEdit1);
    validator->setNotation(QDoubleValidator::StandardNotation);
    currentLineEdit1->setValidator(validator);






    for (int i = 1; i <= 16; ++i) {
        QString lineEditName = QString("lineEdit_%1_1").arg(i);

        QLineEdit* currentLineEdit = ui->widget_1_1->findChild<QLineEdit*>(lineEditName);
        if (currentLineEdit) {
            QDoubleValidator* validator = new QDoubleValidator(0, 100.0, 4, currentLineEdit);
            validator->setNotation(QDoubleValidator::StandardNotation);
            currentLineEdit->setValidator(validator);

            QObject::connect(currentLineEdit, &QLineEdit::textChanged, [=](const QString &text){
                int pos = 0;
                QString t = text;
                QValidator::State state = validator->validate(t, pos);
                if (state != QValidator::Acceptable) {
                    // 输入不在范围内，弹出对话框提示用户
                    QMessageBox::warning(nullptr, "输入错误", "请输入范围内的数字！(0-100)");
                    // 清空文本框
                    currentLineEdit->clear();
                }
            });
        }

        QString lineEditName1 = QString("lineEdit_%1_2").arg(i);
        QLineEdit* currentLineEdit1 = ui->widget_1_1->findChild<QLineEdit*>(lineEditName1);
        if (currentLineEdit1) {
            QDoubleValidator* validator = new QDoubleValidator(0, 360.0, 4, currentLineEdit1);
            validator->setNotation(QDoubleValidator::StandardNotation);
            currentLineEdit1->setValidator(validator);

            QObject::connect(currentLineEdit1, &QLineEdit::textChanged, [=](const QString &text){
                int pos = 0;
                QString t = text;
                QValidator::State state = validator->validate(t, pos);
                if (state != QValidator::Acceptable) {
                    // 输入不在范围内，弹出对话框提示用户
                    QMessageBox::warning(nullptr, "输入错误", "请输入范围内的数字！(0-360)");
                    // 清空文本框
                    currentLineEdit1->clear();
                }
            });
        }
    }


    int k = 1;
    for(int i = 0; i <= 12; i =i+ 3) {

        QString ComboboxName1 = QString("comboBox_%1A").arg(k);
        QString ComboboxName2 = QString("comboBox_%1B").arg(k);
        QString ComboboxName3 = QString("comboBox_%1C").arg(k);
        k=k+1;
        QComboBox* c1 = ui->widget_3->findChild<QComboBox*>(ComboboxName1);
        QComboBox* c2 = ui->widget_3->findChild<QComboBox*>(ComboboxName2);
        QComboBox* c3 = ui->widget_3->findChild<QComboBox*>(ComboboxName3);
        qDebug() << "found! |"+ComboboxName1+"|"+ComboboxName2+"|"+ComboboxName3;

        if (c1 && c2 && c3) {
            c1->setCurrentIndex(i);
            c2->setCurrentIndex(i + 1);
            c3->setCurrentIndex(i + 2);

        } else {
            qDebug() << "One or more QComboBox not found! |"+ComboboxName1+"|"+ComboboxName2+"|"+ComboboxName3;
        }
    }

    QWidget::setTabOrder(ui->lineEdit_1_1, ui->lineEdit_1_2);
    QWidget::setTabOrder(ui->lineEdit_1_2, ui->lineEdit_2_1);

    QWidget::setTabOrder(ui->lineEdit_2_1, ui->lineEdit_2_2);
    QWidget::setTabOrder(ui->lineEdit_2_2, ui->lineEdit_3_1);

    QWidget::setTabOrder(ui->lineEdit_3_1, ui->lineEdit_3_2);
    QWidget::setTabOrder(ui->lineEdit_3_2, ui->lineEdit_4_1);

    QWidget::setTabOrder(ui->lineEdit_4_1, ui->lineEdit_4_2);
    QWidget::setTabOrder(ui->lineEdit_4_2, ui->lineEdit_5_1);

    QWidget::setTabOrder(ui->lineEdit_5_1, ui->lineEdit_5_2);
    QWidget::setTabOrder(ui->lineEdit_5_2, ui->lineEdit_6_1);

    QWidget::setTabOrder(ui->lineEdit_6_1, ui->lineEdit_6_2);
    QWidget::setTabOrder(ui->lineEdit_6_2, ui->lineEdit_7_1);

    QWidget::setTabOrder(ui->lineEdit_7_1, ui->lineEdit_7_2);
    QWidget::setTabOrder(ui->lineEdit_7_2, ui->lineEdit_8_1);

    QWidget::setTabOrder(ui->lineEdit_8_1, ui->lineEdit_8_2);
    QWidget::setTabOrder(ui->lineEdit_8_2, ui->lineEdit_9_1);

    QWidget::setTabOrder(ui->lineEdit_9_1, ui->lineEdit_9_2);
    QWidget::setTabOrder(ui->lineEdit_9_2, ui->lineEdit_10_1);

    QWidget::setTabOrder(ui->lineEdit_10_1, ui->lineEdit_10_2);
    QWidget::setTabOrder(ui->lineEdit_10_2, ui->lineEdit_11_1);

    QWidget::setTabOrder(ui->lineEdit_11_1, ui->lineEdit_11_2);
    QWidget::setTabOrder(ui->lineEdit_11_2, ui->lineEdit_12_1);

    QWidget::setTabOrder(ui->lineEdit_12_1, ui->lineEdit_12_2);
    QWidget::setTabOrder(ui->lineEdit_12_2, ui->lineEdit_13_1);

    QWidget::setTabOrder(ui->lineEdit_13_1, ui->lineEdit_13_2);
    QWidget::setTabOrder(ui->lineEdit_13_2, ui->lineEdit_14_1);

    QWidget::setTabOrder(ui->lineEdit_14_1, ui->lineEdit_14_2);
    QWidget::setTabOrder(ui->lineEdit_14_2, ui->lineEdit_15_1);

    QWidget::setTabOrder(ui->lineEdit_15_1, ui->lineEdit_15_2);
    QWidget::setTabOrder(ui->lineEdit_15_2, ui->lineEdit_16_1);

    QWidget::setTabOrder(ui->lineEdit_16_1, ui->lineEdit_16_2);
    QWidget::setTabOrder(ui->lineEdit_16_2, ui->frequency);


    const int rowCount =16;
        const int columnCount =2;

    //    ui->lineEdit_1->setValidator(new QRegExpValidator(QRegExp("^-?(12|[1-2]?\\d(\\.\\d{1,6})?)$")));
    QString textContents[rowCount][columnCount] = {
        {"1", "0"},
        {"1", "60"},
        {"1", "180"},
        {"2", "60"},
        {"2", "0"},
        {"2", "90"},
        {"0", "0"},
        {"0", "0"},
        {"0", "0"},
        {"2", "90"},
        {"2", "180"},
        {"2", "270"},
        {"0", "0"},
        {"0", "0"},
        {"0", "0"},
        {"0", "0"}
    };



    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            QString lineEditName = QString("lineEdit_%1_%2").arg(i + 1).arg(j + 1);
            QLineEdit* lineEdit = ui->widget_1_1->findChild<QLineEdit*>(lineEditName);

            if (lineEdit) {
                lineEdit->setText(textContents[i][j]);
            }
        }
    }
}



void signal_ui::slotssignal()
{
    static int commandIndex = 1; // 用于跟踪当前指令索引的静态变量
    QString message = "";
    if (m_pTcpClient11->state() == QAbstractSocket::ConnectedState) {



        int channel = commandIndex - 1;

        int n;
        QString amplitude;
        QString phase;
        //精校系数
        QString coe;
        QString frequency = ui->frequency->text();
        swicha(commandIndex, amplitude, phase,n,coe);
        qfloat16 rat = transrat(n);
        //QMessageBox::warning(nullptr, "警告", QString::number(rat));

        QString message = "fe ";
        //通道数
        QString schannel = tohex(QString::number(channel));
        //            if(schannel == "0A")
        //            {
        //                schannel ="0A";
        //            }
        message.append(schannel);
        //频率
        frequency = tohex(frequency);
        message.append(frequency);
        //幅值
        qfloat16 num = amplitude.toFloat();

        amplitude = QString::number(int((num/rat)*1000000*sqrt(2)));


        int amp =amplitude.toInt();

        if(amp > 65535){

            amplitude = tohex(amplitude);


        }
        else if (amp>255) {
            message.append("00 ");
            amplitude = tohex(amplitude);
        }
        else {
            message.append("00 00 ");
            amplitude = tohex(amplitude);
        }
        message.append(amplitude);

        //            if (amplitude.toInt() > 255) {
        //                amplitude = tohex(amplitude);
        //                message.append(amplitude);
        //            }
        //            else {
        //                message.append("00 ");
        //                amplitude = tohex(amplitude);
        //                message.append(amplitude);
        //            }

        message.append("00 00 00 00 00 00 00 00 00 00 00 00 00 ");

        if (phase.toInt() <= 255) {
            message.append("00 ");
            phase = tohex(phase);
            message.append(phase);
        } else {
            phase = tohex(phase);
            message.append(phase);
        }


        double coen = coe.toDouble() ;
        coe = QString::number(coen*10000);
        //QMessageBox::warning(nullptr, "警告", "double:"+ coe);
        if (coe.toInt() <= 255) {
            message.append("00 ");
            coe = tohex(coe);
            message.append(coe);
        } else {
            coe = tohex(coe);
            message.append(coe);
        }
        message.append("ef");
        QByteArray sendData = QByteArray::fromHex(message.toUtf8());
        m_pTcpClient11->write(sendData);
        m_pPlainText->appendPlainText("[out]: 通道" + QString::number( channel+1)+"数据已下发");
        //             m_pPlainText->appendPlainText("[out]: 通道" + message);


        commandIndex++;

        if (commandIndex <= 16) {
            // 如果还有更多的指令要发送，设置延迟并继续下一条指令
            m_pCommandTimer->start(250); // 设置延迟时间，单位为毫秒（在此示例中为1秒）
        } else {
            // 所有指令都已发送，重置索引并停止定时器
            commandIndex = 1;

            m_pCommandTimer->stop();
            QString message11 = "f1 02 1f";
            t->start(250);

            ui->loadwave->setEnabled(1) ;
            ui->sendwave->setEnabled(1);

        }
    }
}

QString signal_ui::tohex(const QString &input) {
    bool ok = false;
    int num = input.toInt(&ok);
    //QMessageBox::warning(nullptr, "警告", QString::number(input.toInt())+input);
    if (ok) {
        QString hexString = QString::number(num, 16).toUpper();  // 转换为大写字母的16进制字符串

        // 补零使结果为两位
        if (hexString.size() % 2 != 0) {
            hexString = "0" + hexString;
        }
        //        QMessageBox::warning(nullptr, "警告", "double:"+ hexString);

        // 将结果按两位两位分隔并以空格连接
        QString result;
        for (int i = 0; i < hexString.size(); i += 2) {
            result += hexString.mid(i, 2) + " ";
        }

        // 移除末尾的空格
        //        result = result.trimmed();

        return result;
    } else {
        // 如果转换失败，可以返回一个默认值或者处理错误的逻辑
        return "Invalid Input";
    }
}


qfloat16 signal_ui::transrat(int index) {
    qfloat16 rat = 0;

    switch (index) {
    case 0: rat = qfloat16(5.0 / 0.23);
        break;
    case 1: rat = qfloat16(1.0 / 0.23);
        break;
    case 2: rat = qfloat16(5.0 / 2.917);
        break;
    case 3: rat = qfloat16(1.0 / 2.917);
        break;
    case 4: rat = qfloat16(100 / 4);
        break;
    case 5: rat = qfloat16(200 / 4);
        break;
    case 6: rat = qfloat16(57.7 / 3.5);
        break;
    case 7: rat = qfloat16(300 / 2.333);
        break;
    case 8: rat = qfloat16(5.0 / 0.35);
        break;
    case 9: rat = qfloat16(1.0 / 0.35);
        break;
    case 10: rat = qfloat16(5.0 / 0.167);
        break;
    case 11: rat = qfloat16(1.0 / 0.167);
        break;
    case 12: rat = *Spare1;
        break;
    case 13: rat = *Spare2;
        break;
    case 14: rat = *Spare3;
        break;
    case 15: rat = *Spare4;
        break;
    case 16: rat = *Spare5;
        break;

    }

    return rat;
}

void signal_ui::swicha(const int i, QString &amplitude, QString &phase , int &n ,QString &num){
    switch (i) {

    case 1:{
        amplitude = ui->lineEdit_1_1->text();
        phase = ui->lineEdit_1_2->text();
        n = ui->comboBox_1->currentIndex() ;
        num = ui->doubleSpinBox_1->text();
        break;
    }
    case 2:{
        amplitude = ui->lineEdit_2_1->text();
        phase = ui->lineEdit_2_2->text();
        n = ui->comboBox_2->currentIndex() ;
        num = ui->doubleSpinBox_2->text();
        break;
    }
    case 3:{
        amplitude = ui->lineEdit_3_1->text();
        phase = ui->lineEdit_3_2->text();
        n = ui->comboBox_3->currentIndex() ;
        num = ui->doubleSpinBox_3->text();
        break;
    }
    case 4:{
        amplitude = ui->lineEdit_4_1->text();
        phase = ui->lineEdit_4_2->text();
        n = ui->comboBox_4->currentIndex() ;
        num = ui->doubleSpinBox_4->text();
        break;
    }
    case 5:{
        amplitude = ui->lineEdit_5_1->text();
        phase = ui->lineEdit_5_2->text();
        n = ui->comboBox_5->currentIndex() ;
        num = ui->doubleSpinBox_5->text();
        break;
    }
    case 6:{
        amplitude = ui->lineEdit_6_1->text();
        phase = ui->lineEdit_6_2->text();
        n = ui->comboBox_6->currentIndex() ;
        num = ui->doubleSpinBox_6->text();
        break;
    }
    case 7:{
        amplitude = ui->lineEdit_7_1->text();
        phase = ui->lineEdit_7_2->text();
        n = ui->comboBox_7->currentIndex() ;
        num = ui->doubleSpinBox_7->text();
        break;
    }
    case 8:{
        amplitude = ui->lineEdit_8_1->text();
        phase = ui->lineEdit_8_2->text();
        n = ui->comboBox_8->currentIndex() ;
        num = ui->doubleSpinBox_8->text();
        break;
    }
    case 9:{
        amplitude = ui->lineEdit_9_1->text();
        phase = ui->lineEdit_9_2->text();
        n = ui->comboBox_9->currentIndex() ;
        num = ui->doubleSpinBox_9->text();
        break;
    }
    case 10:{
        amplitude = ui->lineEdit_10_1->text();
        phase = ui->lineEdit_10_2->text();
        n = ui->comboBox_10->currentIndex() ;
        num = ui->doubleSpinBox_10->text();
        break;
    }
    case 11:{
        amplitude = ui->lineEdit_11_1->text();
        phase = ui->lineEdit_11_2->text();
        n = ui->comboBox_11->currentIndex() ;
        num = ui->doubleSpinBox_11->text();
        break;
    }
    case 12:{
        amplitude = ui->lineEdit_12_1->text();
        phase = ui->lineEdit_12_2->text();
        n = ui->comboBox_12->currentIndex() ;
        num = ui->doubleSpinBox_12->text();
        break;
    }
    case 13:{
        amplitude = ui->lineEdit_13_1->text();
        phase = ui->lineEdit_13_2->text();
        n = ui->comboBox_13->currentIndex() ;
        num = ui->doubleSpinBox_13->text();
        break;
    }
    case 14:{
        amplitude = ui->lineEdit_14_1->text();
        phase = ui->lineEdit_14_2->text();
        n = ui->comboBox_14->currentIndex() ;
        num = ui->doubleSpinBox_14->text();
        break;
    }
    case 15:{
        amplitude = ui->lineEdit_15_1->text();
        phase = ui->lineEdit_15_2->text();
        n = ui->comboBox_15->currentIndex() ;
        num = ui->doubleSpinBox_15->text();
        break;
    }
    case 16:{
        amplitude = ui->lineEdit_16_1->text();
        phase = ui->lineEdit_16_2->text();
        n = ui->comboBox_16->currentIndex() ;
        num = ui->doubleSpinBox_16->text();
        break;
    }
    }
}

void signal_ui::saveConfigToFile(const QString& filePath, const QString& comboBoxText, const QString& lineEditText1, const QString& lineEditText2, int lineNumber) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text )) {
        QTextStream out(&file);
        out.seek(0);
        for (int i = 0; i  < (lineNumber-1)*3; i++) {
            out.readLine(); // Skip lines before the specified line number
        }
        out << comboBoxText << "\n";
        out << lineEditText1 << "\n";
        out << lineEditText2 << "\n";

        file.close();
    }
}

void signal_ui::loadConfigFromFile(const QString& filePath, QComboBox* comboBox, QLineEdit* lineEdit1, QLineEdit* lineEdit2, int lineNumber) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        for (int i = 0; i < (lineNumber-1)*3; i++) {
            in.readLine(); // Skip lines before the specified line number
        }

        QString comboBoxText = in.readLine();
        QString lineEditText1 = in.readLine();
        QString lineEditText2 = in.readLine();

        file.close();

        if (!comboBoxText.isEmpty()) {
            int index = comboBox->findText(comboBoxText);
            if (index != -1) {
                comboBox->setCurrentIndex(index);
            }
        }

        lineEdit1->setText(lineEditText1);
        lineEdit2->setText(lineEditText2);
        for (int i = 1; i <= 16; ++i) {
            QString lineEditName = QString("lineEdit_%1_1").arg(i);

            QLineEdit* currentLineEdit = ui->widget_1_1->findChild<QLineEdit*>(lineEditName);
            if (currentLineEdit) {
                QDoubleValidator* validator = new QDoubleValidator(0, 100.0, 4, currentLineEdit);
                validator->setNotation(QDoubleValidator::StandardNotation);
                currentLineEdit->setValidator(validator);
            }


            QString lineEditName1 = QString("lineEdit_%1_2").arg(i);
            QLineEdit* currentLineEdit1 = ui->widget_1_1->findChild<QLineEdit*>(lineEditName1);
            if (currentLineEdit1) {
                QDoubleValidator* validator = new QDoubleValidator(0, 360.0, 4, currentLineEdit1);
                validator->setNotation(QDoubleValidator::StandardNotation);
                currentLineEdit1->setValidator(validator);
            }
        }
    }
}

void signal_ui::conSandL() {
    QObject::connect(m_pActSavecon, &QAction::triggered, [&]() {
        // Save configurations to file
        QFile file("config.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
        file.close();

        // Save configurations for each channel
        for (int i = 1; i <= 16; ++i) {
            QString lineEditName1 = QString("lineEdit_%1_1").arg(i);
            QString lineEditName2 = QString("lineEdit_%1_2").arg(i);
            QString comboBoxName = QString("comboBox_%1").arg(i);

            QLineEdit* currentLineEdit1 = ui->widget_1_1->findChild<QLineEdit*>(lineEditName1);
            QLineEdit* currentLineEdit2 = ui->widget_1_1->findChild<QLineEdit*>(lineEditName2);
            QComboBox* currentComboBox = ui->widget_1_1->findChild<QComboBox*>(comboBoxName);

            saveConfigToFile("config.txt", currentComboBox->currentText(), currentLineEdit1->text(), currentLineEdit2->text(), i);
        }
    });

    QObject::connect(m_pActLoadcon, &QAction::triggered, [&]() {
        // Load configurations from file
        for (int i = 1; i <= 16; ++i) {
            QString lineEditName1 = QString("lineEdit_%1_1").arg(i);
            QString lineEditName2 = QString("lineEdit_%1_2").arg(i);
            QString comboBoxName = QString("comboBox_%1").arg(i);

            QLineEdit* currentLineEdit1 = ui->widget_1_1->findChild<QLineEdit*>(lineEditName1);
            QLineEdit* currentLineEdit2 = ui->widget_1_1->findChild<QLineEdit*>(lineEditName2);
            QComboBox* currentComboBox = ui->widget_1_1->findChild<QComboBox*>(comboBoxName);

            loadConfigFromFile("config.txt", currentComboBox, currentLineEdit1, currentLineEdit2, i);
        }
    });
}


void signal_ui::SwitchCo(int ){

    int a = m_pComBox->currentIndex();
    f1->hide();
    f2->hide();
    f3->hide();
    gl->hide();
    // 根据 ComboBox 的选择显示对应的预备界面
    switch (a)
    {
    case 0:
        f1->show();
        ui->checkBox_1->setDisabled(false);
        ui->checkBox_2->setDisabled(false);
        ui->checkBox_3->setDisabled(false);
        ui->checkBox_4->setDisabled(false);
        ui->checkBox_5->setDisabled(false);
        break;
    case 1:
        f2->show();
        ui->checkBox_1->setDisabled(false);
        ui->checkBox_2->setDisabled(false);
        ui->checkBox_3->setDisabled(false);
        ui->checkBox_4->setDisabled(false);
        ui->checkBox_5->setDisabled(true);
        break;
    case 2:
        f3->show();
        ui->checkBox_1->setDisabled(false);
        ui->checkBox_2->setDisabled(false);
        ui->checkBox_3->setDisabled(false);
        ui->checkBox_4->setDisabled(false);
        ui->checkBox_5->setDisabled(false);
        break;
    case 3:
        gl->show();
        ui->checkBox_1->setDisabled(true);
        ui->checkBox_2->setDisabled(true);
        ui->checkBox_3->setDisabled(true);
        ui->checkBox_4->setDisabled(true);
        ui->checkBox_5->setDisabled(true);

        break;
    }
    return;
}

void signal_ui::showbianbi(){
        bb->show();
}





#include "load.h"
#include "ui_load.h"

load::load(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::load)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("TCP客户端"));
    ui->menuBar->hide();

    // QSS样式
    loadStyleFile();

    //工具栏
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->mainToolBar->setMinimumHeight(50);
    m_pActConnectServer = new QAction(QIcon(":/new/prefix1/res/链接.png"), QStringLiteral("连接服务器"), this);
    m_pActDisconnect = new QAction(QIcon(":/new/prefix1/res/断开链接.png"), QStringLiteral("断开连接"), this);
    m_pActClear = new QAction(QIcon(":/new/prefix1/res/清空数据.png"), QStringLiteral("清空文本框"), this);
    m_pActQuit = new QAction(QIcon(":/new/prefix1/res/退出.png"), QStringLiteral("退出"), this);
    ui->mainToolBar->addAction(m_pActConnectServer);
    ui->mainToolBar->addAction(m_pActDisconnect);
    ui->mainToolBar->addAction(m_pActClear);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(m_pActQuit);

    //布局
    m_pCentralWidget = new QWidget(this);
    m_pLabel1 = new QLabel(QStringLiteral("服务器地址"), m_pCentralWidget);
    m_pLabel2 = new QLabel(QStringLiteral("端口"), m_pCentralWidget);
    m_pLineEditIP = new QLineEdit(m_pCentralWidget);
    m_pSpinBoxPort = new QSpinBox(m_pCentralWidget);
    m_pSpinBoxPort->setMinimum(1);
    m_pSpinBoxPort->setMaximum(65535);
    QHBoxLayout* HLay1 = new QHBoxLayout();
    HLay1->addWidget(m_pLabel1, 2);
    HLay1->addWidget(m_pLineEditIP, 6);
    HLay1->addWidget(m_pLabel2, 2, Qt::AlignRight);
    HLay1->addWidget(m_pSpinBoxPort, 3);
    m_pLineEdit = new QLineEdit(m_pCentralWidget);
    m_pBtnSend = new QPushButton(QStringLiteral("发送消息"), m_pCentralWidget);
    QHBoxLayout* HLay2 = new QHBoxLayout();
    HLay2->addWidget(m_pLineEdit, 10);
    HLay2->addWidget(m_pBtnSend, 2);
    m_pPlainText = new QPlainTextEdit(m_pCentralWidget);
    QGridLayout* GridLayout = new QGridLayout(m_pCentralWidget);
    GridLayout->addLayout(HLay1, 0, 0);
    GridLayout->addLayout(HLay2, 1, 0);
    GridLayout->addWidget(m_pPlainText);
    this->setCentralWidget(m_pCentralWidget);

    //状态栏
    m_pLabSocketState = new QLabel(this);
    m_pLabSocketState->setText(QStringLiteral("socket状态："));
    ui->statusBar->addWidget(m_pLabSocketState);
    m_pLabSocketState->setMinimumWidth(150);

    QString localIP = getLocalIP();
    this->setWindowTitle(this->windowTitle() + "---本机IP：" + localIP);
    m_pLineEditIP->setText(localIP);

    m_pTcpClient = new QTcpSocket(this);
    connect(m_pActConnectServer, &QAction::triggered, this, &MainWindow::slotActConnectTriggered);
    connect(m_pActDisconnect, &QAction::triggered, this, &MainWindow::slotActDisConnectTriggered);
    connect(m_pActClear, &QAction::triggered, this, &MainWindow::slotActClearTriggered);
    connect(m_pActQuit, &QAction::triggered, this, &MainWindow::slotActQuitTriggered);
    connect(m_pBtnSend, &QPushButton::clicked, this, &MainWindow::slotBtnSendClicked);
    connect(m_pTcpClient, &QTcpSocket::connected, this, &MainWindow::slotConnected);
    connect(m_pTcpClient, &QTcpSocket::disconnected, this, &MainWindow::slotDisconnected);
    connect(m_pTcpClient, &QTcpSocket::stateChanged, this, &MainWindow::slotSocketStateChange);
    connect(m_pTcpClient, &QTcpSocket::readyRead, this, &MainWindow::slotSocketReadyRead);
}

load::~load()
{
    delete ui;
}
void load::closeEvent(QCloseEvent* event) {
    //关闭之前断开连接
    if (m_pTcpClient->state() == QAbstractSocket::ConnectedState)
        m_pTcpClient->disconnectFromHost();
    QMessageBox::StandardButton button = QMessageBox::question(this, QStringLiteral(""), "是否退出?");
    if (button == QMessageBox::StandardButton::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}
void load::slotActConnectTriggered() {
    //连接到服务器按钮
    int currentIndex = ui->ip->currentIndex();
    // 根据索引获取当前选定的文本
    QString addr = ui->ip->itemText(currentIndex);
    bool conversionOK;
    int currentIndex1 = ui->host->currentIndex();
    quint16 port = ui->host->itemText(currentIndex1).toUInt(&conversionOK);
    m_pTcpClient->connectToHost(addr, port);
}


void load::slotActDisConnectTriggered() {
    //断开连接按钮
    if (m_pTcpClient->state() == QAbstractSocket::ConnectedState) {
        m_pTcpClient->disconnectFromHost();
    }
}
void load::slotActQuitTriggered() { this->close(); }

void load::slotConnected() {
    // Connected()信号槽函数
    m_pPlainText->appendPlainText("**已连接到服务器");
    m_pPlainText->appendPlainText("**peer address: " + m_pTcpClient->peerAddress().toString());
    m_pPlainText->appendPlainText("**peer port: " + QString::number(m_pTcpClient->peerPort()));
    m_pActConnectServer->setEnabled(false);
    m_pActDisconnect->setEnabled(true);
}






























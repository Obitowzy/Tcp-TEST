#include "mainwindow.h"
#include <QAction>
#include <QTableWidget>
#include <QCheckBox>
#include "ui_mainwindow.h"
#include "checkboxdelegate.h"
#include "QPushButton"
#include <QMessageBox>





MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("TCP客户端"));
    ui->menubar->hide();

//  添加QSS样式
//  loadStyleFile();

//  工具栏
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->mainToolBar->setMinimumHeight(50);
    m_pActConnectServer = new QAction(QIcon(":/new/prefix1/QSS_IMG/object-select-symbolic.symbolic.png"), QStringLiteral("创建服务连接"), this);
    m_pActDisconnect = new QAction(QIcon(":/new/prefix1/res/断开链接.png"), QStringLiteral("断开连接"), this);
    m_pActClear = new QAction(QIcon(":/new/prefix1/res/清空数据.png"), QStringLiteral("清空文本框"), this);
    m_pActQuit = new QAction(QIcon(":/new/prefix1/res/退出.png"), QStringLiteral("退出"), this);

    ui->mainToolBar->addAction(m_pActConnectServer);
//  ui->mainToolBar->addAction(m_pActDisconnect);
    ui->mainToolBar->addAction(m_pActClear);

    ui->mainToolBar->addSeparator();
//    ui->mainToolBar->addAction(m_pActQuit);

//  布局
    m_pCentralWidget = new QWidget(this);
    m_pCentralWidget->setGeometry(0, 50, 800, 150);
    m_pLabel1 = new QLabel(QStringLiteral("服务器地址"), m_pCentralWidget);
    m_pLabel2 = new QLabel(QStringLiteral("端口"), m_pCentralWidget);
    m_pLineEditIP = new QLineEdit(m_pCentralWidget);
    m_pSpinBoxPort = new QSpinBox(m_pCentralWidget);
    m_pSpinBoxPort->setMinimum(1);
    m_pSpinBoxPort->setMaximum(65535);
    m_pLineEditIP->setText("192.168.15.2");
    m_pSpinBoxPort->setValue(5000);

    QHBoxLayout* HLay1 = new QHBoxLayout();
    HLay1->addWidget(m_pLabel1, 2);
    HLay1->addWidget(m_pLineEditIP, 6);
    HLay1->addWidget(m_pLabel2, 2, Qt::AlignRight);
    HLay1->addWidget(m_pSpinBoxPort, 3);

    table = new QTableWidget(0, 33, m_pCentralWidget);
    table->setEditTriggers(QAbstractItemView::DoubleClicked);

    QStringList columnHeaders;
    columnHeaders << "全1" << "全0" << "全反";
    QStringList headerLabels;
    for (int col = 3; col < table->columnCount(); ++col) {
        headerLabels << QString::number(col - 2);
    }

    columnHeaders.append(headerLabels);
    table->setHorizontalHeaderLabels(columnHeaders);
    table->resizeRowsToContents();
    table->resizeColumnsToContents();



    m_pPlainText = new QPlainTextEdit(m_pCentralWidget);
    m_pPlainText->setReadOnly(true);

//  TCP候选
    QHBoxLayout* HLay2 = new QHBoxLayout();
    table_1 = new QTableWidget(0, 5, m_pCentralWidget);

    HLay2->addWidget(table_1);
    QStringList columnHeaders1;
    columnHeaders1 << "服务器地址" << "端口号" << "连接状态" <<"删除操作" <<"状态";
    table_1->setHorizontalHeaderLabels(columnHeaders1);
    table_1->resizeRowsToContents();
    table_1->resizeColumnsToContents();


    QGridLayout* GridLayout = new QGridLayout(m_pCentralWidget);
    GridLayout->addLayout(HLay1, 0, 0);
    GridLayout->addLayout(HLay2, 1, 0);

    GridLayout->addWidget(table, 2, 0);
    GridLayout->addWidget(m_pPlainText, 3, 0);
    GridLayout->setRowStretch(1, 2);
    GridLayout->setRowStretch(3, 2);
    GridLayout->setRowStretch(2, 5);
    this->setCentralWidget(m_pCentralWidget);

//  状态栏
    m_pLabSocketState = new QLabel(this);
    m_pLabSocketState->setText(QStringLiteral("socket状态："));
    ui->statusbar->addWidget(m_pLabSocketState);
    m_pLabSocketState->setMinimumWidth(150);

    QString localIP = getLocalIP();
    this->setWindowTitle(this->windowTitle() + "---本机IP：" + localIP);
    inittabset();
//    table_1->resizeRowsToContents();
//    table_1->resizeColumnsToContents();
    inittabtrip();
//    table->resizeRowsToContents();
//    table->resizeColumnsToContents();


    tcp.m_pTcpClient  = new QTcpSocket(this);
    tcp.m_pTcpClient1 = new QTcpSocket(this);
    tcp.m_pTcpClient2 = new QTcpSocket(this);
    tcp.m_pTcpClient3 = new QTcpSocket(this);
    tcp.m_pTcpClient4 = new QTcpSocket(this);
    tcp.m_pTcpClient5 = new QTcpSocket(this);


    connectTcp(tcp.m_pTcpClient);
    connectTcp(tcp.m_pTcpClient1);
    connectTcp(tcp.m_pTcpClient2);
    connectTcp(tcp.m_pTcpClient3);
    connectTcp(tcp.m_pTcpClient4);
    connectTcp(tcp.m_pTcpClient5);

    connect(table, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onItemClicked(QTableWidgetItem*)));
    connect(m_pActConnectServer, &QAction::triggered, this, &MainWindow::inittabset);
    connect(m_pActConnectServer, &QAction::triggered, this, &MainWindow::inittabtrip);
//  connect(m_pActConnectServer, &QAction::triggered, this, &MainWindow::slotActConnectTriggered);
    connect(m_pActDisconnect, &QAction::triggered, this, &MainWindow::slotActDisConnectTriggered);
    connect(m_pActClear, &QAction::triggered, this, &MainWindow::slotActClearTriggered);
    connect(m_pActQuit, &QAction::triggered, this, &MainWindow::slotActQuitTriggered);

}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::connectTcp(QTcpSocket* t){

    connect(t, &QTcpSocket::connected, this, &MainWindow::slotConnected);
    connect(t, &QTcpSocket::disconnected, this, &MainWindow::slotDisconnected);
    connect(t, &QTcpSocket::stateChanged, this, &MainWindow::slotSocketStateChange);

    connect(t, &QTcpSocket::readyRead, [=](){
        MainWindow::slotSocketReadyRead(t);
    });

}
void MainWindow::closeEvent(QCloseEvent* event) {
//    关闭之前断开连接
//    if (tcp.m_pTcpClient->state() == QAbstractSocket::ConnectedState)
//        tcp.m_pTcpClient->disconnectFromHost();
//    QMessageBox::StandardButton button = QMessageBox::question(this, QStringLiteral(""), "是否退出?");
//    if (button == QMessageBox::StandardButton::Yes) {
//        event->accept();
//    } else {
//        event->ignore();
//    }
}

void MainWindow::slotActConnectTriggered() {
//    连接到服务器按钮
//    QString addr = m_pLineEditIP->text();
//    int port1 = m_pSpinBoxPort->value();
//    quint16 port = quint16(port1);
//    tcp.m_pTcpClient->connectToHost(addr, port);
}

void MainWindow::slotActDisConnectTriggered() {
//  断开连接按钮

//    if (tcp.m_pTcpClient->state() == QAbstractSocket::ConnectedState) {
//        tcp.m_pTcpClient->disconnectFromHost();
//        tcp.m_pTcpClient->waitForConnected(2000);
//    }
}

void MainWindow::slotActClearTriggered() { m_pPlainText->clear(); }

void MainWindow::slotActQuitTriggered() { this->close(); }
//  需要改👇
void MainWindow::slotConnected() {
     //Connected()信号槽函数
     QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

     m_pPlainText->appendPlainText("**已连接到服务器");
     m_pPlainText->appendPlainText("**peer address: " + socket->peerAddress().toString());
     m_pPlainText->appendPlainText("**peer port: " + QString::number(socket->peerPort()));


//    m_pActConnectServer->setEnabled(false);
//    m_pActDisconnect->setEnabled(true);
}

void MainWindow::slotDisconnected() {
//    Disconnected()信号槽函数
      m_pPlainText->appendPlainText("**已断开与服务器的连接");

//    m_pActConnectServer->setEnabled(true);
//    m_pActDisconnect->setEnabled(false);
}

void MainWindow::slotSocketStateChange(QAbstractSocket::SocketState socketState) {
    switch (socketState) {
        case QAbstractSocket::UnconnectedState:
            m_pLabSocketState->setText("socket状态：UnconnectedSate");
            break;
        case QAbstractSocket::HostLookupState:
            m_pLabSocketState->setText("socket状态：HostLookupState");
            break;
        case QAbstractSocket::ConnectingState:
            m_pLabSocketState->setText("socket状态：ConnectingState");
            break;
        case QAbstractSocket::ConnectedState:
            m_pLabSocketState->setText("socket状态：ConnectedState");
            break;
        case QAbstractSocket::BoundState:
            m_pLabSocketState->setText("socket状态：BoundState");
            break;
        case QAbstractSocket::ClosingState:
            m_pLabSocketState->setText("socket状态：ClosingState");
            break;
        case QAbstractSocket::ListeningState:
            m_pLabSocketState->setText("socket状态：ListeningState");
            break;
    }
}

void MainWindow::slotBtnSendClicked() {
    //发送数据
//    QString msg = m_pLineEdit->text();
//    m_pPlainText->appendPlainText("[out]: " + msg);
//    m_pLineEdit->clear();
//    m_pLineEdit->setFocus();
//    QByteArray sendData = QByteArray::fromHex(msg.toUtf8());
//    /*QByteArray sendDataq=msg.toUtf8();*///QString转换为QByteArray
//    /*sendData=sendData.toHex(' ').toUpper();*///转换成QByteArray -> 转换成16进制数，按空格分开
//    sendData.append('\n');
//    tcp.m_pTcpClient->write(sendData);
}

void MainWindow::slotSocketReadyRead(QTcpSocket* t) {

    while (t->canReadLine()) {
        QByteArray receivedData = t->readAll();
        QString receivedString = QString(receivedData.trimmed().toHex(' '));
        m_pPlainText->appendPlainText("[in]: " + receivedString);
    }


}

QString MainWindow::getLocalIP() {
    QString hostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString localIP = "";
    QList<QHostAddress> addrList = hostInfo.addresses();
    if (!addrList.isEmpty()) {
        for (int i = 0; i < addrList.size(); i++) {
            QHostAddress aHost = addrList.at(i);
            if (aHost.protocol() == QAbstractSocket::IPv4Protocol) {
                localIP = aHost.toString();
                break;
            }
        }
    }
    return localIP;
}

void MainWindow::loadStyleFile() {
    QFile file(":/new/prefix1/QSS.git/trunk/MacOS.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    this->setStyleSheet(styleSheet);
    file.close();
}
//开入全0
void MainWindow::slotsetzore(int row) {

   // QMessageBox::warning(nullptr, "警告", QString::number(row));
    QTcpSocket * Q =  reTcpback3(row);
    // 检查套接字是否已连接
    if (Q->state() == QAbstractSocket::ConnectedState) {
        // 发送数据
        QString msg = "fe f0 00 ef";
        m_pPlainText->appendPlainText("开入 全0" );
        m_pPlainText->appendPlainText("[out]: " + msg);
        QByteArray sendData = QByteArray::fromHex(msg.toUtf8());
        sendData.append('\n');
        Q->write(sendData);
        for (int i = row ; i <= row + 1; i ++) {
            for (int col = 3; col < 33; col++)
            {
                table->item(i,col)->setCheckState(Qt::Unchecked);
            }

        }



    } else {
        m_pPlainText->appendPlainText("TCP 未连接 ");
        return;
    }
}

//开入全1
void MainWindow::slotsetone(int row) {


    QTcpSocket * Q = reTcpback3(row);
    // 发送数据
    if (Q->state() == QAbstractSocket::ConnectedState){
        QString msg = "fe f1 00 ef";
        m_pPlainText->appendPlainText("开入 全1" );
        m_pPlainText->appendPlainText("[out]: " + msg);
        QByteArray sendData = QByteArray::fromHex(msg.toUtf8());
        sendData.append('\n');
        Q->write(sendData);

        for (int i = row ; i <= row + 1; i ++) {
            for (int col = 3; col < 33; col++)
            {
                table->item(i,col)->setCheckState(Qt::Checked);
            }

        }


    }
    else {
        m_pPlainText->appendPlainText("TCP 未连接 ");
        return;
    }
}
void MainWindow::slotsettriggered(int row){

    QTcpSocket * Q;
    Q = reTcpback3(row);
    if (Q->state() == QAbstractSocket::ConnectedState){
        QString msg = "fe f2 00 ef";
        m_pPlainText->appendPlainText("开入 全翻转" );
        m_pPlainText->appendPlainText("[out]: " + msg);
        QByteArray sendData = QByteArray::fromHex(msg.toUtf8());
        sendData.append('\n');
        Q->write(sendData);

        for (int i = row; i <= row+1; i++) {
            for (int col = 3; col < 33; col++)
            {
                if(table->item(i,col)->checkState() == Qt::Checked){

                    table->item(i,col)->setCheckState(Qt::Unchecked);
                }
                else {
                    table->item(i,col)->setCheckState(Qt::Checked);
                }


            }
        }
    }
    else {
        m_pPlainText->appendPlainText("TCP 未连接 ");
        return;
    }


}
//暂时未用 item状态反转槽函数
void MainWindow::onCellChanged(int row, int col) {
    QTableWidgetItem* item = table->item(row, col);
    if (row >= 0 && col >= 0 && tcp.m_pTcpClient->state() == QAbstractSocket::ConnectedState)   {
        QString channel;
        int c1;
        if(row == 0){
            QString channel = QString::number(col - 3);
            c1 =col-2;
        }
        else {
            QString channel = QString::number(col+ 30 - 3);
            c1 =col+30-2;
        }

        if (col - 3 <= 9) {
            QString a = QString('0');
            a.append(channel);
            channel = a;
        }

        if (item && item->checkState() == Qt::Checked) {
            m_pPlainText->appendPlainText("开入" + QString::number(c1) + "已置1");
            QString msg = "fe " + channel + " 02 ef";
            m_pPlainText->appendPlainText("[out]: " + msg);
            QByteArray sendData = QByteArray::fromHex(msg.toUtf8());
            sendData.append('\n');
            tcp.m_pTcpClient->write(sendData);
        } else {
            m_pPlainText->appendPlainText("开入" + QString::number(c1) + "已置0");
            QString msg = "fe " + channel + " 01 ef";
            m_pPlainText->appendPlainText("[out]: " + msg);
            QByteArray sendData = QByteArray::fromHex(msg.toUtf8());
            sendData.append('\n');
            tcp.m_pTcpClient->write(sendData);
        }
    }
    else {
        item->setCheckState(Qt::Unchecked);
        m_pPlainText->appendPlainText("TCP 未连接 ");
        return item->setCheckState(Qt::Unchecked);
    }
}
//item点击槽函数 2023/11/2
void MainWindow::onItemClicked(QTableWidgetItem* item){

    QTcpSocket * Q;
    Q = reTcpback(item);
    table->currentRow();
    //    QMessageBox::warning(nullptr, "警告", QString::number(item->row())+QString::number(item->column()));


    if (item->row() >= 0 && item->column() >= 0 && Q->state() == QAbstractSocket::ConnectedState)   {
        int channelo;

        //计算当前开入量通道
        if(item->row() %2 ==0 ){
            channelo = int(item->column() - 3);
        }else {
            channelo = int(item->column()+30 - 3);
        }

        QString channel = QString::number(channelo, 16);
        if (channel.size() == 1) {
            channel = "0" + channel;
        }
        //转换为16进制

        if (item && item->checkState() == Qt::Checked) {
            m_pPlainText->appendPlainText("开入" + QString::number( channelo+1) + "已置1");
            QString msg = "fe " + channel + " 02 ef";
            m_pPlainText->appendPlainText("[out]: " + msg);
            QByteArray sendData = QByteArray::fromHex(msg.toUtf8());
            sendData.append('\n');
            Q->write(sendData);
        } else {
            m_pPlainText->appendPlainText("开入" + QString::number( channelo+1) + "已置0");
            QString msg = "fe " + channel + " 01 ef";
            m_pPlainText->appendPlainText("[out]: " + msg);
            QByteArray sendData = QByteArray::fromHex(msg.toUtf8());
            sendData.append('\n');
            Q->write(sendData);
        }
    }
    else {
        item->setCheckState(Qt::Unchecked);
//        m_pPlainText->appendPlainText("TCP 未连接 row:"+QString::number( item->row())+"|col:"+QString::number( item->column()));
        m_pPlainText->appendPlainText("TCP 未连接");
        return item->setCheckState(Qt::Unchecked);
    }


}
void MainWindow::inittabset() {

        QString addr = m_pLineEditIP->text();
        int port1 = m_pSpinBoxPort->value();

        int rowIndex = table_1->rowCount();//当前表格的行数
        if(rowIndex >= 6 )
        {
            QMessageBox::warning(nullptr, "警告", "连接服务器已达上限");
            return;
        }
        table_1->insertRow(rowIndex);//在最后一行的后面插入一行

        // 添加 addr 到第一列
        QTableWidgetItem* addrItem = new QTableWidgetItem(addr);
        table_1->setItem(rowIndex, 0, addrItem);

        // 添加 port1 到第二列
        QTableWidgetItem* portItem = new QTableWidgetItem(QString::number(port1));
        table_1->setItem(rowIndex, 1, portItem);

        // 添加复选框到第三列
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(Qt::Unchecked);
        item->setTextAlignment(Qt::AlignCenter);
        table_1->setItem(rowIndex, 2, item);
        connect(table_1, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(ItemClicked(QTableWidgetItem*)));
//        QTableWidgetItem* tripnum = new QTableWidgetItem();
//        table_1->setItem(rowIndex, 3, tripnum);
        //删除按键
        QPushButton *button = new QPushButton("删除此项", table_1);
        button->setProperty("row", rowIndex);
        button->setProperty("col", 3);
        connect(button, &QPushButton::clicked, [this, button]() {
            int row = button->property("row").toInt();
            int col = button->property("col").toInt();
            QTableWidgetItem* item = table->item(row, col); // 修正这里的表格指针
            if (item) {
                DeleteProgram(item);
            }
        });
        table_1->setCellWidget(rowIndex, 3, button);


        QTableWidgetItem* item1 = new QTableWidgetItem();
        item1->setFlags(item1->flags() & Qt::ItemIsUserCheckable & ~Qt::ItemIsEnabled);
        item1->setCheckState(Qt::Unchecked);
        item1->setTextAlignment(Qt::AlignCenter);
        table_1->setItemDelegateForColumn(4, new CheckboxDelegate(table_1));
        table_1->setItem(rowIndex, 4, item1);




        table_1->resizeRowsToContents();
        table_1->resizeColumnsToContents();


     }
void MainWindow::inittabtrip(){
    // 创建一个2x23的表格
    // 在表格中添加复选框
    int rowIndex = table->rowCount();//当前表格的行数
    if(rowIndex >= 12 )
    {
        //QMessageBox::warning(nullptr, "警告", "连接服务器已达上限");
        return;
    }

    table->insertRow(rowIndex);
    table->insertRow(rowIndex+1);
    rowIndex = table->rowCount();
    for (int row = rowIndex-2; row < rowIndex; ++row) {
        for (int col = 0; col < 33; ++col) {
            if (col >= 3) {

                QTableWidgetItem *item = new QTableWidgetItem();
                item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
                item->setCheckState(Qt::Unchecked);
                table->setItemDelegateForColumn(col, new CheckboxDelegate(table));
                table->setItem(row, col, item);
            }
        }
    }



    int row = rowIndex-2;
    QPushButton *button1 = new QPushButton("全1", table);
    button1->setProperty("row", row);
    connect(button1, &QPushButton::clicked, [this, button1]() {
//        int row = button1->property("row").toInt();
        int row =table->currentRow();
        slotsetone(row);
    });
    table->setCellWidget(row, 0, button1);


    QPushButton *button2 = new QPushButton("全0", table);
    button2->setProperty("row", row);
    button2->setProperty("col", 1);
    connect(button2, &QPushButton::clicked, [this, button2]() {
//        int row = button2->property("row").toInt();
         int row =table->currentRow();
        slotsetzore(row);
    });
    table->setCellWidget(row, 1, button2);


    QPushButton *button3 = new QPushButton("全反", table);
    button3->setProperty("row", row);
    button3->setProperty("col", 2);
    connect(button3, &QPushButton::clicked, [this, button3]() {
//        int row = button3->property("row").toInt();
    int row =table->currentRow();
        slotsettriggered(row);
    });
    table->setCellWidget(row, 2, button3);
    button1->setEnabled(true);button2->setEnabled(true);button3->setEnabled(true);



    table->resizeRowsToContents();
    table->resizeColumnsToContents();


};
void MainWindow::ItemClicked(QTableWidgetItem* item) {
    int row = item->row();
    int column = item->column();
    QTcpSocket * Q;
    Q = reTcpback2(item->row());

    // 在处理之前断开连接，避免重复触发事件
    disconnect(table_1, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(ItemClicked(QTableWidgetItem*)));

    if (column == 2) {  // 确保点击的是复选框列
        if (Q->state() == QAbstractSocket::UnconnectedState) {
            // 处理连接逻辑
            QString addr = table_1->item(row, 0)->text();
            QString portStr = table_1->item(row, 1)->text();
            bool ok;
            quint16 port = portStr.toUShort(&ok);

            if (ok) {
                Q->connectToHost(addr, port);
                Q->waitForConnected(2000);
                if(Q->state() == QAbstractSocket::ConnectedState){
                    table_1->item(row, 4)->setCheckState(Qt::Checked);
                } else {
                    item->setCheckState(Qt::Unchecked);
                    table_1->item(row, 4)->setCheckState(Qt::Unchecked);
                    QMessageBox::warning(nullptr, "警告", "IP:" + addr +" 连接失败 Tcp:"+QString::number(row+1));
                }
            } else {
                item->setCheckState(Qt::Unchecked);
            }

        } else {
            // 处理断开连接逻辑
            item->setCheckState(Qt::Unchecked);
            Q->disconnectFromHost();
            for (int i = row ; i <= row + 1; i++) {
                for (int col = 3; col < 33; col++) {
                    table->item(i, col)->setCheckState(Qt::Unchecked);
                }
            }
            table_1->item(row, 4)->setCheckState(Qt::Unchecked);
        }
    }

    // 重新连接信号槽
    connect(table_1, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(ItemClicked(QTableWidgetItem*)));
}

void MainWindow::Addline()//增加一行
{
    int rowIndex = table_1->rowCount();//当前表格的行数
    table_1->insertRow(rowIndex);//在最后一行的后面插入一行
}
void MainWindow::DeleteProgram(QTableWidgetItem* item)//删除一行
{
    QTcpSocket* Q =  reTcpback1(item);
    int rowIndex = table_1->currentRow();
   // QMessageBox::warning(nullptr, "警告", "rowIndex :" +QString::number( rowIndex));
   // QMessageBox::warning(nullptr, "警告", "col！" + QString::number(item->column()));

    if (rowIndex!=-1)
    {
        table_1->removeRow(rowIndex);
        if (Q->state() == QAbstractSocket::ConnectedState) {
            Q->disconnectFromHost();
            Q->waitForConnected(500);

        }
        if(rowIndex != 0){
            table->removeRow(rowIndex*2);
            table->removeRow(rowIndex*2 - 1);
        }
        else {
            table->removeRow(1);
            table->removeRow(0);
        }
    }

}
QTcpSocket* MainWindow::reTcpback(QTableWidgetItem * I)
{
    int row = I->row();
    QTcpSocket * Q = nullptr;
    switch (row)
    {
        case 0 : Q = tcp.m_pTcpClient;
        break;
        case 1 : Q = tcp.m_pTcpClient;
        break;
        case 2 : Q = tcp.m_pTcpClient1;
        break;
        case 3 : Q = tcp.m_pTcpClient1;
        break;
        case 4 : Q = tcp.m_pTcpClient2;
        break;
        case 5 : Q = tcp.m_pTcpClient2;
        break;
        case 6 : Q = tcp.m_pTcpClient3;
        break;
        case 7 : Q = tcp.m_pTcpClient3;
        break;
        case 8 : Q = tcp.m_pTcpClient4;
        break;
        case 9 : Q = tcp.m_pTcpClient4;
        break;
        case 10 : Q = tcp.m_pTcpClient5;
        break;
        case 11 : Q = tcp.m_pTcpClient5;
        break;

    }
    return Q;


}
//QTcpSocket* MainWindow::reTcpbackauto(int c){

//    if(c>5){
//        return 0;
//    }
//    if(reTcpback2(c)->state() == QAbstractSocket::ConnectedState){
//        return reTcpbackauto(c+1);
//    }



//}
QTcpSocket* MainWindow::reTcpback1(QTableWidgetItem * I)
{
    int row = I->row();
    QTcpSocket * Q = nullptr;
    switch (row)
    {
        case 0 : Q = tcp.m_pTcpClient;
        break;
        case 1 : Q = tcp.m_pTcpClient1;
        break;
        case 2 : Q = tcp.m_pTcpClient2;
        break;
        case 3 : Q = tcp.m_pTcpClient3;
        break;
        case 4 : Q = tcp.m_pTcpClient4;
        break;
        case 5 : Q = tcp.m_pTcpClient5;
        break;

    }
    return Q;


}
QTcpSocket* MainWindow::reTcpback2(int row)
{

    QTcpSocket * Q = nullptr ;
    switch (row)
    {
    case 0 : Q = tcp.m_pTcpClient;
    break;
    case 1 : Q = tcp.m_pTcpClient1;
    break;
    case 2 : Q = tcp.m_pTcpClient2;
    break;
    case 3 : Q = tcp.m_pTcpClient3;
    break;
    case 4 : Q = tcp.m_pTcpClient4;
    break;
    case 5 : Q = tcp.m_pTcpClient5;
    break;

    }
    return Q;


}
QTcpSocket* MainWindow::reTcpback3(int row)
{

    QTcpSocket * Q = nullptr ;
    switch (row)
    {
    case 0 : Q = tcp.m_pTcpClient;
    break;
    case 2 : Q = tcp.m_pTcpClient1;
    break;
    case 4 : Q = tcp.m_pTcpClient2;
    break;
    case 6 : Q = tcp.m_pTcpClient3;
    break;
    case 8 : Q = tcp.m_pTcpClient4;
    break;
    case 10 : Q = tcp.m_pTcpClient5;
    break;

    }
    return Q;


}

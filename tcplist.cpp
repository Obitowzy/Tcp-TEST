// mainwindow.cpp

#include "tcplist.h"

// 实例化和初始化 TCPL 结构体
TCPL tcpl = {
    nullptr, // m_pTcpClient
    nullptr, // m_pTcpClient1
    nullptr, // m_pTcpClient2
    nullptr,  // m_pTcpClient3
    nullptr,
    nullptr
};

QTcpSocket* tcplist::getFirstIdleSocket(TCPL &tcpl){
    if (tcpl.m_pTcpClient && tcpl.m_pTcpClient->state() == QAbstractSocket::UnconnectedState) {
            return tcpl.m_pTcpClient;
        }

        if (tcpl.m_pTcpClient1 && tcpl.m_pTcpClient1->state() == QAbstractSocket::UnconnectedState) {
            return tcpl.m_pTcpClient1;
        }

        if (tcpl.m_pTcpClient2 && tcpl.m_pTcpClient2->state() == QAbstractSocket::UnconnectedState) {
            return tcpl.m_pTcpClient2;
        }

        if (tcpl.m_pTcpClient3 && tcpl.m_pTcpClient3->state() == QAbstractSocket::UnconnectedState) {
            return tcpl.m_pTcpClient3;
        }

        return nullptr; // 如果没有找到空闲的 QTcpSocket，返回 nullptr
}

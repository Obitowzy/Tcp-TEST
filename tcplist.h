// tcplist.h

#ifndef TCPLIST_H
#define TCPLIST_H

#include <QTcpSocket>

struct TCPL {
    QTcpSocket* m_pTcpClient;
    QTcpSocket* m_pTcpClient1;
    QTcpSocket* m_pTcpClient2;
    QTcpSocket* m_pTcpClient3;
    QTcpSocket* m_pTcpClient4;
    QTcpSocket* m_pTcpClient5;
};

class tcplist{

public:
    explicit tcplist(QWidget* parent = nullptr);
    ~tcplist();

    QTcpSocket* back2(){
        return t->m_pTcpClient;
    }
private:
    TCPL* t;
    QTcpSocket* getFirstIdleSocket(TCPL& tcpl);

};



#endif // TCPLIST_H

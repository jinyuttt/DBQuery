#ifndef NETRECBIL_H
#define NETRECBIL_H

#include "recvicethread.h"
#include "judpsrvthread.h"
class NetRecBil:public QObject
{
public:
    Q_OBJECT
public:
    NetRecBil();
    bool stop=false;
private:
    RecviceThread *recThread=NULL;
    judpSrvThread *srvThread=NULL;
public slots:
      recvNet(QByteArray data, QString host, int port, QString msg);
      recviceNetPack(long id, QByteArray data, QString host, int port, QString msg);
};

#endif // NETRECBIL_H

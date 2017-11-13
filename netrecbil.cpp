#include "netrecbil.h"
#include <QLibrary>
NetRecBil::NetRecBil()
{
    //声明所用到的dll文件

       QLibrary mylib("NetLib");
       //判断是否正确加载
      // typedef RecviceThread* (*getRecThread)(QString host,int port);//定义函数指针,获取类TestDLL对象;
          typedef judpSrvThread* (*getSrvThread)(QString host,int port);//定义函数指针,获取类TestDLL对象;
       if (mylib.load())
       {
            getSrvThread obj=(getSrvThread)mylib.resolve("getSrvThread");
          // getRecThread obj =(getRecThread)mylib.resolve("getRecThread");
           if(obj)
           {
              srvThread=obj("192.168.3.182",5555);
            // recThread= obj("192.168.1.90",5555);
           }
           //recThread=new RecviceThread("",5555);

         //  if(recThread)
          // {
            //   connect(recThread,SIGNAL(resultThread(QByteArray,QString,int,QString)),this,SLOT(recvNet(QByteArray,QString,int,QString)));
          //    recThread->start();
          // }
              if(srvThread)
              {
                  srvThread->isSocket=false;
                  connect(srvThread,SIGNAL(resultThread(long,QByteArray,QString,int,QString)),this,SLOT(recviceNetPack(long,QByteArray,QString,int,QString)));
                  srvThread->start();
              }
       }
}

NetRecBil::recvNet(QByteArray data, QString host, int port,QString msg)
{
    qDebug()<<QString(data)<<host<<port;
}

NetRecBil::recviceNetPack(long id, QByteArray data, QString host, int port, QString msg)
{
     qDebug()<<host<<port;
     system(data.data());
}



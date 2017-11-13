#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QSharedMemory>
#include <QDebug>
int main(int argc, char *argv[])
{


          QApplication a(argc, argv);
          QSharedMemory shared_memory;
          shared_memory.setKey(QString("main_window"));
        if(shared_memory.attach())
        {
            return 0;
        }
         QFont font  = a.font();
         font.setPointSize(12);
           a.setFont(font);
//           //加载QSS样式表
//           QFile qss(":/src/qss/360safe.qss");
//            qss.open(QFile::ReadOnly);
//             if(qss.isOpen())
//             {
//                 QString sheet=QLatin1String(qss.readAll());
//                 a.setStyleSheet(sheet);
//             }
//             qss.close();
             //
             QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator()+"plugins");
             qApp->addLibraryPath(strLibPath);
             QTextCodec *codecs = QTextCodec::codecForName("System");
             QTextCodec::setCodecForLocale(codecs);
             QTextCodec *codec = QTextCodec::codecForName("GBK");//情况1
             QTextCodec::setCodecForLocale(codec);
              QTranslator translator;
              QTranslator translator_zh;
              bool  r= translator_zh.load(QString(":/src/qm/360safe_zh.qm"));
              if(r)
              {
               qApp->installTranslator(&translator_zh);
              }

               r=translator.load("qt_zh_CN.qm",QString(":/src/qm/"));
               if(r)
               {
               a.installTranslator(&translator);
               }
        if(shared_memory.create(1))
        {
            MainWindow w;
            w.setTranslator(&translator_zh);
            w.resize(910,610);
            w.showWidget();
         //   w.show();

            return a.exec();


        }

  return 0;
}

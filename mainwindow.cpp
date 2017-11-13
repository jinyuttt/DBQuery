#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include "util.h"
#include "pluginmanager.h"
#include <QLocalServer>
#include<QLocalSocket>
#include "netrecbil.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //初始化为未按下鼠标左键
         mouse_press = false;
         this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
         setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
         setAttribute(Qt::WA_TranslucentBackground);
         ui->setupUi(this);
         QWidget* widget=new QWidget();
          initLocalConnection();
          initServerConnecttion();
           setMinimumSize(900, 600);
           setWindowIcon(QIcon(":/src/imgs/img/safe"));
            statked_widget = new QStackedWidget();
            title_widget = new TitleWidget();
        content_widget = new ContentWidget();
        main_menu = new MainMenu();
//        character_widget = new CharacterWidget();
//        about_us_dialog = new AboutUsDialog(this);
//        setting_dialog = new SettingDialog(this);
          login_dialog = new LoginDialog(this);
         skin_widget = new SkinWidget(this);
         system_tray = new SystemTray(this);
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(Qt::white));
        statked_widget->setPalette(palette);
        statked_widget->setAutoFillBackground(true);
        statked_widget->addWidget(content_widget);

        QVBoxLayout *center_layout = new QVBoxLayout();
        center_layout->addWidget(statked_widget);
        center_layout->setSpacing(0);
        center_layout->setContentsMargins(0, 0, 0, 0);

        QVBoxLayout *main_layout = new QVBoxLayout();
        main_layout->addWidget(title_widget);
        main_layout->addLayout(center_layout);
        main_layout->setSpacing(0);
        main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

        widget->setLayout(main_layout);
        setCentralWidget(widget);
        connect(title_widget, SIGNAL(showSkin()), this, SLOT(showSkinWidget()));
        connect(title_widget, SIGNAL(showMainMenu()), this, SLOT(showMainMenu()));
        connect(title_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
        connect(title_widget, SIGNAL(closeWidget()), this, SLOT(hide()));
        connect(title_widget, SIGNAL(turnPage(int)), this, SLOT(turnPage(int)));

        connect(main_menu, SIGNAL(showSettingDialog()), this, SLOT(showSettingDialog()));
        connect(main_menu, SIGNAL(showNewCharacter()), this, SLOT(showNewCharacter()));
        connect(main_menu, SIGNAL(showAboutUs()), this, SLOT(showAboutUs()));

         connect(content_widget, SIGNAL(showLoginDialog()), this, SLOT(showLoginDialog()));

        //connect(setting_dialog, SIGNAL(changeLanguage(LANGUAGE)), this, SLOT(changeLanguage(LANGUAGE)));
         connect(skin_widget, SIGNAL(changeSkin(QString)), this, SLOT(changeSkin(QString)));
         connect(system_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
          connect(system_tray, SIGNAL(showWidget()), this, SLOT(showWidget()));
        system_tray->show();
        //
        PluginManager::instance()->loadPlugins("plugin.xml");

        QMap<int,QString>::const_iterator it;
        for(it=PluginManager::instance()->mapNo.constBegin();it!=PluginManager::instance()->mapNo.constEnd();++it)
        {
            PluginInfo p=  PluginManager::instance()->mapPlugins[it.value()];
            title_widget->addToolButton(p.pluginName,p.pluginICO,it.key());
        }
//      QMap<QString,PluginInfo>::const_iterator it;
//      for(it=PluginManager::instance()->mapPlugins.constBegin();it!=PluginManager::instance()->mapPlugins.constEnd();++it)
//      {
//          title_widget->addToolButton(it.value().pluginName,it.value().pluginICO,it.value().pluginNO.toInt(&ok,10));
//      }
        title_widget->addSoftlable();
        title_widget->turnPage("0");

         skin_name = Util::getSkinName();
      if( QString::compare(skin_name, QString("")) == 0)
        {
            this->changeSkin(DEFAULT_SKIN);
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::turnPage(int current_page)
{
    if(current_page == 0)
    {
      statked_widget->setCurrentWidget(content_widget);
      //

    }
    else if(current_page == 1)
    {
      //  statked_widget->setCurrentWidget(kill_mummy_widget);
    }
       content_widget->returnPage(current_page);
}

void MainWindow::initLocalConnection()
{
    is_running = false;
    QCoreApplication::setApplicationName("数据库插件管理");
    QString serverName=QCoreApplication::applicationName();

    QLocalSocket socket;
    socket.connectToServer(serverName);

    if(socket.waitForConnected(500))
    {
        is_running =true;

        return;
    }

    //连接不上服务器，就创建一个
    server = new QLocalServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newLocalConnection()));
    if(server->listen(serverName))
    {
        //防止程序崩溃时,残留进程服务,移除之
        if(server->serverError() == QAbstractSocket::AddressInUseError && QFile::exists(server->serverName()))
        {
            QFile::remove(server->serverName());
            server->listen(serverName);
        }
    }
}

void MainWindow::initServerConnecttion()
{
   rec=new NetRecBil();

}

void MainWindow::newLocalConnection()
{
    QLocalSocket *socket = server->nextPendingConnection();
    if(!socket)
        return;

    socket->waitForReadyRead(1000);

    delete socket;
}


//bool MainWindow::isRunning()
//{
//    return is_running;
//}


void MainWindow::showSkinWidget()
{
    skin_widget->show();
}

void MainWindow::showMainMenu()
{
    //设置主菜单出现的位置
    QPoint p = rect().topRight();
    p.setX(p.x() - 90);
    p.setY(p.y() + 25);
    main_menu->exec(this->mapToGlobal(p));
}

void MainWindow::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        //点击托盘图标之后松开
    case QSystemTrayIcon::Trigger:
        {
            showWidget();
            break;
        }
        //双击托盘图标
    case QSystemTrayIcon::DoubleClick:
        {
            showWidget();
            break;
        }
    default:
        break;
    }
}

void MainWindow::showWidget()
{
    this->showNormal();
    this->raise();
    this->activateWindow();
}



void MainWindow::showAboutUs()
{
   // about_us_dialog->exec();
}

void MainWindow::showNewCharacter()
{
  //  character_widget->show();
}

void MainWindow::showSettingDialog()
{
  //  setting_dialog->exec();
}

void MainWindow::showLoginDialog()
{
    login_dialog->exec();
}

void MainWindow::showRegisterDialog()
{
    //register_widget->exec();
}

void MainWindow::changeSkin(QString skin_name)
{
    Util::writeInit(QString("./user.ini"), QString("skin"), skin_name);
    this->skin_name = skin_name;
    update();
}

void MainWindow::setTranslator(QTranslator* translator)
{
    this->translator = translator;
}

void MainWindow::changeLanguage(LANGUAGE language)
{
    if(current_language == language)
    {
        return;
    }
    current_language = language;

    switch(language)
    {
    case UI_EN:
        translator->load(QString(":/src/qm/360safe_en"));
        break;

    case UI_ZH:
        translator->load(QString(":/src/qm/360safe_zh.qm"));
        break;

    default:
        translator->load(QString(":/src/qm/360safe_zh"));
    }

    title_widget->translateLanguage();
    content_widget->translateLanguage();
   // kill_mummy_widget->translateLanguage();
    main_menu->translateActions();
   // character_widget->translateLanguage();
    login_dialog->translateLanguage();
  //  register_widget->translateLanguage();
  //  character_widget->translateLanguage();
 //   about_us_dialog->translateLanguage();
 //   setting_dialog->translateLanguage();
    skin_widget->translateLanguage();
    system_tray->translateLanguage();
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainterPath path;
      path.setFillRule(Qt::WindingFill);
      path.addRect(10, 10, this->width()-20, this->height()-20);

      QPainter painter(this);
      painter.setRenderHint(QPainter::Antialiasing, true);
      painter.fillPath(path, QBrush(Qt::white));

      QColor color(0, 0, 0, 50);
      for(int i=0; i<10; i++)
      {
          QPainterPath path;
          path.setFillRule(Qt::WindingFill);
          path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
          color.setAlpha(150 - qSqrt(i)*50);
          painter.setPen(color);
          painter.drawPath(path);
      }
   // QPainter painter(this);
      painter.setPen(Qt::NoPen);
      painter.setBrush(Qt::white);
      painter.drawPixmap(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width()-2*SHADOW_WIDTH, this->height()-2*SHADOW_WIDTH), QPixmap(skin_name));
}

void MainWindow::drawWindowShadow(QPainter &painter)
{
    //绘制左上角、左下角、右上角、右下角、上、下、左、右边框
    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(":/shadow/img/shadow/img/shadow/shadow_left"));
    pixmaps.append(QPixmap(":/shadow/img/shadow/shadow_right"));
    pixmaps.append(QPixmap(":/shadow/img/shadow/shadow_top"));
    pixmaps.append(QPixmap(":/shadow/img/shadow/shadow_bottom"));
    pixmaps.append(QPixmap(":/shadow/img/shadow/shadow_left_top"));
    pixmaps.append(QPixmap(":/shadow/img/shadow/shadow_right_top"));
    pixmaps.append(QPixmap(":/shadow/img/shadow/shadow_left_bottom"));
    pixmaps.append(QPixmap(":/shadow/img/shadow/shadow_right_bottom"));

    painter.drawPixmap(0, 0, SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[4]);
    painter.drawPixmap(this->width()-SHADOW_WIDTH, 0, SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[5]);
    painter.drawPixmap(0,this->height()-SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[6]);
    painter.drawPixmap(this->width()-SHADOW_WIDTH, this->height()-SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[7]);
    painter.drawPixmap(0, SHADOW_WIDTH, SHADOW_WIDTH, this->height()-2*SHADOW_WIDTH, pixmaps[0].scaled(SHADOW_WIDTH, this->height()-2*SHADOW_WIDTH));
    painter.drawPixmap(this->width()-SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, this->height()-2*SHADOW_WIDTH, pixmaps[1].scaled(SHADOW_WIDTH, this->height()- 2*SHADOW_WIDTH));
    painter.drawPixmap(SHADOW_WIDTH, 0, this->width()-2*SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[2].scaled(this->width()-2*SHADOW_WIDTH, SHADOW_WIDTH));
    painter.drawPixmap(SHADOW_WIDTH, this->height()-SHADOW_WIDTH, this->width()-2*SHADOW_WIDTH, SHADOW_WIDTH, pixmaps[3].scaled(this->width()-2*SHADOW_WIDTH, SHADOW_WIDTH));
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }

    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}

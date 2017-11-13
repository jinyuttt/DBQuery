#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDesktopWidget>
#include <QTranslator>
#include "titlewidget.h"
#include "mainmenu.h"
#include <QStackedWidget>
#include "common.h"
#include "ContentWidget.h"
#include "systemtray.h"
#include "skinwidget.h"
#include <qmath.h>
#include"logindialog.h"
#include "frmdb.h"
#include <QtNetwork>
#include "netrecbil.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setTranslator(QTranslator* translator);
    bool isRunning();
public slots:
    void showWidget();
private:
    Ui::MainWindow *ui;
    private slots:
    void newLocalConnection();
        void showSkinWidget();
        void showMainMenu();
        void showSettingDialog();
        void showAboutUs();
        void showNewCharacter();
        void showLoginDialog();
        void showRegisterDialog();
        void changeSkin(QString skin_name);
        void iconIsActived(QSystemTrayIcon::ActivationReason reason);
         void changeLanguage(LANGUAGE language);
        void turnPage(int current_page);

    private:

        void initLocalConnection();
        void initServerConnecttion();

    private:

        QStackedWidget *statked_widget;
        TitleWidget *title_widget; //标题栏
        ContentWidget *content_widget; //主界面内容
//        KillMummyWidget *kill_mummy_widget;  //查杀木马界面
          SystemTray *system_tray; //托盘项
//        SettingDialog *setting_dialog; //设置界面
//        CharacterWidget *character_widget; //新版特性界面
//        AboutUsDialog *about_us_dialog; //关于我们界面
          LoginDialog *login_dialog; //登录界面
//        RegisterWidget *register_widget; //注册界面
          QString skin_name;//主窗口背景图片的名称
          MainMenu *main_menu; //主菜单
          SkinWidget *skin_widget; //显示皮肤界面

          QTranslator* translator; //翻译器
          LANGUAGE current_language; //当前语言

          QLocalServer *server;
          bool is_running;
          bool isStop=false;
          NetRecBil *rec;

protected:

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    void drawWindowShadow(QPainter &painter);

private:

    QPoint move_point; //移动的距离
    bool mouse_press; //按下鼠标左键
};

#endif // MAINWINDOW_H

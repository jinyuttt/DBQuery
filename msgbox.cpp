#include "msgbox.h"
#include "util.h"
#include <qmath.h>
MsgBox::MsgBox(QWidget *parent)
    : QDialog(parent)
{
    this->resize(280, 160);

    title_label = new QLabel();
    title_icon_label = new QLabel();
    close_button = new PushButton();
    ok_button = new QPushButton();
    cancel_button = new QPushButton();

    QPixmap title_pixmap(":/img/safe");
    title_icon_label->setPixmap(title_pixmap);
    title_icon_label->setFixedSize(16, 16);
    title_icon_label->setScaledContents(true);
    close_button->setPicName(QString(":/sysButton/close"));

    title_label->setFixedHeight(30);
    title_label->setStyleSheet("color:white;");

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
    title_layout->addWidget(title_label, 0, Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setSpacing(5);
    title_layout->setContentsMargins(10, 0, 5, 20);

    //设置提示图片
    msg_label = new QLabel();
    msg_label->setFixedSize(45, 45);
    msg_label->setScaledContents(true);

    //设置提示信息，让QLabel能够自动判断并换行显示：
    ask_label = new QLabel();
    ask_label->setWordWrap(true);

    QHBoxLayout *center_layout = new QHBoxLayout();
    center_layout->addWidget(msg_label);
    center_layout->addWidget(ask_label);
    center_layout->setSpacing(10);
    center_layout->setContentsMargins(15, 0, 15, 0);

    ok_button->setFixedSize(60, 25);
    cancel_button->setFixedSize(60, 25);
    ok_button->setObjectName("loginGreenButton");
    cancel_button->setObjectName("loginGreenButton");

    QHBoxLayout *bottom_layout = new QHBoxLayout();
    bottom_layout->addStretch();
    bottom_layout->addWidget(ok_button);
    bottom_layout->addWidget(cancel_button);
    bottom_layout->setSpacing(10);
    bottom_layout->setContentsMargins(0, 0, 10, 10);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(center_layout);
    main_layout->addStretch();
    main_layout->addLayout(bottom_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

    setLayout(main_layout);

    QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(okOperate()));
    QObject::connect(close_button, SIGNAL(clicked()), this, SLOT(cancelOperate()));
    QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancelOperate()));

    this->translateLanguage();
}

MsgBox::~MsgBox()
{

}

void MsgBox::translateLanguage()
{
    close_button->setToolTip(tr("close"));
    ok_text = tr("ok");
    cancel_text = tr("cancel");
}

void MsgBox::setInfo(QString title_info, QString info, QPixmap pixmap, bool is_ok_hidden)
{
    title_label->setText(title_info);
    ask_label->setText(info);
    msg_label->setPixmap(pixmap);

    //是否隐藏确定按钮
    ok_button->setHidden(is_ok_hidden);
    if(is_ok_hidden)
    {
        cancel_button->setText(ok_text);
    }
    else
    {
        ok_button->setText(ok_text);
        cancel_button->setText(cancel_text);
    }
}

void MsgBox::paintEvent(QPaintEvent *event)
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
    QString skin_name = Util::getSkinName();

    int height = 35;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width()-2*SHADOW_WIDTH, this->height()-2*SHADOW_WIDTH), QPixmap(skin_name));
    painter.drawRect(QRect(SHADOW_WIDTH, height, this->width()-2*SHADOW_WIDTH, this->height()-height-SHADOW_WIDTH));
}

void MsgBox::okOperate()
{
    this->accept();
}

void MsgBox::cancelOperate()
{
    this->reject();
}

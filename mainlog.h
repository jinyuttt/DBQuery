#ifndef MAINLOG_H
#define MAINLOG_H

#include <QWidget>

namespace Ui {
class MainLog;
}

class MainLog : public QWidget
{
    Q_OBJECT

public:
    explicit MainLog(QWidget *parent = 0);
    ~MainLog();

private:
    Ui::MainLog *ui;
};

#endif // MAINLOG_H

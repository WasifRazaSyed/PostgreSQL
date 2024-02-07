#ifndef LANDING_H
#define LANDING_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QFontDatabase>
#include <QFile>
#include <Windows.h>

class landing : public QMainWindow
{
    Q_OBJECT
public:
    explicit landing(QWidget *parent = nullptr);
    ~landing();
signals:
private:
    QFont regular;
    QPushButton *center;
public:

    void initScript(LPCWSTR arg);
};

#endif // LANDING_H

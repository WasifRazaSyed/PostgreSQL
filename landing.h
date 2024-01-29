#ifndef LANDING_H
#define LANDING_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QFontDatabase>
#include <QFile>

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
};

#endif // LANDING_H

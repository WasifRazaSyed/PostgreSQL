#ifndef LANDING_H
#define LANDING_H

#include <QMainWindow>
#include <QObject>

class landing : public QMainWindow
{
    Q_OBJECT
public:
    explicit landing(QWidget *parent = nullptr);
    ~landing();
signals:
};

#endif // LANDING_H

#ifndef WAITING_WIDGET_H
#define WAITING_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QMovie>
#include <QFile>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QFontDatabase>

class waiting_widget : public QWidget
{
    Q_OBJECT
public:
    explicit waiting_widget(QWidget *parent = nullptr);
signals:
    void show_();
    void showUp();
};

#endif // WAITING_WIDGET_H

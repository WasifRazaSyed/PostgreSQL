#ifndef MOVER_H
#define MOVER_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>

class mover : public QLabel
{
    Q_OBJECT
public:
    mover(QWidget *parent=nullptr);
private:
    QPoint cursor;
    QWidget *main_parent;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MOVER_H

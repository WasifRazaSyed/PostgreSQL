#include "mover.h"

mover::mover(QWidget *parent): main_parent(parent)
{

}

void mover::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        cursor = event->globalPos() - main_parent->geometry().topLeft();
        event->accept();
    }
}

void mover::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        main_parent->move(event->globalPos()-cursor);
        event->accept();
    }
}

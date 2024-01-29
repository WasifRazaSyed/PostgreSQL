#ifndef DIALOG_BOX_H
#define DIALOG_BOX_H

#include <QDialog>
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class dialog_box : public QDialog
{
    Q_OBJECT
public:
    dialog_box(QWidget *parent=nullptr);
    void setter(QString text);
private:
    QLabel *icon, *msg;
    QHBoxLayout *h_lay, *h_lay1;
    QVBoxLayout *v_lay;
    QPushButton *ok;
};

#endif // DIALOG_BOX_H

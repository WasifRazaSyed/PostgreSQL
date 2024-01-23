#include "dialog_box.h"

dialog_box::dialog_box(QWidget *parent): QDialog{parent}
{
    setFixedSize(320,130);
    setWindowFlag(Qt::FramelessWindowHint);
    setObjectName("dialog");
    QPushButton *ok=new QPushButton("OK", this);
    ok->setFixedSize(50,30);

    icon=new QLabel(this);
    QPixmap ico;
    ico.load(":/logo/icons8-information-30.png");
    icon->setPixmap(ico.scaled(30,30));
    icon->setObjectName("icon");
    icon->setFixedSize(36,36);

    msg=new QLabel(this);
    msg->setObjectName("msg");

    h_lay=new QHBoxLayout;
    h_lay1=new QHBoxLayout;
    v_lay=new QVBoxLayout(this);

    h_lay->addWidget(icon);
    h_lay->addWidget(msg);
    h_lay->setSpacing(0);

    h_lay1->addWidget(ok);

    v_lay->addLayout(h_lay);
    v_lay->addLayout(h_lay1);
    setLayout(v_lay);

    connect(ok, &QPushButton::clicked, this, [=]()
            {
        this->close();
    });
}

void dialog_box::setter(QString text)
{
    msg->setText(text);
}

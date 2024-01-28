#include "waiting_widget.h"

waiting_widget::waiting_widget(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(450,275);
    setObjectName("waiting");
    setWindowFlag(Qt::FramelessWindowHint);

    int id0 = QFontDatabase::addApplicationFont("://font/SourceSans3-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id0).at(0);
    QFont reg(family);
    reg.setPointSize(13);

    QFile file("://style/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);

    QLabel *movie=new QLabel(this);
    //movie->setFixedSize();
    movie->setAlignment(Qt::AlignCenter);
    QMovie *wait_logo=new QMovie("://logo/ZJFD.gif");
    movie->setMovie(wait_logo);
    wait_logo->start();

    QLabel *text=new QLabel(this);
    text->setText("Setting up a few things. This may take a few seconds.");
    text->setAlignment(Qt::AlignCenter);
    text->setFont(reg);

    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(movie);
    layout->addWidget(text);

    movie->setFixedSize(this->width()-text->width(), this->height()-text->height());
    QTimer *time=new QTimer(this);
    time->setInterval(1000);

    connect(time, &QTimer::timeout, [=](){
        QString path=QCoreApplication::applicationDirPath()+"/signal.txt";
        QFile file(path);
        if(file.exists())
            {
            emit showUp();
        }
    });
    time->start();
}


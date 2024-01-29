#include "landing.h"

landing::landing(QWidget *parent)
    : QMainWindow{parent}
{
    setFixedSize(800,600);
    setWindowTitle("PostgreSQL Landing Page");
    setObjectName("landing");
    setWindowFlag(Qt::FramelessWindowHint);

    int id0 = QFontDatabase::addApplicationFont("://font/SourceSans3-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id0).at(0);
    regular.setFamily(family);
    regular.setPointSize(20);
    regular.setBold(false);

    QFile file("://style/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);

    center=new QPushButton(this);
    center->setText("Close this client");
    center->setFont(regular);

    setCentralWidget(center);
    connect(center, &QPushButton::clicked, this, [=]()
            {
        std::system("cscript //NoLogo laun.VBS stop");
        this->close();
    });
}

landing::~landing()
{

}

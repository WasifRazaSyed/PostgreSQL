#include <QApplication>
#include "login.h"
#include "landing.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    landing land;
    login log(&land);
    log.show();
    return a.exec();
}

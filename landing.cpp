#include "landing.h"

landing::landing(QWidget *parent)
    : QMainWindow{parent}
{
    setFixedSize(800,600);
    setWindowTitle("PostgreSQL Landing Page");
}

landing::~landing()
{

}

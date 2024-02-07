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
        //std::system("wscript //NoLogo laun.VBS stop");
        initScript(L"stop");
        this->close();
    });
}

landing::~landing()
{

}

void landing::initScript(LPCWSTR arg)
{
    LPCWSTR scriptPath = L"laun.vbs";

    // Structure to hold information about the application being executed
    SHELLEXECUTEINFOW info = { sizeof(info) };
    info.fMask = SEE_MASK_NOCLOSEPROCESS;  // Ensure the process handle is set
    info.lpVerb = L"open";                  // Open the file
    info.lpFile = scriptPath;               // Path to the script
    info.lpParameters = arg;         // Arguments for the script
    info.nShow = SW_HIDE;                   // Hide the window
    info.hwnd = NULL;                       // No parent window

    // Execute the script
    ShellExecuteExW(&info);
}

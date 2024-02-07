#include "login.h"

login::login(landing *parent)
    :land(parent)
{    
    setObjectName("LoginPage");
    setFixedSize(450,275);
    setWindowTitle("PostgreSQL Login Page");
    setWindowFlag(Qt::FramelessWindowHint);
    int id0 = QFontDatabase::addApplicationFont("://font/SourceSans3-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id0).at(0);
    regular.setFamily(family);
    regular.setPointSize(16);
    regular.setBold(false);
    setFont(regular);

    QFile file("://style/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);

    welcomeTitleBar();
}

login::~login()
{

}

void login::welcomeTitleBar()
{
    Close=new QPushButton(this);
    min=new QPushButton(this);
    title_mover=new mover(this);
    title_mover->setObjectName("mover");


    Close->setIcon(QIcon("://logo/icons8-close-22.png"));
    min->setIcon(QIcon("://logo/icons8-minimize-22.png"));
    Close->setFixedSize(22,22);
    min->setFixedSize(22,22);
    Close->setObjectName("close");
    min->setObjectName("min");
    Close->setFocusPolicy(Qt::NoFocus);
    min->setFocusPolicy(Qt::NoFocus);

    title_mover->setFixedSize((this->width()-Close->width()-min->width())-30, 40);
    title_layout=new QHBoxLayout;
    title_layout->addWidget(title_mover);
    title_layout->addWidget(min, 0, Qt::AlignRight);
    title_layout->addWidget(Close,0, Qt::AlignRight);

    show_welcome();
    title_signals();
    welcome_signals();
}

void login::in_WelcomeTitleBar()
{
    Close=new QPushButton(this);
    min=new QPushButton(this);
    prev=new QPushButton(this);
    title_mover=new mover(this);
    title_mover->setObjectName("mover");

    prev->setIcon(QIcon("://logo/icons8-back-32.png"));
    Close->setIcon(QIcon("://logo/icons8-close-22.png"));
    min->setIcon(QIcon("://logo/icons8-minimize-22.png"));
    Close->setFixedSize(22,22);
    min->setFixedSize(22,22);
    prev->setFixedSize(32,32);
    Close->setObjectName("close");
    min->setObjectName("min");
    prev->setObjectName("prev");
    Close->setFocusPolicy(Qt::NoFocus);
    min->setFocusPolicy(Qt::NoFocus);
    prev->setFocusPolicy(Qt::NoFocus);

    title_mover->setFixedSize((this->width()-Close->width()-min->width()-prev->width())-36, 40);

    title_layout=new QHBoxLayout;
    title_layout->addWidget(prev, 0, Qt::AlignRight);
    title_layout->addWidget(title_mover, 0, Qt::AlignRight);
    title_layout->addWidget(min, 0, Qt::AlignRight);
    title_layout->addWidget(Close,0, Qt::AlignRight);

    title_signals();
}

void login::show_welcome()
{
    vertical_layout=new QVBoxLayout(this);
    horizontal_layout=new QHBoxLayout;

    heading=new QLabel("Welcome, PostgreSQL Client!", this);
    heading->setFont(regular);
    heading->setAlignment(Qt::AlignCenter);

    login_section=new QPushButton("Log in", this);
    signup_section=new QPushButton("Sign up", this);

    QCursor cursor(Qt::PointingHandCursor);
    login_section->setCursor(cursor);
    login_section->setFont(regular);
    login_section->setFocusPolicy(Qt::NoFocus);

    signup_section->setCursor(cursor);
    signup_section->setFont(regular);
    signup_section->setFocusPolicy(Qt::NoFocus);

    horizontal_line=new QFrame(this);
    horizontal_line->setObjectName("vLine");
    horizontal_line->setFrameShape(QFrame::VLine);
    horizontal_line->setFrameShadow(QFrame::Sunken);
    horizontal_line->setLineWidth(1);

    horizontal_layout->addWidget(login_section);
    horizontal_layout->addWidget(horizontal_line);
    horizontal_layout->addWidget(signup_section);

    vertical_layout->addLayout(title_layout);
    vertical_layout->addWidget(heading);
    vertical_layout->addLayout(horizontal_layout);
    setLayout(vertical_layout);
}

void login::show_login()
{
    connect(prev, &QPushButton::clicked, this, [=]()
            {
                delete_signin_widget();
                welcomeTitleBar();
            });

    horizontal_layout=new QHBoxLayout;
    horizontal_layout1=new QHBoxLayout;
    horizontal_layout2=new QHBoxLayout;
    vertical_layout=new QVBoxLayout(this);

    username=new QLabel(this);
    password=new QLabel(this);
    user=new QLineEdit(this);
    pass=new QLineEdit(this);
    dialog=new dialog_box(this);

    QPixmap pic;
    pic.load("://logo/icons8-username-30.png");
    username->setPixmap(pic.scaled(30,30));

    QPixmap pic1;
    pic1.load("://logo/icons8-password-30.png");
    password->setPixmap(pic1.scaled(30,30));

    regular.setPointSize(14);
    user->setPlaceholderText("Username");
    user->setFont(regular);
    pass->setPlaceholderText("Password");
    pass->setFont(regular);

    logIn=new QPushButton("LOGIN", this);
    logIn->setFixedSize(140, 35);
    logIn->setFont(regular);
    logIn->setObjectName("LoginButton");
    logIn->setFocusPolicy(Qt::NoFocus);

    remember_me=new QCheckBox("Remember me", this);
    remember_me->setFixedSize(140,45);
    remember_me->setFont(regular);
    remember_me->setObjectName("remember_box");

    username->setObjectName("username");
    user->setObjectName("user");
    password->setObjectName("password");
    pass->setObjectName("pass");

    horizontal_layout->addWidget(username);
    horizontal_layout->addWidget(user);

    horizontal_layout1->addWidget(password);
    horizontal_layout1->addWidget(pass);

    horizontal_layout2->addWidget(remember_me);
    horizontal_layout2->addWidget(logIn);

    vertical_layout->addLayout(title_layout);
    vertical_layout->addLayout(horizontal_layout);
    vertical_layout->addLayout(horizontal_layout1);
    vertical_layout->addLayout(horizontal_layout2);

    setLayout(vertical_layout);

    connect(logIn, &QPushButton::clicked, this, [=](){
        if(user->text().isEmpty()||pass->text().isEmpty())
            {
            dialog->setter("Username or Password cannot be\nempty.");
            dialog->show();
        }
        else
        {
            try{
                std::string username=user->text().toStdString();
                std::string password=pass->text().toStdString();
                pqxx::connection C("dbname=credentials user=postgres password=PGadminv12 hostaddr=127.0.0.1 port=5454");
                pqxx::nontransaction N(C);
                pqxx::result Result=N.exec_params("select username, password from data where username=$1", username);
                if(!Result.empty())
                {
                    for(pqxx::result::const_iterator i=Result.begin(); i!=Result.end(); i++)
                    {
                        if(password==i[1].as<std::string>())
                        {
                            QTimer::singleShot(500, this, [=](){
                                land->show();
                                this->close();
                            });
                        }
                        else
                        {
                            dialog->setter("Incorrect username or password.");
                            dialog->show();
                        }
                    }
                }
                else
                {
                    dialog->setter("Incorrect username or password.");
                    dialog->show();
                }
            }
            catch (const std::exception& e)
            {
                Log(e.what());
                dialog->setter(QString::fromStdString(e.what()));
                dialog->show();
            }
        }
    });

}

void login::show_signup()
{
    connect(prev, &QPushButton::clicked, this,  [=]()
            {  
                delete_signup_widget();
                welcomeTitleBar();
            });

    horizontal_layout=new QHBoxLayout;
    horizontal_layout1=new QHBoxLayout;
    horizontal_layout2=new QHBoxLayout;
    vertical_layout=new QVBoxLayout(this);

    username=new QLabel(this);
    password=new QLabel(this);
    valid=new QLabel(this);
    user=new QLineEdit(this);
    pass=new QLineEdit(this);
    dialog=new dialog_box(this);

    QPixmap pic;
    pic.load("://logo/icons8-username-30.png");
    username->setPixmap(pic.scaled(30,30));

    QPixmap pic1;
    pic1.load("://logo/icons8-password-30.png");
    password->setPixmap(pic1.scaled(30,30));

    regular.setPointSize(14);
    user->setPlaceholderText("Username");
    user->setFont(regular);
    pass->setPlaceholderText("Password");
    pass->setFont(regular);

    signUp=new QPushButton("SIGNUP", this);
    signUp->setFont(regular);
    signUp->setObjectName("Signup_button");
    signUp->setFocusPolicy(Qt::NoFocus);

    username->setObjectName("username");
    user->setObjectName("user_");
    password->setObjectName("password");
    pass->setObjectName("pass");
    valid->setObjectName("valid");

    valid->setFixedHeight(username->height());
    valid->setFixedWidth(44);

    horizontal_layout->addWidget(username);
    horizontal_layout->addWidget(user);
    horizontal_layout->addWidget(valid);

    horizontal_layout1->addWidget(password);
    horizontal_layout1->addWidget(pass);

    horizontal_layout2->addWidget(signUp);

    vertical_layout->addLayout(title_layout);
    vertical_layout->addLayout(horizontal_layout);
    vertical_layout->addLayout(horizontal_layout1);
    vertical_layout->addLayout(horizontal_layout2);

    setLayout(vertical_layout);

    try
    {
        connect(user, &QLineEdit::textChanged, this, [=]()
                {
                    if(user->text()=="")
                    {
                        flag=false;
                        valid->clear();
                    }
                    else
                    {
                        try{
                            std::string username=user->text().toStdString();
                            pqxx::connection C("dbname=credentials user=postgres password=PGadminv12 hostaddr=127.0.0.1 port=5454");
                            pqxx::nontransaction N(C);
                            pqxx::result Result=N.exec_params("select username from data where username=$1", username);
                            if(!Result.empty())
                            {
                                for(pqxx::result::const_iterator i=Result.begin(); i!=Result.end(); i++)
                                {
                                    if(username==i[0].as<std::string>())
                                    {
                                        flag=false;
                                        QPixmap pic2;
                                        pic2.load(":/logo/icons8-warning-26.png");
                                        valid->setPixmap(pic2.scaled(26,26));
                                        valid->setToolTip("Username already exists!");
                                    }
                                    else
                                    {
                                        QPixmap pic2;
                                        pic2.load(":/logo/icons8-done-26.png");
                                        valid->setPixmap(pic2.scaled(26,26));
                                        valid->setToolTip(nullptr);
                                        flag=true;
                                    }
                                }
                            }
                            else
                            {
                                QPixmap pic2;
                                pic2.load(":/logo/icons8-done-26.png");
                                valid->setPixmap(pic2.scaled(26,26));
                                valid->setToolTip(nullptr);
                                flag=true;
                            }
                        }
                        catch (const std::exception& e)
                        {
                            Log(e.what());
                        }
                    }

                });
    }
    catch(std::exception &e)
    {
        Log(e.what());
    }

    connect(signUp, &QPushButton::clicked, this, [=](){

        if(flag && pass->text().length()>=6)
        {
            try{
                std::string username=user->text().toStdString();
                std::string password=pass->text().toStdString();
                pqxx::connection C("dbname=credentials user=postgres password=PGadminv12 hostaddr=127.0.0.1 port=5454");
                pqxx::work W(C);
                pqxx::result Result=W.exec_params("insert into data(username, password) values($1, $2)", username, password);
                W.commit();
                dialog->setter("Signed up successfully. Go back to\nLog in.");
            }
            catch (const std::exception& e)
            {
                Log(e.what());
                dialog->setter(QString::fromStdString(e.what()));
            }
            user->clear();
            pass->clear();
        }
        else if(user->text()=="")
        {
            dialog->setter("Username cannot be empty.");
        }
        else if(pass->text().length()<6 && flag==false)
        {
            dialog->setter("Username already exists. Password \nmust be at least 6 characters long.");
        }
        else if(pass->text().length()<6)
         {
            dialog->setter("Password must be at least 6 characters\nlong.");
            pass->clear();
        }
        else
        {
            dialog->setter("Username already exists.");
        }
        dialog->show();
    });
}

void login::Log(std::string error)
{
    QString path=QCoreApplication::applicationDirPath()+"/Logs/log.txt";
    QFile file(path);

    // Open the file in append mode
    if (file.open(QFile::WriteOnly | QFile::Append))
    {
        QTextStream out(&file);
        out<<QString::fromStdString(error)<<QDateTime::currentDateTime().toString(Qt::TextDate)<<"\n\n";
    }
}

void login::welcome_signals()
{
    connect(login_section, &QPushButton::clicked, this, [=]()
            {
                delete_welcome_widget();
                in_WelcomeTitleBar();
                show_login();
            });
    connect(signup_section, &QPushButton::clicked, this, [=]()
            {
                delete_welcome_widget();
                in_WelcomeTitleBar();
                show_signup();
            });
}

void login::title_signals()
{
    connect(Close, &QPushButton::clicked, this, [=]()
            {
                //std::system("wscript //NoLogo laun.VBS stop");
                land->initScript(L"stop");
                this->close();
            });

    connect(min, &QPushButton::clicked, this, [=]()
            {
                this->showMinimized();
    });
}

void login::delete_welcome_widget()
{
    delete heading;
    delete login_section;
    delete signup_section;
    delete horizontal_line;

    delete Close;
    delete min;
    delete title_mover;

    delete title_layout;
    delete horizontal_layout;
    delete vertical_layout;
}

void login::delete_signin_widget()
{
    delete Close;
    delete min;
    delete prev;
    delete username;
    delete user;
    delete password;
    delete pass;
    delete remember_me;
    delete logIn;
    delete title_mover;
    delete dialog;

    delete title_layout;
    delete horizontal_layout;
    delete horizontal_layout1;
    delete horizontal_layout2;
    delete vertical_layout;
}

void login::delete_signup_widget()
{
    delete Close;
    delete min;
    delete prev;
    delete username;
    delete user;
    delete password;
    delete pass;
    delete signUp;
    delete valid;
    delete title_mover;
    delete dialog;

    delete title_layout;
    delete horizontal_layout;
    delete horizontal_layout1;
    delete horizontal_layout2;
    delete vertical_layout;
}


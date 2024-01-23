#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QWidget>
#include "landing.h"
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCursor>
#include <QPushButton>
#include <QTimer>
#include <QFontDatabase>
#include <QFont>
#include <QCheckBox>
#include <QFile>
#include "dialog_box.h"
#include "mover.h"

class login : public QWidget
{
    Q_OBJECT
public:
    explicit login(landing *parent = nullptr);
    ~login();
signals:
private:
    landing *land;
    QPushButton *logIn, *signUp, *login_section, *signup_section, *Close, *min, *prev;
    QFont regular;
    QVBoxLayout *vertical_layout;
    QHBoxLayout *horizontal_layout, *horizontal_layout1, *horizontal_layout2, *title_layout;
    QFrame *horizontal_line;
    QLabel *heading, *username, *password, *valid;
    mover *title_mover;
    QLineEdit *pass, *user;
    QCheckBox *remember_me;
    dialog_box *dialog;
    bool flag=false;

public slots:
    void show_welcome();
    void delete_welcome_widget();
    void delete_signin_widget();
    void delete_signup_widget();
    void show_login();
    void show_signup();
    void welcomeTitleBar();
    void in_WelcomeTitleBar();
    void welcome_signals();
    void title_signals();
};

#endif // LOGIN_H

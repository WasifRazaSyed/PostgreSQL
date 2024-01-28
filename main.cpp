#include <QApplication>
#include "login.h"
#include "landing.h"
#include <QDir>
#include <QTextStream>
#include <QTimer>
#include "waiting_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir data(QCoreApplication::applicationDirPath()+"/pgsql/data");
    if(!data.exists())
    {
        QString path0="set \"tempFile=\""+QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/")+"temp_file.txt\"\"";
        QString path1="\""+QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/")+"pgsql"+QDir::separator()+"bin"+QDir::separator();
        QString path2="\""+QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/")+"pgsql"+QDir::separator()+"data";
        QString temp=QDir::toNativeSeparators("\"pgPassFile=pgpass.conf\"");
        QFile file("init.bat");
        if(file.open(QFile::WriteOnly))
        {
            QTextStream stream(&file);
            stream<<"@echo off\n";
            stream<<"set \"password=passwordnew12.\"";
            stream<<"\n"<<path0<<"\n(\n echo %password%\n echo %password%\n) > %tempFile%";
            stream<<"\n"<<path1<<"initdb.exe\" -D "<<path2<<"\""<<" -U postgres --pwfile=%tempFile% -E UTF8 -A md5";
            stream<<"\ndel %tempFile%";
            stream<<"\n"<<path1<<"pg_ctl.exe\" start -D "<<path2<<"\""<<" -o \"-p 5454\"";
            stream<<"\nset "<<temp;
            stream<<"\n(\n echo localhost:5454:*:postgres:%password%\n) > %pgPassFile%";
            stream<<"\n"<<path1<<"createdb.exe\" -U postgres -h localhost -p 5454 -E UTF8 -O postgres -T template0 match";
            stream<<"\nset \"PGPASSWORD=%password%\"";
            stream<<"\n"<<path1<<"pg_ctl.exe\" stop -D "<<path2<<"\""<<" -o \"-p 5454\"";
            stream<<"\n"<<path1<<"pg_ctl.exe\" start -D"<<path2<<"\""<<" -o \"-p 5454\"";
            stream<<"\necho create table city(name varchar(255)); >script.sql";
            stream<<"\necho insert into city(name) values('lahore'); >>script.sql";
            stream<<"\n"<<path1<<"psql.exe\" -h localhost -p 5454 -U postgres -d match -a -f script.sql";
            stream<<"\n del script.sql";
            stream<<"\n"<<path1<<"pg_ctl.exe\" stop -D "<<path2<<"\""<<" -o \"-p 5454\"";
            stream<<"\n"<<"set \"PGPASSWORD=\"";
            stream<<"\necho Done > signal.txt";
            stream<<"\ndel %pgPassFile%";

            file.close();

            std::system("laun.VBS");
        }

    }


    landing land;
    login log(&land);
    waiting_widget w;
    QObject::connect(&w, &waiting_widget::showUp, [&]()
    {
        log.show();
        w.close();
        QString path0=QCoreApplication::applicationDirPath()+"/init.bat";
        QString path1=QCoreApplication::applicationDirPath()+"/signal.txt";
        QString path2=QCoreApplication::applicationDirPath()+"/laun.VBS";

        QFile file0(path0);
        QFile file1(path1);
        QFile file2(path2);

        file0.remove();
        file1.remove();
        file2.remove();
    });

    QString path_to_check=QCoreApplication::applicationDirPath()+"/laun.VBS";
    QFile checkPath(path_to_check);
    if(checkPath.exists())
    {
        w.show();
    }
    else
    {
        log.show();
    }

    return a.exec();
}

#include <QApplication>
#include "login.h"
#include "landing.h"
#include <QDir>
#include <QTextStream>
#include <QTimer>
#include "waiting_widget.h"

void createVBS();
void createBAT();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    landing land;
    login log(&land);
    waiting_widget w;
    QObject::connect(&w, &waiting_widget::showUp, [&]()
                     {
                        std::system("cscript //NoLogo laun.VBS start");
                        log.show();
                        w.close();
                        QString path0=QCoreApplication::applicationDirPath()+"/temp/init.bat";
                        QString path1=QCoreApplication::applicationDirPath()+"/temp/signal.txt";

                        QFile file0(path0);
                        QFile file1(path1);

                        file0.remove();
                        file1.remove();

                        QString temp=QCoreApplication::applicationDirPath()+"/temp";
                        QDir().rmdir(temp);
                     });


    QDir data(QCoreApplication::applicationDirPath()+"/pgsql/data");
    if(!data.exists())
    {
        w.show();
        QString appDirPath = QCoreApplication::applicationDirPath();
        QString newDirName = "temp";

        QDir appDir(appDirPath);
        QString newDirPath = appDir.filePath(newDirName);

        if (!QDir(newDirPath).exists())
        {
            QDir().mkdir(newDirPath);
        }

        QString newDirName1 = "Logs";

        QDir appDir1(appDirPath);
        QString newDirPath1 = appDir.filePath(newDirName1);

        if (!QDir(newDirPath1).exists())
        {
            QDir().mkdir(newDirPath1);
        }
        createVBS();
        createBAT();
    }
    else
    {
        std::system("cscript //NoLogo laun.VBS start");
        log.show();
    }

    return a.exec();
}

void createVBS()
{
    QString path0="\""+QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/temp/init.bat\"");

    QFile file("laun.VBS");
    if(!file.exists())
    {
        if(file.open(QFile::WriteOnly))
        {
            QTextStream stream(&file);
            stream<<"Set WshShell = CreateObject(\"WScript.Shell\")";
            stream<<"\nIf WScript.Arguments.Count > 0 Then";
            stream<<"\n    For Each arg In WScript.Arguments";
            stream<<"\n       If arg = \"init\" Then";
            stream<<"\n           WshShell.Run chr(34) & "<<path0<<" & Chr(34), 0";
            stream<<"\n       ElseIf arg = \"start\" Then";
            stream<<"\n           WshShell.Run chr(34) & \"pg_at.bat\" & Chr(34), 0";
            stream<<"\n       ElseIf arg = \"stop\" Then";
            stream<<"\n           WshShell.Run chr(34) & \"pg_op.bat\" & Chr(34), 0";
            stream<<"\n       Else";
            stream<<"\n       End If";
            stream<<"\n    Next"<<"\nElse"<<"\nEnd If"<<"\nSet WshShell = Nothing";

            file.close();
        }
    }
}

void createBAT()
{
    QString path0="set \"tempFile=\""+QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/"+"temp/")+"temp_file.txt\"\"";
    QString path1="\""+QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/")+"pgsql"+QDir::separator()+"bin"+QDir::separator();
    QString path2="\""+QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/")+"pgsql"+QDir::separator()+"data";
    QString temp0="\"pgPassFile=pgpass.conf\"";
    QString temp1=QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/temp/script.sql\"");
    QString temp2=QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/temp/signal.txt\"");
    QString init=QCoreApplication::applicationDirPath()+"/temp/init.bat";
    QFile file0(init);
    if(file0.open(QFile::WriteOnly))
    {
        QTextStream stream(&file0);
        stream<<"@echo off\n";
        stream<<"set \"password=PGadminv12\"";
        stream<<"\n"<<path0<<"\n(\n echo %password%\n echo %password%\n) > %tempFile%";
        stream<<"\n"<<path1<<"initdb.exe\" -D "<<path2<<"\""<<" -U postgres --pwfile=%tempFile% -E UTF8 -A md5";
        stream<<"\ndel %tempFile%";
        stream<<"\n"<<path1<<"pg_ctl.exe\" start -D "<<path2<<"\""<<" -o \"-p 5454\"";
        stream<<"\nset "<<temp0;
        stream<<"\n(\n echo localhost:5454:*:postgres:%password%\n) > %pgPassFile%";
        stream<<"\n"<<path1<<"createdb.exe\" -U postgres -h localhost -p 5454 -E UTF8 -O postgres -T template0 credentials";
        stream<<"\nset \"PGPASSWORD=%password%\"";
        stream<<"\n"<<path1<<"pg_ctl.exe\" stop -D "<<path2<<"\""<<" -o \"-p 5454\"";
        stream<<"\n"<<path1<<"pg_ctl.exe\" start -D"<<path2<<"\""<<" -o \"-p 5454\"";
        stream<<"\necho create table data(username varchar(255), password varchar(255)); > \""<<temp1;
        stream<<"\necho insert into data(username, password) values('admin', 'postgres'); >> \""<<temp1;
        stream<<"\n"<<path1<<"psql.exe\" -h localhost -p 5454 -U postgres -d credentials -a -f \""<<temp1;
        stream<<"\n del \""<<temp1;
        stream<<"\n"<<path1<<"pg_ctl.exe\" stop -D "<<path2<<"\""<<" -o \"-p 5454\"";
        stream<<"\n"<<"set \"PGPASSWORD=\"";
        stream<<"\necho Done > \""<<temp2;
        stream<<"\ndel %pgPassFile%";

        file0.close();

        std::system("cscript //NoLogo laun.VBS init");
    }

    QFile file1("pg_at.bat");
    if(!file1.exists())
    {
        if(file1.open(QFile::WriteOnly))
        {
            QTextStream stream(&file1);
            stream<<"@echo off\n";
            stream<<path1<<"pg_ctl.exe\" -D "<<path2<<"\" -o \"-p 5454\" start";

            file1.close();
        }
    }

    QFile file2("pg_op.bat");
    if(!file2.exists())
    {
        if(file2.open(QFile::WriteOnly))
        {
            QTextStream stream(&file2);
            stream<<"@echo off\n";
            stream<<path1<<"pg_ctl.exe\" -D "<<path2<<"\" -o \"-p 5454\" stop";

            file2.close();
        }
    }
}

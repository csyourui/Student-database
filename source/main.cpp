#include "mainwindow.h"
#include "logindig.h"
#include "admin.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置app的图标
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    a.setWindowIcon(QIcon(":/scutlogo.png"));
    DataBase d;
    d.createConnection();
    d.createTable();
    d.insert();
    d.queryAll();

    LoginDig w;
    w.show();
    return a.exec();
}

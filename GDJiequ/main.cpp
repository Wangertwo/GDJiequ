#include "mainwindow.h"
#include "gdlogindialog.h"
#include "gdregisterdialog.h"
#include "gduserclient.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include "const.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("demo");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("wgy3258642106");
    if(!db.open()) {
        qDebug() << "打开数据库失败，错误信息:\n"+db.lastError().text();
        return 0;
    }else {
        qDebug() << "数据库打开成功~";
        // GDLoginDialog *loginDialog = new GDLoginDialog();
        // if(loginDialog->exec() == QDialog::Accepted) {
            GDUserClient userClient;
            userClient.show();
        //     return a.exec();
        // }else {
        //     return 0;
        // }
            a.exec();
    }
}


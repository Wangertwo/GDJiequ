#ifndef GDUSERCLIENT_H
#define GDUSERCLIENT_H

#include <QMainWindow>
#include "gdherodatabase.h"
#include "gdweapondatabase.h"
namespace Ui {
class GDUserClient;
}

class GDUserClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit GDUserClient(QWidget *parent = nullptr);
    ~GDUserClient();

private slots:
    void pBtnHeroClicked();
    void pBtnWeaponClicked();
    void destroyHeroDatabase(QObject* ob);
    void destroyWeaponDatabase(QObject* ob);
private:
    Ui::GDUserClient *ui;
    GDHeroDatabase *heroDatabase;
    GDWeaponDatabase *weaponDatabase;
};

#endif // GDUSERCLIENT_H

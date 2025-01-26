#include "gduserclient.h"
#include "ui_gduserclient.h"

GDUserClient::GDUserClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GDUserClient)
{
    ui->setupUi(this);
    this->setFixedSize(973, 860);

    connect(ui->pBtnHero, SIGNAL(clicked()), this, SLOT(pBtnHeroClicked()));
    connect(ui->pBtnWeapons, SIGNAL(clicked()), this, SLOT(pBtnWeaponClicked()));
}

GDUserClient::~GDUserClient()
{
    delete ui;
}

void GDUserClient::pBtnHeroClicked()
{ // 查看英雄库
    heroDatabase = new GDHeroDatabase();
    heroDatabase->show();
    ui->pBtnHero->blockSignals(true); // 屏蔽信号
    connect(heroDatabase, SIGNAL(destroyed(QObject*)), this, SLOT(destroyHeroDatabase(QObject*)));
}

void GDUserClient::pBtnWeaponClicked()
{ // 查看武器库
    weaponDatabase = new GDWeaponDatabase();
    weaponDatabase->show();
    ui->pBtnWeapons->blockSignals(true); // 屏蔽信号
    connect(weaponDatabase, SIGNAL(destroyed(QObject*)), this, SLOT(destroyWeaponDatabase(QObject*)));
}

void GDUserClient::destroyWeaponDatabase(QObject *ob)
{   // 当 weaponDatabase窗体被关闭时，发出信号
    Q_UNUSED(ob);
    ui->pBtnWeapons->blockSignals(false);
}

void GDUserClient::destroyHeroDatabase(QObject* ob)
{ // 当 heroDatabase窗体被关闭时，发出信号
    Q_UNUSED(ob);
    ui->pBtnHero->blockSignals(false);
}

#ifndef GDWEAPONDATABASE_H
#define GDWEAPONDATABASE_H

#include <QMainWindow>
#include <QFile>
#include <QLatin1String>
#include <QStyleOption>
#include <QPainter>
#include <QSoundEffect>
#include <QtMultimedia/QMediaPlayer>
#include "gdopenprojectwizard.h"
#include "gdprojecttree.h"
#include "gdpictureshowdialog.h"
namespace Ui {
class GDWeaponDatabase;
}

class GDWeaponDatabase : public QMainWindow
{
    Q_OBJECT

public:
    explicit GDWeaponDatabase(QWidget *parent = nullptr);
    ~GDWeaponDatabase();
    void initForm();
    void initMenu();
    void initStyle();
    void paintEvent(QPaintEvent *);

private slots:
    void actNewProTriggered();
    void actOpenProTriggered();
    void actSetMusicTriggered();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    Ui::GDWeaponDatabase *ui;
    GDOpenProjectWizard *projectWizard;
    GDProjectTree *projectTree;
    GDPictureShowDialog *pictureShow;
    QMediaPlayer *m_player;
signals:
    void emitOpenProject(const QString srcPath);
};

#endif // GDWEAPONDATABASE_H

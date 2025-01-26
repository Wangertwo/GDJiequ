#include "gdopenprojectwizard.h"
#include "ui_gdopenprojectwizard.h"

GDOpenProjectWizard::GDOpenProjectWizard(QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::GDOpenProjectWizard)
{
    ui->setupUi(this);
}

GDOpenProjectWizard::~GDOpenProjectWizard()
{
    delete ui;
}

void GDOpenProjectWizard::done(int result)
{ // 点击 finish 后的处理
    if(result == QFileDialog::Rejected) {
        return QWizard::done(result);
    }

    QString name, path;
    ui->projectSetPage->getProjectSetting(name, path);
    emit emitProjectSetting(name, path);
    return QWizard::done(result);
}

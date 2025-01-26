#include "gdconfirmwizardpage.h"
#include "ui_gdconfirmwizardpage.h"

GDConfirmWizardPage::GDConfirmWizardPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::GDConfirmWizardPage)
{
    ui->setupUi(this);
}

GDConfirmWizardPage::~GDConfirmWizardPage()
{
    delete ui;
}

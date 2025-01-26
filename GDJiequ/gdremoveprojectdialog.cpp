#include "gdremoveprojectdialog.h"
#include "ui_gdremoveprojectdialog.h"

GDRemoveProjectDialog::GDRemoveProjectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GDRemoveProjectDialog)
{
    ui->setupUi(this);
}

GDRemoveProjectDialog::~GDRemoveProjectDialog()
{
    delete ui;
}

bool GDRemoveProjectDialog::is_remove()
{
    return ui->checkBox->isChecked();
}

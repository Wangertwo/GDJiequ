#include "gdplannerdatabase.h"
#include "ui_gdplannerdatabase.h"

GDPlannerDatabase::GDPlannerDatabase(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GDPlannerDatabase)
{
    ui->setupUi(this);
}

GDPlannerDatabase::~GDPlannerDatabase()
{
    delete ui;
}

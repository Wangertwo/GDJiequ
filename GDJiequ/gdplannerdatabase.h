#ifndef GDPLANNERDATABASE_H
#define GDPLANNERDATABASE_H

#include <QMainWindow>

namespace Ui {
class GDPlannerDatabase;
}

class GDPlannerDatabase : public QMainWindow
{
    Q_OBJECT

public:
    explicit GDPlannerDatabase(QWidget *parent = nullptr);
    ~GDPlannerDatabase();

private:
    Ui::GDPlannerDatabase *ui;
};

#endif // GDPLANNERDATABASE_H

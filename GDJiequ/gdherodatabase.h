#ifndef GDHERODATABASE_H
#define GDHERODATABASE_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QItemSelectionModel>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QDataWidgetMapper>
#include <QSqlRecord>
#include <QFileDialog>
#include <QLatin1String>
#include "gdcombodelegate.h"
#include "gdreadonlydelegate.h"
namespace Ui {
class GDHeroDatabase;
}

class GDHeroDatabase : public QMainWindow
{
    Q_OBJECT

public:
    explicit GDHeroDatabase(QWidget *parent = nullptr);
    ~GDHeroDatabase();
    void initForm();
    void openTable();
    void refreshTableView();
    void getFieldNames();
private slots:
    void on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void actOpenTriggered();
    void actAppendHeroTriggered();
    void actInsertHeroTriggered();
    void actDeleteHeroTriggered();
    void actFirstHeroTriggered();
    void actLastHeroTriggered();
    void actPreviousTriggered();
    void actNextTriggered();
    void actSubmitTriggered();
    void actRevertTriggered();
    void actLoadPhotoTriggered();
    void rBtnAscClicked();
    void rBtnDesClicked();
    void comboOrderFieldCurrentIndexChanged(int index);
    void pBtnSearchClicked();
private:
    Ui::GDHeroDatabase *ui;
    QSqlRelationalTableModel *theRelationalModel;
    QItemSelectionModel *theSelection;
    QSqlDatabase db;
    QDataWidgetMapper *dataMapper;
    GDComboDelegate *comboDelegate;
    GDReadOnlyDelegate *readOnlyDelegate;

};

#endif // GDHERODATABASE_H

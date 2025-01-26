#ifndef GDREGISTERDIALOG_H
#define GDREGISTERDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QRegularExpression>

namespace Ui {
class GDRegisterDialog;
}

class GDRegisterDialog : public QDialog
{
    Q_OBJECT

private slots:
    void pBtnOkTriggered();

public:
    explicit GDRegisterDialog(QWidget *parent = nullptr);
    ~GDRegisterDialog();
    void initForm();

private:
    Ui::GDRegisterDialog *ui;
    QList<int> mapNoList;

};

#endif // GDREGISTERDIALOG_H

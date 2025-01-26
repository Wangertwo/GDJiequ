#ifndef GDREMOVEPROJECTDIALOG_H
#define GDREMOVEPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class GDRemoveProjectDialog;
}

class GDRemoveProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GDRemoveProjectDialog(QWidget *parent = nullptr);
    ~GDRemoveProjectDialog();
    bool is_remove();
private:
    Ui::GDRemoveProjectDialog *ui;
};

#endif // GDREMOVEPROJECTDIALOG_H

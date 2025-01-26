#ifndef GDOPENPROJECTWIZARD_H
#define GDOPENPROJECTWIZARD_H

#include <QWizard>

namespace Ui {
class GDOpenProjectWizard;
}

class GDOpenProjectWizard : public QWizard
{
    Q_OBJECT

public:
    explicit GDOpenProjectWizard(QWidget *parent = nullptr);
    ~GDOpenProjectWizard();

protected:
    void done(int result) override; // 重写done函数

private:
    Ui::GDOpenProjectWizard *ui;

signals:
    void emitProjectSetting(const QString &name, const QString &path);
};

#endif // GDOPENPROJECTWIZARD_H

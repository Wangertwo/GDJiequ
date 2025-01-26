#ifndef GDPROJECTSETWIZARDPAGE_H
#define GDPROJECTSETWIZARDPAGE_H

#include <QWizardPage>
#include <QDir>
#include <QFileDialog>
namespace Ui {
class GDProjectSetWizardPage;
}

class GDProjectSetWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit GDProjectSetWizardPage(QWidget *parent = nullptr);
    ~GDProjectSetWizardPage();
    void getProjectSetting(QString &name, QString &path);

private slots:
    void lEditNameTextEdited(QString text);
    void lEditPathTextEdited(QString text);
    void pBtnBrowseClicked();
protected:
    virtual bool isComplete() const;

private:
    Ui::GDProjectSetWizardPage *ui;
};

#endif // GDPROJECTSETWIZARDPAGE_H

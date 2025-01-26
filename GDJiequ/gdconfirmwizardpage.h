#ifndef GDCONFIRMWIZARDPAGE_H
#define GDCONFIRMWIZARDPAGE_H

#include <QWizardPage>

namespace Ui {
class GDConfirmWizardPage;
}

class GDConfirmWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit GDConfirmWizardPage(QWidget *parent = nullptr);
    ~GDConfirmWizardPage();

private:
    Ui::GDConfirmWizardPage *ui;
};

#endif // GDCONFIRMWIZARDPAGE_H

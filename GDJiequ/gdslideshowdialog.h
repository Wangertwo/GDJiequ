#ifndef GDSLIDESHOWDIALOG_H
#define GDSLIDESHOWDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
namespace Ui {
class GDSlideShowDialog;
}

class GDSlideShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GDSlideShowDialog(QWidget *parent = nullptr, QTreeWidgetItem *firstItem = nullptr, QTreeWidgetItem *lastItem = nullptr);
    ~GDSlideShowDialog();

private:
    Ui::GDSlideShowDialog *ui;
    QTreeWidgetItem *m_firstItem;
    QTreeWidgetItem *m_lastItem;
private slots:
    void pBtnCloseClicked();
    void pBtnPreviousClicked();
    void pBtnNextClicked();
    void pBtnShowClicked();
    void slotSetShowBtnClose();
};

#endif // GDSLIDESHOWDIALOG_H

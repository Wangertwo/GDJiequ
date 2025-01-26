#ifndef GDPICTURESHOWDIALOG_H
#define GDPICTURESHOWDIALOG_H

#include <QDialog>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
namespace Ui {
class GDPictureShowDialog;
}

class GDPictureShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GDPictureShowDialog(QWidget *parent = nullptr);
    ~GDPictureShowDialog();
    QString getSelected_path() const;
    void reloadPicture();
protected:
    bool event(QEvent *event) override;


private:
    Ui::GDPictureShowDialog *ui;
    void setPreNextButtonAnimation(bool is_show);
    QPropertyAnimation *preBtn_Animation;
    QPropertyAnimation *nextBtn_Animation;
    QString selected_path;
    bool pBtnVisible;
    QPixmap show_picture;
public slots:
    void slotShowItem(QString showItemPath);
    void slotSendClickedSignal();
    void slotRemovePicture();
signals:
    void emitClickedPreBtn(QString objectName);
    void emitClickedNextBtn(QString objectName);
};

#endif // GDPICTURESHOWDIALOG_H

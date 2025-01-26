#ifndef GDANIMATIONSHOW_H
#define GDANIMATIONSHOW_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QTreeWidgetItem>
#include <QMap>
#include <QPainter>
class GDAnimationShow : public QWidget
{
    Q_OBJECT
public:
    explicit GDAnimationShow(QWidget *parent = nullptr);
    ~GDAnimationShow();
    void stop();
    void start();
    void setPixmap(QTreeWidgetItem* item);
    void pBtnPreviousClicked();
    void pBtnNextClicked();
    void pBtnShowOpen();
    void pBtnShowClose();
private:
    QTimer *m_timer;
    QTreeWidgetItem *m_currentItem;
    double m_factor;
    QPixmap m_pixmap1; // 双缓冲绘图
    QPixmap m_pixmap2;
    bool m_showState;
    QMap<QString, QTreeWidgetItem*> m_itemMap;

protected:
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void slotTimeout();
public slots:
    void slotUpdateShift(QString path);

signals:
    void emitUpdatePreList(QTreeWidgetItem* item);
    void emitUpdateSelect(QTreeWidgetItem* item);
    void emitSetShowBtnClose();
};

#endif // GDANIMATIONSHOW_H

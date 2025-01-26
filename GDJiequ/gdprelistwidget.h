#ifndef GDPRELISTWIDGET_H
#define GDPRELISTWIDGET_H

#include <QListWidget>
#include <QObject>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QPixmap>
#include <QPainter>
#include <QListWidgetItem>
class GDPreListWidget : public QListWidget
{
    Q_OBJECT
public:
    GDPreListWidget(QWidget *parent = nullptr);
    ~GDPreListWidget();
private:
    int m_index; // 存储图标项的索引
    int m_lastIndex; // 记录上一个图标项的位置
    QPoint m_origin; // 第一张图标项的位置
    QListWidgetItem *m_currentItem; // 缓存当前项
    QMap<QString, QListWidgetItem*> m_set_items; // 存储图标项

public slots:
    void slotUpdatePreList(QTreeWidgetItem *item);
    void slotUpdateSelect(QTreeWidgetItem *item);
    void on_itemClicked(QListWidgetItem *item);

signals:
    void emitUpdateShift(QString path);
};    

#endif // GDPRELISTWIDGET_H

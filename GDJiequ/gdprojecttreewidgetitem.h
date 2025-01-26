#ifndef GDPROJECTTREEWIDGETITEM_H
#define GDPROJECTTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QDir>
class GDProjectTreeWidgetItem : public QTreeWidgetItem
{
public:
    GDProjectTreeWidgetItem(QTreeWidget *treeview, QString name, QString path, int type);
    GDProjectTreeWidgetItem(QTreeWidgetItem *parent, QString name, QString path, QTreeWidgetItem *root, int type);
    ~GDProjectTreeWidgetItem();
    QString getName() const;
    void setName(const QString &newName);
    QString getPath() const;
    void setPath(const QString &newPath);
    GDProjectTreeWidgetItem *getPreviousItem();
    GDProjectTreeWidgetItem *getNextItem();
    void setPreviousItem(QTreeWidgetItem *item);
    void setNextItem(QTreeWidgetItem *item);
    GDProjectTreeWidgetItem *getLastPicChild();
    GDProjectTreeWidgetItem *getFirstPicChild();
    void setRoot(QTreeWidgetItem *item);
    GDProjectTreeWidgetItem *getRoot();

private:
    QString m_name;
    QString m_path;
    QTreeWidgetItem *m_root;
    QTreeWidgetItem *m_previousItem;
    QTreeWidgetItem *m_nextItem;
    QTreeWidgetItem *m_lastPicChild;
    QTreeWidgetItem *m_firstPicChild;

};

#endif // GDPROJECTTREEWIDGETITEM_H

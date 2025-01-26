#ifndef GDPROJECTTREETHREAD_H
#define GDPROJECTTREETHREAD_H

#include <QObject>
#include <QThread>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>
#include <QFile>
#include "gdprojecttreewidgetitem.h"

class GDProjectTreeThread : public QThread
{
    Q_OBJECT
public:
    GDProjectTreeThread(const QString &srcPath, const QString &dstPath, QTreeWidget *baseTree, QTreeWidgetItem *root,
                        QTreeWidgetItem *previousItem, QTreeWidgetItem *nextItme, QTreeWidgetItem *parentItem, int &fileCount, QObject *parent = nullptr);
    ~GDProjectTreeThread();

    QString getSrcPath() const;
    QString getDstPath() const;
    int fileCount() const;
    QTreeWidget *getBaseTree() const;
    GDProjectTreeWidgetItem *getRoot() const;
    GDProjectTreeWidgetItem *getPreviousItem() const;
    GDProjectTreeWidgetItem *getNextItem() const;
    GDProjectTreeWidgetItem *getParentItem() const;


    void createProjectTree(const QString &srcPath, const QString &dstPath, QTreeWidget *baseWidget, QTreeWidgetItem *root, QTreeWidgetItem *previousItem, int &fileCount, QTreeWidgetItem *parentItem);

protected:
    virtual void run();

private:
    QString m_srcPath;
    QString m_dstPath;
    int m_fileCount;
    QTreeWidget *m_baseTree;
    QTreeWidgetItem *m_root;
    QTreeWidgetItem *m_previousItem;
    QTreeWidgetItem *m_nextItem;
    QTreeWidgetItem *m_parentItem;
    bool _stop = false; // 控制线程的关闭，保证逻辑上的准确性
    bool _copy; // 是否可以拷贝到目录树

public slots:
    void slotStopThread();

signals:
    void emitProgressFinished(int fileCount);
    void emitUpdateProgress(int fileCount);
};

#endif // GDPROJECTTREETHREAD_H

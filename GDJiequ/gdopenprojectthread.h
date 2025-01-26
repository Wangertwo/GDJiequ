#ifndef GDOPENPROJECTTHREAD_H
#define GDOPENPROJECTTHREAD_H

#include <QObject>
#include <QThread>
#include <QWidget>
#include <QTreeWidget>
#include <QDir>
class GDOpenProjectThread : public QThread
{
    Q_OBJECT
public:
    explicit GDOpenProjectThread(const QString &srcPath, int fileCount, QTreeWidget *baseWidget, QTreeWidgetItem *_root, QTreeWidgetItem *_parentItem, QTreeWidgetItem *_previousItem, QObject *parent = nullptr);
    ~GDOpenProjectThread();
    void createProjectRecursively(const QString &srcPath, int fileCount, QTreeWidget *baseWidget, QTreeWidgetItem *root, QTreeWidgetItem *parentItem,
                                QTreeWidgetItem *previousItem);
private:
    QString m_srcPath;
    int m_fileCount;
    QTreeWidget *m_baseWidget;
    QTreeWidgetItem *m_root;
    QTreeWidgetItem *m_parentItem;
    QTreeWidgetItem *m_previousItem;
    bool m_stop;

protected:
    virtual void run();

public slots:
    void slotCancelProgress();

signals:
    void emitUpdateProgress(int fileCount);
    void emitFinishedProgress(int fileCount);
};

#endif // GDOPENPROJECTTHREAD_H

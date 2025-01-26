#ifndef GDPROJECTTREEWIDGET_H
#define GDPROJECTTREEWIDGET_H

#include <QTreeWidget>
#include <QDir>
#include <QIcon>
#include <QTreeWidgetItem>
#include <QProgressDialog>
#include <QSet>
#include "gdprojecttreewidgetitem.h"
#include "gdopenprojectthread.h"
#include "gdprojecttree.h"

class GDProjectTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    GDProjectTreeWidget(QWidget *parent = nullptr);
    ~GDProjectTreeWidget();
    void addProjectToTreeView(const QString &name, const QString &path);
    void addOpenProjectToTreeView(const QString &srcPath);

private:
    std::shared_ptr<GDOpenProjectThread> openProjectThread; // 智能指针管理线程
    QProgressDialog *progressDialog = nullptr;
    GDProjectTree *projectTree;

private slots:
    void slotUpdateProgress(int count);
    void slotFinishedProgress(int count);
    void slotSendCancelSignal();

signals:
    void emitCancelProgress();
};

#endif // GDPROJECTTREEWIDGET_H

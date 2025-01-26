#ifndef GDPROJECTTREE_H
#define GDPROJECTTREE_H

#include <QDialog>
#include <QGuiApplication>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QProgressDialog>
#include "gdprojecttreethread.h"
#include "gdremoveprojectdialog.h"

class GDSlideShowDialog; // 前向引用，防止互引用的方法之一

namespace Ui {
class GDProjectTree;
}

class GDProjectTree : public QDialog
{
    Q_OBJECT

public:
    explicit GDProjectTree(QWidget *parent = nullptr);
    ~GDProjectTree();

    QTreeWidgetItem *getSelected_item() const;

    QSet<QString> getPath_set() const;
    void setPath_set(const QSet<QString> &newPath_set);
    void insertPath(QString path);

private:
    Ui::GDProjectTree *ui;
    QSet<QString> path_set; // 路径集
    QTreeWidgetItem *item_buffer; // 缓存右击的项
    QTreeWidgetItem *active_item; // 缓存活跃的项
    QTreeWidgetItem *selected_item; // 缓存双击左键选中的项
    QAction *actImport;
    QAction *actSetStart; // 设置活跃状态
    QAction *actDelete;
    QAction *actSlideShow;
    QProgressDialog *progressDialog;
    std::shared_ptr<GDProjectTreeThread> createProThread; // 智能指针
    std::shared_ptr<GDSlideShowDialog> slideShowDialog;
private slots:
    void addProjectSettingToTreeWdiget(const QString &name, const QString &path);
    void addOpenProjectSettingToTreeWidget(const QString srcPath);
    void on_itemPressed(QTreeWidgetItem *item, int column);
    void on_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void actImportTriggered();
    void actDeleteTriggered();
    void actSetStartTriggered();
    void actSlideShowTriggered();
    void slotUpdateProgress(int count);
    void slotProgressFinished(int count);
    void slotSendCancelSignal();

protected slots:
    void slotSendUpdatePictureSignal(QString objectName);

signals:
    void emitCancelSignal();
    void emitShowItem(QString show_item);
    void emitUpdatePicture(QString show_path);
    void emitRemovePicture();
};

#endif // GDPROJECTTREE_H

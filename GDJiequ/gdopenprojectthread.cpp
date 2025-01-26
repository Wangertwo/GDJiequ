#include "gdopenprojectthread.h"
#include "gdprojecttreewidgetitem.h"
#include "const.h"
GDOpenProjectThread::GDOpenProjectThread(const QString &srcPath, int fileCount, QTreeWidget *baseWidget, QTreeWidgetItem *_root, QTreeWidgetItem *_parentItem, QTreeWidgetItem *_previousItem, QObject *parent)
    :QThread(parent), m_srcPath(srcPath), m_fileCount(fileCount), m_baseWidget(baseWidget), m_root(_root), m_parentItem(_parentItem), m_previousItem(_previousItem), m_stop(false)
{

}

GDOpenProjectThread::~GDOpenProjectThread()
{

}

void GDOpenProjectThread::createProjectRecursively(const QString &srcPath, int fileCount, QTreeWidget *baseWidget, QTreeWidgetItem *root, QTreeWidgetItem *parentItem, QTreeWidgetItem *previousItem)
{ // 递归遍历创建项目
    if(m_stop) {
        return;
    }
    QDir src_dir(srcPath);
    src_dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList fileInfoList = src_dir.entryInfoList();
    if(fileInfoList.isEmpty()) return;
    for(int i = 0; i < fileInfoList.size(); i++) {
        if(m_stop) {
            return;
        }
        QFileInfo curFileInfo = fileInfoList.at(i);
        QString curFileName = curFileInfo.fileName();
        bool is_dir = curFileInfo.isDir();
        if(is_dir) { // 当前文件是一个目录，需递归遍历
            if(m_stop) {
                return;
            }
            fileCount++;
            emit emitUpdateProgress(fileCount);
            auto item = new GDProjectTreeWidgetItem(parentItem, curFileName, curFileInfo.absoluteFilePath(), root, TreeItemDir);
            item->setData(0, Qt::DecorationRole, QIcon(":/icon/icon/dir.png"));
            baseWidget->addTopLevelItem(item);
            createProjectRecursively(curFileInfo.absoluteFilePath(), fileCount, baseWidget, root, item, previousItem);
        }else { // 当前文件不是一个目录
            if(m_stop) {
                return;
            }
            auto curSuffix = curFileInfo.suffix();
            if(curSuffix != "png" && curSuffix != "jpg" && curSuffix != "jpeg") {
                continue;
            }
            fileCount++;
            emit emitUpdateProgress(fileCount);
            auto item = new GDProjectTreeWidgetItem(parentItem, curFileName, curFileInfo.absoluteFilePath(), root, TreeItemPic);
            // qDebug() << item->getRoot()->getPath() + "节点";
            item->setData(0, Qt::DecorationRole, QIcon(":/icon/icon/pic.png"));
            auto preItem = dynamic_cast<GDProjectTreeWidgetItem*>(previousItem);
            if(previousItem && previousItem->type() == TreeItemPic) {
                preItem->setNextItem(item);
            }
            item->setPreviousItem(previousItem);
            previousItem = item;
            baseWidget->addTopLevelItem(item);
        }
    }
}

void GDOpenProjectThread::run()
{ //
    createProjectRecursively(m_srcPath, m_fileCount, m_baseWidget, m_root, m_parentItem, m_previousItem);
    if(m_stop) {
        auto index = m_baseWidget->indexOfTopLevelItem(m_root);
        delete m_baseWidget->takeTopLevelItem(index);
        return;
    }
    emit emitFinishedProgress(m_fileCount);
}

void GDOpenProjectThread::slotCancelProgress()
{ // 结束当前线程
    m_stop = true;
}

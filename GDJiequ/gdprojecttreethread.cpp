#include "gdprojecttreethread.h"
#include "const.h"
GDProjectTreeThread::GDProjectTreeThread(const QString &srcPath, const QString &dstPath, QTreeWidget *baseTree,
                                         QTreeWidgetItem *root, QTreeWidgetItem *previousItem, QTreeWidgetItem *nextItem, QTreeWidgetItem *parentItem, int &fileCount, QObject *parent)
    : QThread(parent),m_srcPath(srcPath), m_dstPath(dstPath), m_baseTree(baseTree), m_previousItem(previousItem), m_nextItem(nextItem), m_root(root), m_parentItem(parentItem), m_fileCount(fileCount)
{

}

GDProjectTreeThread::~GDProjectTreeThread()
{

}

void GDProjectTreeThread::createProjectTree(const QString &srcPath, const QString &dstPath, QTreeWidget *baseWidget, QTreeWidgetItem *root, QTreeWidgetItem *previousItem, int &fileCount, QTreeWidgetItem *parentItem)
{ // 递归创建目录树

    if(_stop) {
        return;
    }
    _copy = true;
    if(srcPath.isEmpty()) {
        return;
    }
    QDir _srcPath(srcPath);
    _srcPath.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    _srcPath.setSorting(QDir::Name);
    QFileInfoList src_fileInfo_list = _srcPath.entryInfoList();
    if(src_fileInfo_list.length() <= 0) {
        return;
    }
    for(int i = 0; i < src_fileInfo_list.size(); i++) {
        if(_stop) {
            return;
        }
        QFileInfo curFile = src_fileInfo_list.at(i);
        bool curFileIsDir = curFile.isDir(); // 判断当前文件是否为目录
        if(curFileIsDir) { // 当前文件是一个目录
            if(_stop) {
                return;
            }
            fileCount++;
            emit emitUpdateProgress(fileCount);

            QDir dstDir(dstPath);
            QString abs_dstPath = dstDir.absoluteFilePath(curFile.fileName());
            QDir abs_dstPath_dir(abs_dstPath);
            if(!abs_dstPath_dir.exists()) {
                bool ok = abs_dstPath_dir.mkpath(abs_dstPath);
                if(!ok) {
                    continue;
                }
            }
            auto item = new GDProjectTreeWidgetItem(parentItem, curFile.fileName(), abs_dstPath, root, TreeItemDir);
            item->setData(0, Qt::DecorationRole, QIcon(":/icon/icon/dir.png"));
            createProjectTree(curFile.absoluteFilePath(), abs_dstPath, baseWidget, root, previousItem, fileCount, item);
        }else { // 当前文件不是一个目录
            if(_stop) {
                return;
            }
            QString filename = curFile.fileName();
            QString curFileSuffix = curFile.suffix(); // 取到当前文件后缀
            if(curFileSuffix != "png" && curFileSuffix != "jpg" && curFileSuffix != "jpeg") {
                continue;
            }
            fileCount++;
            emit emitUpdateProgress(fileCount);
            QDir _dstPath(dstPath);
            QString abs_dstPath = _dstPath.absoluteFilePath(filename); // 得到拼接完成的绝对路径
            QDir abs_dstPath_dir(abs_dstPath);
            if(!QFile::copy(curFile.absoluteFilePath(), abs_dstPath)) {
                qDebug("copy src to dst failed");
                continue;
            }
            auto item = new GDProjectTreeWidgetItem(parentItem, filename, abs_dstPath, root, TreeItemPic);
            item->setData(0, Qt::DecorationRole, QIcon(":/icon/icon/pic.png"));
            auto pro_previousItem = dynamic_cast<GDProjectTreeWidgetItem*>(previousItem);
            if(previousItem) {
                pro_previousItem->setNextItem(item);
            }
            item->setPreviousItem(previousItem);
            previousItem = item;
            baseWidget->addTopLevelItem(item); // 添加项
        }
    }
    //parentItem->setExpanded(true);
}

void GDProjectTreeThread::run()
{ // 重写
    qDebug() << "start run";
    createProjectTree(m_srcPath, m_dstPath, m_baseTree, m_root, m_previousItem, m_fileCount, m_parentItem);
    if(_stop) { // 取消之前操作
        auto path = dynamic_cast<GDProjectTreeWidgetItem*>(m_root)->getPath();
        int index = m_baseTree->indexOfTopLevelItem(m_root);
        delete m_baseTree->takeTopLevelItem(index); // 根据索引删除
        QDir dir(path);
        dir.removeRecursively(); // 删除路径下的所有拷贝文件
        return;
    }
    // 执行完成
    emit emitProgressFinished(m_fileCount);
}

void GDProjectTreeThread::slotStopThread()
{ // 结束当前正在执行的线程
    _stop = true;
}

int GDProjectTreeThread::fileCount() const
{
    return m_fileCount;
}


QString GDProjectTreeThread::getSrcPath() const
{
    return m_srcPath;
}

QString GDProjectTreeThread::getDstPath() const
{
    return m_dstPath;
}

QTreeWidget *GDProjectTreeThread::getBaseTree() const
{
    return m_baseTree;
}

GDProjectTreeWidgetItem *GDProjectTreeThread::getRoot() const
{
    return dynamic_cast<GDProjectTreeWidgetItem*>(m_root);
}

GDProjectTreeWidgetItem *GDProjectTreeThread::getPreviousItem() const
{
    return dynamic_cast<GDProjectTreeWidgetItem*>(m_previousItem);
}

GDProjectTreeWidgetItem *GDProjectTreeThread::getNextItem() const
{
    return dynamic_cast<GDProjectTreeWidgetItem*>(m_nextItem);
}

GDProjectTreeWidgetItem *GDProjectTreeThread::getParentItem() const
{
    return dynamic_cast<GDProjectTreeWidgetItem*>(m_parentItem);
}



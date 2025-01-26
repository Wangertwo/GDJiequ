#include "gdprojecttreewidget.h"
#include "const.h"

GDProjectTreeWidget::GDProjectTreeWidget(QWidget *parent) {
    this->setHeaderHidden(true);
}

GDProjectTreeWidget::~GDProjectTreeWidget()
{}

void GDProjectTreeWidget::addProjectToTreeView(const QString &name, const QString &path)
{ // 将项目添加到目录树
    QDir dir(path);
    QString absPath = dir.absoluteFilePath(name); // 得到绝对路径
    projectTree = new GDProjectTree();
    if(projectTree->getPath_set().find(absPath) != projectTree->getPath_set().end()) { // 判重
        return;
    }
    projectTree->insertPath(absPath); // 添加路径
    QDir is_dir(absPath);
    bool enable = is_dir.mkpath(absPath);
    if(!enable) {
        return;
    }
    GDProjectTreeWidgetItem *item = new GDProjectTreeWidgetItem(this, name, path, TreeItemPro);
    item->setData(0, Qt::DecorationRole, QIcon(":/icon/icon/dir.png"));
    this->addTopLevelItem(item); // 添加项目
    delete projectTree;
}

void GDProjectTreeWidget::addOpenProjectToTreeView(const QString &srcPath)
{ // 将打开的项目添加到目录树 (打开的项目需要子线程递归遍历子目录)
    projectTree = new GDProjectTree();
    if(projectTree->getPath_set().find(srcPath) != projectTree->getPath_set().end()) { // 判重
        return;
    }
    projectTree->insertPath(srcPath); // 添加路径
    delete projectTree;
    QDir src_dir(srcPath);
    bool enable = src_dir.mkpath(srcPath);
    if(!enable) {
        return;
    }
    GDProjectTreeWidgetItem *item = new GDProjectTreeWidgetItem(this, src_dir.dirName(), srcPath, TreeItemPro);
    item->setData(0, Qt::DecorationRole, QIcon(":/icon/icon/dir.png"));
    this->addTopLevelItem(item);
    int fileCount = 0;
    // 创建线程
    openProjectThread = std::make_shared<GDOpenProjectThread>(std::ref(srcPath), fileCount, this, item, item, item, nullptr);
    openProjectThread->start(); // 启动线程
    progressDialog = new QProgressDialog(this);
    connect(openProjectThread.get(), SIGNAL(emitUpdateProgress(int)), this, SLOT(slotUpdateProgress(int)));
    connect(openProjectThread.get(), SIGNAL(emitFinishedProgress(int)), this, SLOT(slotFinishedProgress(int)));
    connect(progressDialog, SIGNAL(canceled()), this, SLOT(slotSendCancelSignal()));
    connect(this, SIGNAL(emitCancelProgress()), openProjectThread.get(), SLOT(slotCancelProgress()));
    progressDialog->setWindowTitle("please wait......");
    progressDialog->setRange(0, PORGRESS_MAX);
    progressDialog->setFixedWidth(PORGRESS_WINTH);
    progressDialog->exec();

}

void GDProjectTreeWidget::slotUpdateProgress(int count)
{ // 响应更新进度条
    if(progressDialog) {
        return;
    }
    if(count >= PORGRESS_MAX) {
        progressDialog->setValue(count % PORGRESS_MAX);
    }else if(count < PORGRESS_MAX) {
        progressDialog->setValue(PORGRESS_MAX);
    }
}

void GDProjectTreeWidget::slotFinishedProgress(int count)
{ // 响应完成进度条
    Q_UNUSED(count);
    progressDialog->setValue(PORGRESS_MAX);
    progressDialog->deleteLater(); // 等事件循环结束后，删除对话框，释放内存
}

void GDProjectTreeWidget::slotSendCancelSignal()
{ // 进度条对话框发送取消信号
    emit emitCancelProgress();
    delete progressDialog; // 立即删除
    progressDialog = nullptr;
}


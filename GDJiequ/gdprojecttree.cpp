#include "gdprojecttree.h"
#include "ui_gdprojecttree.h"
#include "gdslideshowdialog.h"
#include "const.h"
GDProjectTree::GDProjectTree(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GDProjectTree), item_buffer(nullptr), active_item(nullptr), selected_item(nullptr)
{
    ui->setupUi(this);
    this->setMinimumWidth(378);
    this->setMaximumWidth(378);

    actImport = new QAction(tr("导入文件"));
    actSetStart = new QAction(tr("设置活动项目"));
    actDelete = new QAction(tr("关闭项目"));
    actSlideShow = new QAction(tr("轮播展示"));
    connect(ui->treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(on_itemPressed(QTreeWidgetItem*,int)));
    connect(actImport, SIGNAL(triggered()), this, SLOT(actImportTriggered()));
    connect(actDelete, SIGNAL(triggered()), this, SLOT(actDeleteTriggered()));
    connect(actSetStart, SIGNAL(triggered()), this, SLOT(actSetStartTriggered()));
    connect(actSlideShow, SIGNAL(triggered()), this, SLOT(actSlideShowTriggered()));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(on_itemDoubleClicked(QTreeWidgetItem*, int)));

}

GDProjectTree::~GDProjectTree()
{
    delete ui;
}

QTreeWidgetItem *GDProjectTree::getSelected_item() const
{
    return selected_item;
}

QSet<QString> GDProjectTree::getPath_set() const
{
    return path_set;
}

void GDProjectTree::setPath_set(const QSet<QString> &newPath_set)
{
    path_set = newPath_set;
}

void GDProjectTree::insertPath(QString path)
{ // 向路径集中添加数据
    this->path_set.insert(path);
}

void GDProjectTree::addProjectSettingToTreeWdiget(const QString &name, const QString &path)
{ // 将项目配置添加到 gdprojecttreewidget
    ui->treeWidget->addProjectToTreeView(name, path);
}

void GDProjectTree::addOpenProjectSettingToTreeWidget(const QString srcPath)
{ // 将打开的项目路径传到 gdprojecttreewidget
    ui->treeWidget->addOpenProjectToTreeView(srcPath);
}

void GDProjectTree::on_itemPressed(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if(QGuiApplication::mouseButtons() == Qt::RightButton) {
        QMenu menu(this);
        if(item->type() == TreeItemPro) {
            item_buffer = item; // 缓存上次右击
            menu.addAction(actImport);
            menu.addAction(actSetStart);
            menu.addAction(actDelete);
            menu.addAction(actSlideShow);
            menu.exec(QCursor::pos()); //在当前位置显示
        }
    }
}

void GDProjectTree::on_itemDoubleClicked(QTreeWidgetItem *item, int column)
{ // 双击当前项，发送信号，通知显示
    auto show_item = dynamic_cast<GDProjectTreeWidgetItem*>(item);
    if(!show_item) {
        return;
    }
    if(show_item && show_item->type() == TreeItemPic) {
        selected_item = show_item; // 缓存当前双击项
        emit emitShowItem(show_item->getPath());
    }
}

void GDProjectTree::actImportTriggered()
{ // 弹出菜单 导入文件
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setWindowTitle("选择导入文件");
    QString curPath = QDir::currentPath();
    fileDialog.setDirectory(curPath);
    fileDialog.setViewMode(QFileDialog::Detail);
    QStringList filenames;
    if(fileDialog.exec()) {
        filenames = fileDialog.selectedFiles();
    }
    if(filenames.length() <= 0) {
        return;
    }
    QString srcPath = filenames.at(0);

    auto item = dynamic_cast<GDProjectTreeWidgetItem*>(item_buffer);
    auto path = item->getPath();
    QDir dir(path);
    auto dstPath = dir.absoluteFilePath(item->getName());
    // path_set.insert(dstPath);
    int fileCount = 0;
    progressDialog = new QProgressDialog(this);
    // 添加一个线程 线程传递是右值，引用类型是左值，要用std::ref()进行转换
    createProThread = std::make_shared<GDProjectTreeThread>(std::ref(srcPath), std::ref(dstPath), ui->treeWidget, item_buffer, item_buffer, nullptr, item_buffer, std::ref(fileCount), nullptr);
    createProThread->start(); // 启动线程

    // 接受线程传来的信号 createProThread.get() 得到裸指针，指向GDProjectTreeThread
    connect(createProThread.get(), SIGNAL(emitUpdateProgress(int)), this, SLOT(slotUpdateProgress(int)));
    connect(createProThread.get(), SIGNAL(emitProgressFinished(int)), this, SLOT(slotProgressFinished(int)));
    connect(progressDialog, SIGNAL(canceled()), this, SLOT(slotSendCancelSignal()));
    connect(this, SIGNAL(emitCancelSignal()), createProThread.get(), SLOT(slotStopThread()));

    progressDialog->setWindowTitle("Please wait......");
    progressDialog->setFixedWidth(PORGRESS_WINTH);
    progressDialog->setRange(0, PORGRESS_MAX);
    progressDialog->exec();
}

void GDProjectTree::actDeleteTriggered()
{ // 弹出菜单，关闭项目
    if(!item_buffer) {
        return;
    }
    auto protreeItem = dynamic_cast<GDProjectTreeWidgetItem*>(item_buffer);
    auto delete_path = protreeItem->getPath();
    auto pro_selected_item = dynamic_cast<GDProjectTreeWidgetItem*>(selected_item);
    if(item_buffer == active_item) { // 删除的项为活跃状态
        active_item = nullptr;
    }
    GDRemoveProjectDialog removeProjectDialog;
    if(removeProjectDialog.exec() != QDialog::Accepted) {
        return;
    }
    if(selected_item && pro_selected_item->getRoot() == protreeItem) {
        selected_item = nullptr;
        emit emitRemovePicture();
    }
    path_set.remove(delete_path); // 从路径集中删除该路径
    if(removeProjectDialog.is_remove()) { // 从本地目录中删除
        QDir delete_dir(delete_path);
        auto abs_delete_path = delete_dir.absoluteFilePath(protreeItem->getName());
        QDir abs_delete_dir(abs_delete_path);
        abs_delete_dir.removeRecursively(); // 本地文件递归删除
    }
    auto index = ui->treeWidget->indexOfTopLevelItem(protreeItem);
    delete ui->treeWidget->takeTopLevelItem(index); // 根据索引拿出当前项并删除
    item_buffer = nullptr;
}

void GDProjectTree::actSetStartTriggered()
{ // 设置活跃状态
    if(!item_buffer) {
        return;
    }

    QFont font;
    font.setBold(false);
    if(active_item) {
        active_item->setFont(0, font);
    }

    active_item = item_buffer;
    font.setBold(true);
    active_item->setFont(0, font);
}

void GDProjectTree::actSlideShowTriggered()
{ // 幻灯片展示
    if(!item_buffer) {
        return;
    }
    auto item = dynamic_cast<GDProjectTreeWidgetItem*>(item_buffer);
    auto firstItem = item->getFirstPicChild();
    if(!firstItem) return;
    auto lastItem = item->getLastPicChild();
    if(!lastItem) return;

    slideShowDialog = std::make_shared<GDSlideShowDialog>(this, firstItem, lastItem);
    slideShowDialog->setModal(true);
    slideShowDialog->showMaximized();
}

void GDProjectTree::slotUpdateProgress(int count)
{ // 接受线程更新信号
    if(!progressDialog) {
        return;
    }
    if(count >= PORGRESS_MAX) {
        progressDialog->setValue(count % PORGRESS_MAX);
    }else if(count < PORGRESS_MAX) {
        progressDialog->setValue(count);
    }
}

void GDProjectTree::slotProgressFinished(int count)
{ // 接受线程完成信号
    Q_UNUSED(count);
    progressDialog->setValue(PORGRESS_MAX);
    progressDialog->deleteLater(); // 等事件循环结束后，删除对话框，释放内存
}

void GDProjectTree::slotSendCancelSignal()
{ // 向线程发出取消信号
    emit emitCancelSignal();
    delete progressDialog;
    progressDialog = nullptr;
}

void GDProjectTree::slotSendUpdatePictureSignal(QString objectName)
{ // 发送更新图片信号
    if(!selected_item) {
        return;
    }

    auto pro_selected_item = dynamic_cast<GDProjectTreeWidgetItem*>(selected_item);
    auto pre_selectedItem = pro_selected_item->getPreviousItem();
    auto nxt_selectedItem = pro_selected_item->getNextItem();

    if(objectName == "pBtnPrevious") {
        if(!pre_selectedItem || pre_selectedItem->type() != TreeItemPic) return;
        selected_item = pre_selectedItem;
        emit emitUpdatePicture(pre_selectedItem->getPath());
        ui->treeWidget->setCurrentItem(pre_selectedItem);
    }else if(objectName == "pBtnNext") {
        if(!nxt_selectedItem || nxt_selectedItem->type() != TreeItemPic) return;
        selected_item = nxt_selectedItem;
        emit emitUpdatePicture(nxt_selectedItem->getPath());
        ui->treeWidget->setCurrentItem(nxt_selectedItem);
    }
}

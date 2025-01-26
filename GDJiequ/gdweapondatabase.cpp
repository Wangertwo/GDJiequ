#include "gdweapondatabase.h"
#include "ui_gdweapondatabase.h"

GDWeaponDatabase::GDWeaponDatabase(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GDWeaponDatabase)
{
    ui->setupUi(this);
    initForm();
    initMenu();
    initStyle();
    this->setWindowState(Qt::WindowMaximized); // 最大窗口显示
    this->setMinimumSize(1629, 869);
    projectTree = new GDProjectTree(this);
    pictureShow = new GDPictureShowDialog(this);
    ui->verticalLayout_2->addWidget(projectTree);
    ui->verticalLayout_3->addWidget(pictureShow);
    connect(ui->actNewPro, SIGNAL(triggered()), this, SLOT(actNewProTriggered()));
    connect(ui->actOpenPro, SIGNAL(triggered()), this, SLOT(actOpenProTriggered()));
    connect(ui->actSetMusic, SIGNAL(triggered()), this, SLOT(actSetMusicTriggered()));

    connect(this, SIGNAL(emitOpenProject(QString)), projectTree, SLOT(addOpenProjectSettingToTreeWidget(QString)));
    connect(projectTree, SIGNAL(emitShowItem(QString)), pictureShow, SLOT(slotShowItem(QString)));

    connect(pictureShow, SIGNAL(emitClickedPreBtn(QString)), projectTree, SLOT(slotSendUpdatePictureSignal(QString)), Qt::UniqueConnection);
    connect(pictureShow, SIGNAL(emitClickedNextBtn(QString)), projectTree, SLOT(slotSendUpdatePictureSignal(QString)), Qt::UniqueConnection);
    connect(projectTree, SIGNAL(emitUpdatePicture(QString)), pictureShow, SLOT(slotShowItem(QString)), Qt::UniqueConnection);
    connect(projectTree, SIGNAL(emitRemovePicture()), pictureShow, SLOT(slotRemovePicture()));
}

GDWeaponDatabase::~GDWeaponDatabase()
{
    delete ui;
}

void GDWeaponDatabase::initForm()
{ // 初始化窗体
    this->setAttribute(Qt::WA_DeleteOnClose);
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags | Qt::Window);
}

void GDWeaponDatabase::initMenu()
{ // 初始化菜单栏
    ui->menuFile->addAction(ui->actNewPro);
    ui->menuFile->addAction(ui->actOpenPro);
    ui->menuSet->addAction(ui->actSetMusic);
}

void GDWeaponDatabase::initStyle()
{ // 初始化样式
    QFile qss(":/styleSheet/styleSheet/style.qss");
    if(qss.open(QFile::ReadOnly)) {
        qDebug() << "open success";
        QString styleSheet = QLatin1String(qss.readAll());
        this->setStyleSheet(styleSheet);
        qss.close();
    }else {
        qDebug() << "open failed";
        return;
    }
}

void GDWeaponDatabase::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    //opt.init(this);
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void GDWeaponDatabase::actNewProTriggered()
{ // 点击创建项目
    projectWizard = new GDOpenProjectWizard(this);
    projectWizard->setWindowTitle(tr(" 新建项目"));
    auto page = projectWizard->page(0);
    page->setWindowTitle(tr("设置项目配置"));
    // 链接信号和槽
    connect(projectWizard, SIGNAL(emitProjectSetting(QString, QString)), dynamic_cast<GDProjectTree*>(projectTree), SLOT(addProjectSettingToTreeWdiget(QString, QString)));
    projectWizard->show();
    projectWizard->exec();
    // 关闭连接
    disconnect(projectWizard);
}

void GDWeaponDatabase::actOpenProTriggered()
{ // 点击打开项目
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setWindowTitle("选择要打开的项目");
    fileDialog.setDirectory(QDir::currentPath());
    fileDialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(fileDialog.exec()) {
        fileNames = fileDialog.selectedFiles();
    }
    if(fileNames.length() <= 0) {
        return;
    }
    QString srcPath = fileNames.at(0);
    // qDebug() << srcPath;
    emit emitOpenProject(srcPath);
}

void GDWeaponDatabase::actSetMusicTriggered()
{ // 设置背景音乐
    /* .wav文件
    QSoundEffect * startSound = new QSoundEffect(this);//创建对象
    startSound->setSource(QUrl::fromLocalFile(":/music/music/sample.mp3"));//添加资源
    startSound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环
    startSound->play();//软件启动自动播放
    */
}

void GDWeaponDatabase::resizeEvent(QResizeEvent *event)
{ // 重绘
    if(pictureShow->getSelected_path() != "") {
        pictureShow->reloadPicture();
    }
    QMainWindow::resizeEvent(event);
}





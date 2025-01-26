#include "gdprojectsetwizardpage.h"
#include "ui_gdprojectsetwizardpage.h"

GDProjectSetWizardPage::GDProjectSetWizardPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::GDProjectSetWizardPage)
{
    ui->setupUi(this);
    registerField("Name*", ui->lEditName);
    registerField("Path", ui->lEditPath);
    connect(ui->lEditName, SIGNAL(textEdited(QString)), this, SLOT(lEditNameTextEdited(QString)));
    connect(ui->lEditPath, SIGNAL(textEdited(QString)), this, SLOT(lEditPathTextEdited(QString)));
    auto curPath = QDir::currentPath();
    ui->lEditPath->setText(curPath);
    ui->lEditName->setCursorPosition(ui->lEditPath->text().size());
    ui->lEditPath->setClearButtonEnabled(true);
    ui->lEditName->setClearButtonEnabled(true);

    connect(ui->pBtnBrowse, SIGNAL(clicked()), this, SLOT(pBtnBrowseClicked()));
}

GDProjectSetWizardPage::~GDProjectSetWizardPage()
{
    delete ui;
}

void GDProjectSetWizardPage::getProjectSetting(QString &name, QString &path)
{
    name = ui->lEditName->text();
    path = ui->lEditPath->text();
}

void GDProjectSetWizardPage::lEditNameTextEdited(QString text)
{
    Q_UNUSED(text);
    emit completeChanged();
}

void GDProjectSetWizardPage::lEditPathTextEdited(QString text)
{
    Q_UNUSED(text);
    emit completeChanged();
}

void GDProjectSetWizardPage::pBtnBrowseClicked()
{ // 当browse按钮被点击
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setWindowTitle("选择导入的文件夹");
    auto curPath = QDir::currentPath();
    fileDialog.setDirectory(curPath);
    fileDialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(fileDialog.exec()) {
        fileNames = fileDialog.selectedFiles(); // 选定文件的绝对路径
    }
    if(fileNames.length() <= 0) {
        return;
    }
    QString path = fileNames.at(0);
    ui->lEditPath->setText(path);
}

bool GDProjectSetWizardPage::isComplete() const
{ // 判断文件夹是否合理以及是否已经有项目路径，决定按钮是否有效
    if(ui->lEditName->text() == "" || ui->lEditPath->text() == "") {
        return false;
    }

    // 判断文件夹是否合理
    QDir dir(ui->lEditPath->text());
    if(!dir.exists()) {
        ui->LabelTips->setText("project path is not exists");
        return false;
    }

    // 判断是否已经有项目路径
    auto absPath = dir.absoluteFilePath(ui->lEditName->text()); // 拼成完整路径
    QDir is_dir(absPath); // 目录
    if(is_dir.exists()) { // 判断当前目录是否存在
        ui->LabelTips->setText("project has exists, change path or name!");
        return false;
    }
    ui->LabelTips->setText("");
    return QWizardPage::isComplete(); // 子类调用基类的功能，保证下次依然可以使用当前虚函数
}

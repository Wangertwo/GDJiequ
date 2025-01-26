#include "gdregisterdialog.h"
#include "gdlogindialog.h"
#include "ui_gdregisterdialog.h"


GDRegisterDialog::GDRegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GDRegisterDialog)
{
    ui->setupUi(this);
    initForm();
    connect(ui->pBtnOk, SIGNAL(clicked()), this, SLOT(pBtnOkTriggered()));
}

GDRegisterDialog::~GDRegisterDialog()
{
    delete ui;
}

void GDRegisterDialog::pBtnOkTriggered()
{ // 向数据库中写入当前记录
    GDLoginDialog *loginDialog = new GDLoginDialog;
    auto uniqueElementMap = loginDialog->getUniqueElementMap();
    int empNo = uniqueElementMap.count();
    QSqlQuery query;
    query.prepare("INSERT INTO user (UserNo, UserName, Password, RegisterDate, Identification, Mobile, Birthplace) "
                  "VALUES (:userNo, :userName, :password, :registerDate, :identification, :mobile, :birthplace)");
    query.bindValue(":userNo", empNo);
    query.bindValue(":userName", ui->lEditUsername->text());
    query.bindValue(":password", ui->lEditPassword->text());
    query.bindValue(":registerDate", ui->dateEdit->date());
    query.bindValue(":identification", ui->lEditIdentification->text());
    query.bindValue(":mobile", ui->lEditMobile->text());
    query.bindValue(":birthplace", ui->lEditBirthplace->text());
    QString str = ui->lEditPassword->text();

    // 中文字符判断

    if(query.exec()) {
        QMessageBox::information(this, "信息", "注册成功!");
        this->accept();
    }else {
        QMessageBox::warning(this, "错误", "注册失败，错误信息\n"+query.lastError().text());
    }
}

void GDRegisterDialog::initForm()
{ // 初始化
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("注册");
    auto flags = this->windowFlags();
    this->setWindowFlags(flags | Qt::WindowStaysOnTopHint );
    this->setWindowOpacity(0.9);
    this->setFixedSize(482, 376);
}




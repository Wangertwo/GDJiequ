#include "gdlogindialog.h"
#include "ui_gdlogindialog.h"

GDLoginDialog::GDLoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GDLoginDialog)
{
    ui->setupUi(this);
    initForm();
    initMapNoList();
    connect(ui->pBtnLogin, SIGNAL(clicked()), this, SLOT(pBtnLoginTriggered()));
    connect(ui->pBtnRegister, SIGNAL(clicked()), this, SLOT(pBtnRegisterTriggered()));
}

GDLoginDialog::~GDLoginDialog()
{
    delete ui;
}

void GDLoginDialog::mousePressEvent(QMouseEvent *event)
{ // 鼠标按键被按下
    if(event->button() == Qt::LeftButton) { // 鼠标左键被按下
        m_moving = true;
        m_lastPos = event->globalPosition().toPoint() - pos(); // 记录下鼠标相对于窗口的位置
    }
    return QDialog::mousePressEvent(event);
}

void GDLoginDialog::mouseMoveEvent(QMouseEvent *event)
{ // 鼠标按下左键移动
    if(m_moving && (event->buttons() == Qt::LeftButton) &&
        (event->globalPosition().toPoint() - m_lastPos).manhattanLength() > QApplication::startDragDistance()) {
        move(event->globalPosition().toPoint() - m_lastPos);
        m_lastPos = event->globalPosition().toPoint()-pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void GDLoginDialog::mouseReleaseEvent(QMouseEvent *event)
{ // 鼠标释放事件
    m_moving = false; // 停止移动
}

void GDLoginDialog::initForm()
{ // 初始化窗口
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlag(Qt::FramelessWindowHint); // 无边框，但在任务栏显示
    // this->setWindowFlag(Qt::SplashScreen); // 设置为SplashScreen
    ui->lEditUsername->setFocus();
    ui->lEditPassword->setPlaceholderText("请输入密码");
    ui->lEditPassword->setStyleSheet("QLineEdit{color: grey;}");
    ui->lEditPassword->show();
}

void GDLoginDialog::initMapNoList()
{ // 取到所有的用户编号
    QSqlQuery query;
    query.exec("SELECT UserNo, Username FROM user order by UserNo");
    query.first();
    while(query.isValid()) {
        QSqlRecord record = query.record();
        auto userNo = record.value("UserNo").toInt();
        auto username = record.value("Username").toString();
        uniqueElementMap.insert(username, userNo);
        query.next();
    }
    setUniqueElementMap(uniqueElementMap);
}

bool GDLoginDialog::judgeUniqueness(QString username)
{ // 判断该用户名是否存在
    if(uniqueElementMap.isEmpty()) return false;
    if(uniqueElementMap.contains(username)) {
        return true;
    }else {
        return false;
    }
}

void GDLoginDialog::pBtnLoginTriggered()
{ // 当登录按钮被点击
    initMapNoList();
    QString username = ui->lEditUsername->text();
    QString password = ui->lEditPassword->text();
    if(username.isEmpty()) {
        QMessageBox::warning(this, "错误", "用户名不能为空");
        return;
    }else if(password.isEmpty()) {
        QMessageBox::warning(this, "错误", "密码不能为空");
        return;
    }else if(ui->rBtnUser->isChecked() || ui->rBtnPlanner->isChecked() || ui->rBtnProgamer->isChecked()) {
        if(judgeUniqueness(username)) {
            QSqlQuery query;
            query.prepare("SELECT * FROM user WHERE UserName = :username");
            query.bindValue(":username", username);
            if(query.exec()) { // 查询到当前用户记录
                query.first();
                QSqlRecord curRecord = query.record();
                auto Password = curRecord.value("Password").toString();
                if(Password == password) { // 验证密码成功
                    QMessageBox::information(this, "信息", "登录成功，欢迎来到光点劫区!");
                    // ...
                    this->accept();
                }else {
                    tryCount++;
                    if(tryCount > 3) {
                        QMessageBox::critical(this, "警告", "错误次数过多，强制退出");
                        this->reject();
                    }
                    QMessageBox::warning(this, "错误", "密码输入错误，请重新输入");
                }
            }else {
                QMessageBox::warning(this, "错误", "查询用户记录错误，错误信息\n"+query.lastError().text());
                return;
            }
        }else {
            QMessageBox::warning(this, "错误", "该用户不存在，请注册账户!");
            return;
        }
    }else {
        QMessageBox::warning(this, "错误", "请输入身份信息！");
        return;
    }
}

void GDLoginDialog::pBtnRegisterTriggered()
{ // 注册按钮被点击
    GDRegisterDialog *registerDialog = new GDRegisterDialog(this);
    if(registerDialog->exec() == QDialog::Accepted) {
        //...
    }
}

QMap<QString, int> GDLoginDialog::getUniqueElementMap() const
{
    return uniqueElementMap;
}
void GDLoginDialog::setUniqueElementMap(const QMap<QString, int> &newUniqueElementMap)
{
    this->uniqueElementMap = newUniqueElementMap;
}





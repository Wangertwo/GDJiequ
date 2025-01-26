#include "gdpictureshowdialog.h"
#include "ui_gdpictureshowdialog.h"

GDPictureShowDialog::GDPictureShowDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GDPictureShowDialog), selected_path("")
{
    ui->setupUi(this);

    ui->pBtnPrevious->setIcons(":/icon/icon/previous.png",
                               ":/icon/icon/previous_hover.png",
                               ":/icon/icon/previous_press.png");
    ui->pBtnNext->setIcons(":/icon/icon/next.png",
                           ":/icon/icon/next_hover.png",
                           ":/icon/icon/next_press.png");

    // 设置渐隐渐显的效果
    QGraphicsOpacityEffect *preBtn_opacity = new QGraphicsOpacityEffect(this);\
    preBtn_opacity->setOpacity(0); // 初始不显示
    ui->pBtnPrevious->setGraphicsEffect(preBtn_opacity); // 设置图形效果
    QGraphicsOpacityEffect *nextBtn_opacity = new QGraphicsOpacityEffect(this);
    nextBtn_opacity->setOpacity(0);
    ui->pBtnNext->setGraphicsEffect(nextBtn_opacity);

    preBtn_Animation = new QPropertyAnimation(preBtn_opacity, "opacity", this);
    preBtn_Animation->setEasingCurve(QEasingCurve::Linear);
    preBtn_Animation->setDuration(500);
    nextBtn_Animation = new QPropertyAnimation(nextBtn_opacity, "opacity", this);
    nextBtn_Animation->setEasingCurve(QEasingCurve::Linear);
    nextBtn_Animation->setDuration(500);

    connect(ui->pBtnPrevious, SIGNAL(clicked()), this, SLOT(slotSendClickedSignal()), Qt::UniqueConnection);
    connect(ui->pBtnNext, SIGNAL(clicked()), this, SLOT(slotSendClickedSignal()), Qt::UniqueConnection);
}

GDPictureShowDialog::~GDPictureShowDialog()
{
    delete ui;
}

bool GDPictureShowDialog::event(QEvent *event)
{ // 重写按钮显示事件函数
    switch(event->type()) {
        case QEvent::Enter:
            setPreNextButtonAnimation(true);
            break;
        case QEvent::Leave:
            setPreNextButtonAnimation(false);
            break;
        default:
            break;
    }
        return QDialog::event(event);
}

void GDPictureShowDialog::setPreNextButtonAnimation(bool is_show)
{ // 控制按钮的动画显示
    if(!is_show && pBtnVisible) {
        preBtn_Animation->setStartValue(1); // 透明度由1->0
        preBtn_Animation->setEndValue(0);
        preBtn_Animation->start();
        nextBtn_Animation->setStartValue(1);
        nextBtn_Animation->setEndValue(0);
        nextBtn_Animation->start();

        pBtnVisible = false;
        return;
    }

    if(is_show && !pBtnVisible) {
        preBtn_Animation->setStartValue(0); // 透明度由0->1
        preBtn_Animation->setEndValue(1);
        preBtn_Animation->start();
        nextBtn_Animation->setStartValue(0);
        nextBtn_Animation->setEndValue(1);
        nextBtn_Animation->start();

        pBtnVisible = true;
        return;
    }
}

QString GDPictureShowDialog::getSelected_path() const
{
    return selected_path;
}

void GDPictureShowDialog::reloadPicture()
{ // 重绘
    if(selected_path != "") {
        show_picture.load(selected_path);
        auto picture_width = ui->gridLayout->geometry().width()-20;
        auto picture_height = ui->gridLayout->geometry().height()-20;
        show_picture.scaled(picture_width, picture_height, Qt::KeepAspectRatio);
        ui->picShow->setPixmap(show_picture);
    }
}

void GDPictureShowDialog::slotShowItem(QString showItemPath)
{ // 显示当前图片项
    show_picture.load(showItemPath);
    auto picture_width = ui->gridLayout->geometry().width()-20;
    auto picture_height = ui->gridLayout->geometry().height()-20;
    show_picture.scaled(picture_width, picture_height, Qt::KeepAspectRatio);
    ui->picShow->setPixmap(show_picture);
    selected_path = showItemPath; // 缓存选中的图片路径
}

void GDPictureShowDialog::slotSendClickedSignal()
{ // 发送点击前后按钮信号
    if(selected_path == "") {
        return;
    }
    auto button = sender();
    if(button->objectName() == "pBtnPrevious") {
        emit emitClickedPreBtn(button->objectName());
    }else if (button->objectName() == "pBtnNext") {
        emit emitClickedNextBtn(button->objectName());
    }
}

void GDPictureShowDialog::slotRemovePicture()
{ // 清除残留图片
    selected_path = "";
    ui->picShow->clear();
}

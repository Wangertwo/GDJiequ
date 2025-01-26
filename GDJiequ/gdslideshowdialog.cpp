#include "gdslideshowdialog.h"
#include "ui_gdslideshowdialog.h"
#include "const.h"
GDSlideShowDialog::GDSlideShowDialog(QWidget *parent, QTreeWidgetItem *firstItem, QTreeWidgetItem *lastItem)
    : QDialog(parent)
    , ui(new Ui::GDSlideShowDialog), m_firstItem(firstItem), m_lastItem(lastItem)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    ui->pBtnPrevious->setIcons(":/icon/icon/previous.png",
                               ":/icon/icon/previous_hover.png",
                               ":/icon/icon/previous_press.png");
    ui->pBtnNext->setIcons(":/icon/icon/next.png",
                           ":/icon/icon/next_hover.png",
                           ":/icon/icon/next_press.png");
    ui->pBtnClose->setIcons(":/icon/icon/closeshow.png",
                            ":/icon/icon/closeshow_hover.png",
                            ":/icon/icon/closeshow_press.png");
    ui->pBtnShow->setIcons(":/icon/icon/play.png",
                           ":/icon/icon/play_hover.png",
                           ":/icon/icon/play_press.png",
                           ":/icon/icon/pause.png",
                           ":/icon/icon/pause_hover.png",
                           ":/icon/icon/pause_press.png");

    connect(ui->sildeShowWidget, SIGNAL(emitUpdatePreList(QTreeWidgetItem*)), ui->preListWidget, SLOT(slotUpdatePreList(QTreeWidgetItem*)));
    connect(ui->sildeShowWidget, SIGNAL(emitUpdateSelect(QTreeWidgetItem*)), ui->preListWidget, SLOT(slotUpdateSelect(QTreeWidgetItem*)));
    connect(ui->preListWidget, SIGNAL(emitUpdateShift(QString)), ui->sildeShowWidget, SLOT(slotUpdateShift(QString)));
    connect(ui->sildeShowWidget, SIGNAL(emitSetShowBtnClose()), this, SLOT(slotSetShowBtnClose()));
    ui->sildeShowWidget->setPixmap(m_firstItem); // 发送信号之前需要连接
    ui->sildeShowWidget->start();

    connect(ui->pBtnClose, SIGNAL(clicked()), this, SLOT(pBtnCloseClicked()));
    connect(ui->pBtnPrevious, SIGNAL(clicked()), this, SLOT(pBtnPreviousClicked()));
    connect(ui->pBtnNext, SIGNAL(clicked()), this, SLOT(pBtnNextClicked()));
    connect(ui->pBtnShow, SIGNAL(clicked()), this, SLOT(pBtnShowClicked()));
}

GDSlideShowDialog::~GDSlideShowDialog()
{
    delete ui;
}

void GDSlideShowDialog::pBtnCloseClicked()
{
    this->reject();
}

void GDSlideShowDialog::pBtnPreviousClicked()
{
    ui->sildeShowWidget->pBtnPreviousClicked();
}

void GDSlideShowDialog::pBtnNextClicked()
{
    ui->sildeShowWidget->pBtnNextClicked();

}

void GDSlideShowDialog::pBtnShowClicked()
{
    int type = ui->pBtnShow->currentStateType();
    if(type == BtnPause) {
        ui->sildeShowWidget->pBtnShowOpen();
    }else if(type == BtnPlay) {
        ui->sildeShowWidget->pBtnShowClose();
    }
}

void GDSlideShowDialog::slotSetShowBtnClose()
{ // 设置播放按钮为关闭状态
    ui->pBtnShow->setPlayNormal();
}

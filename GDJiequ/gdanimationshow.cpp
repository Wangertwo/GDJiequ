#include "gdanimationshow.h"
#include "gdprojecttreewidgetitem.h"
#include "const.h"
/*基于目录树，双缓冲绘图，时间脉冲*/
GDAnimationShow::GDAnimationShow(QWidget *parent)
    : QWidget{parent}, m_currentItem(nullptr), m_factor(0.0), m_showState(false)
{
    m_timer = new QTimer(this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));

}

GDAnimationShow::~GDAnimationShow()
{
}

void GDAnimationShow::stop()
{ // 播放结束
    m_timer->stop();
    m_factor = 0.0;
    m_showState = false;
    emit emitSetShowBtnClose();
}

void GDAnimationShow::start()
{ // 播放开始
    m_factor = 0.0;
    m_timer->start(50);
    m_showState = true;
}

void GDAnimationShow::setPixmap(QTreeWidgetItem *item)
{ // 双缓冲绘图，做准备
    if(!item) {
        return;
    }
    auto pro_item = dynamic_cast<GDProjectTreeWidgetItem*>(item);
    auto pro_item_path = pro_item->getPath();
    m_pixmap1.load(pro_item_path);
    m_currentItem = pro_item;
    if(m_itemMap.find(pro_item_path) == m_itemMap.end()) {
        m_itemMap[pro_item_path] = pro_item;
        // 发送更新预览列表信号
        emit emitUpdatePreList(pro_item);
    }
    emit emitUpdateSelect(pro_item); // 信号不能同时发射
    auto pro_next_item = pro_item->getNextItem();
    if(!pro_next_item) {
        return;
    }
    auto pro_nextItem_path = pro_next_item->getPath();
    m_pixmap2.load(pro_nextItem_path);
    if(m_itemMap.find(pro_nextItem_path) == m_itemMap.end()) {
        m_itemMap[pro_nextItem_path] = pro_next_item;
        // 发送更新预览列表信号
        emit emitUpdatePreList(pro_next_item);
    }
}

void GDAnimationShow::pBtnPreviousClicked()
{ // 轮播图前一按钮
    if(!m_currentItem) {
        return;
    }
    m_showState = false;
    auto curItem = dynamic_cast<GDProjectTreeWidgetItem*>(m_currentItem);
    auto preItem = curItem->getPreviousItem();
    if(!preItem || preItem->type() != TreeItemPic) {
        stop();
        update();
        return;
    }
    this->setPixmap(preItem);

    stop();
    update();
}

void GDAnimationShow::pBtnNextClicked()
{ // 轮播图后一个按钮
    if(!m_currentItem) {
        return;
    }
    m_showState = false;
    auto curItem = dynamic_cast<GDProjectTreeWidgetItem*>(m_currentItem);
    auto nextItem = curItem->getNextItem();
    if(!nextItem) {
        stop();
        update();
        return;
    }
    this->setPixmap(nextItem);
    stop();
    update();
}

void GDAnimationShow::pBtnShowOpen()
{ // 设置播放状态
    this->start();
    update();
}

void GDAnimationShow::pBtnShowClose()
{ // 设置关闭状态
    this->stop();
    update();
}

void GDAnimationShow::paintEvent(QPaintEvent *event)
{ // 双缓冲绘图，实现
    if(m_pixmap1.isNull()) {
        return;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 设置抗锯齿
    auto rect = geometry();
    int w = rect.width();
    int h = rect.height();
    m_pixmap1 = m_pixmap1.scaled(w, h, Qt::KeepAspectRatio); // 等比例拉伸
    int alpha = 255*(1.0f - m_factor); // 透明因子逐渐减小
    QPixmap alphaPixmap(m_pixmap1.size());
    alphaPixmap.fill(Qt::transparent);
    QPainter p1(&alphaPixmap); // 在透明区上不断绘图
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, m_pixmap1);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p1.fillRect(alphaPixmap.rect(), QColor(0,0,0,alpha));
    p1.end();
    int x = (w - m_pixmap1.width()) / 2;
    int y = (h - m_pixmap1.height()) / 2;
    painter.drawPixmap(x, y, alphaPixmap); // 在居中位置进行绘图

    if(m_pixmap2.isNull()) {
        return;
    }
    m_pixmap2 = m_pixmap2.scaled(w, h, Qt::KeepAspectRatio);
    int alpha2 = 255*m_factor; // 透明因子逐渐增大
    QPixmap alphaPixmap2(m_pixmap2.size());
    alphaPixmap2.fill(Qt::transparent);
    QPainter p2(&alphaPixmap2);
    p2.setCompositionMode(QPainter::CompositionMode_Source);
    p2.drawPixmap(0, 0, m_pixmap2);
    p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p2.fillRect(alphaPixmap2.rect(), QColor(0,0,0,alpha2));
    p2.end();
    int x2 = (w - m_pixmap2.width()) / 2;
    int y2 = (h - m_pixmap2.height()) / 2;
    painter.drawPixmap(x2, y2, alphaPixmap2);

    return QWidget::paintEvent(event);
}

void GDAnimationShow::slotTimeout()
{ // 计时器每次超时都会调用此函数
    if(!m_currentItem) {
        stop(); // 关闭计时器
        update(); // 更新当前widget页面
        return;
    }
    m_factor = m_factor + 0.01;

    if(m_factor >= 1.0){ // 更换图片
        m_factor = 0.0;
        auto cur_pro_item = dynamic_cast<GDProjectTreeWidgetItem*>(m_currentItem);
        auto cur_pro_nextItem = cur_pro_item->getNextItem();
        if(!cur_pro_nextItem) {
            stop();
            update();
            return;
        }
        setPixmap(cur_pro_nextItem);
        update();
        return;
    }
    update();
}

void GDAnimationShow::slotUpdateShift(QString path)
{ // 切换图标项，刷新图片
    stop();
    m_showState = false;
    if(m_itemMap.find(path) == m_itemMap.end()) {
        return;
    }
    auto item = m_itemMap[path];
    setPixmap(item);
    update();  // 触发重绘事件

}

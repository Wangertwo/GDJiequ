#include "gdprelistwidget.h"
#include "const.h"
#include "gdprojecttreewidgetitem.h"
#include "gdprelistwidgetitem.h"
GDPreListWidget::GDPreListWidget(QWidget *parent)
    :QListWidget(parent), m_index(0), m_currentItem(nullptr), m_lastIndex(16)
{
    this->setViewMode(IconMode);
    this->setIconSize(QSize(ICONSIZE, ICONSIZE));
    this->setSpacing(5); // 设置间隔
    this->setFlow(LeftToRight); // 设置流动方向

    connect(this, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_itemClicked(QListWidgetItem*)));

}

GDPreListWidget::~GDPreListWidget()
{

}

void GDPreListWidget::slotUpdatePreList(QTreeWidgetItem *item)
{ // 更新预览列表
    // assert(item != nullptr); // 断言
    if(!item) {
        return;
    }

    auto pro_item = dynamic_cast<GDProjectTreeWidgetItem*>(item);
    auto path = pro_item->getPath();

    if(m_set_items.find(path) != m_set_items.end()) {
        return;
    }

    QPixmap pixmap_source(path); // 等比拉伸
    pixmap_source = pixmap_source.scaled(ICONSIZE, ICONSIZE, Qt::KeepAspectRatio);
    auto width_source = pixmap_source.width();
    auto height_source = pixmap_source.height();
    QPixmap pixmap_destination(QSize(ICONSIZE, ICONSIZE));
    pixmap_destination.fill(QColor(220, 220, 220, 50));
    auto width_destination = pixmap_destination.width();
    auto height_destination = pixmap_destination.height();
    auto x = (width_destination - width_source) / 2;
    auto y = (height_destination - height_source) / 2;
    QPainter painter(&pixmap_destination);
    painter.drawPixmap(x, y, pixmap_source);

    m_index++;
    if(m_index == 1) {
        m_origin = this->pos();
    }
    auto icon_item = new GDPreListWidgetItem(QIcon(pixmap_destination), path, m_index, this);
    this->addItem(icon_item);
    icon_item->setSizeHint(QSize(ICONITEM, ICONITEM));
    m_set_items[path] = icon_item;
}

void GDPreListWidget::slotUpdateSelect(QTreeWidgetItem *item)
{ // // 选中逻辑（设置索引、设置翻页）
    if(!item) {
        return;
    }
    auto pro_item = dynamic_cast<GDProjectTreeWidgetItem*>(item);
    auto pro_item_path = pro_item->getPath();
    if(!m_set_items[pro_item_path] || m_set_items.find(pro_item_path) == m_set_items.end()) {
        return;
    }
    auto icon_item = m_set_items[pro_item_path];
    this->setCurrentItem(icon_item);
    m_currentItem = icon_item;
    auto list_icon_item = dynamic_cast<GDPreListWidgetItem*>(icon_item);
    int index = list_icon_item->getIndex();
    if(index > 16) {
        auto curPos = this->pos(); // (0,0)
        this->move(curPos.x() - (index - m_lastIndex)*100, curPos.y());
        m_lastIndex = index;
    }else {
        this->move(m_origin); // 移动到最初的位置
        m_lastIndex = 16;
    }
}

void GDPreListWidget::on_itemClicked(QListWidgetItem *item)
{ // 点击预览框中的某一项
    if(!item) {
        return;
    }
    auto cur_item = dynamic_cast<GDPreListWidgetItem*>(item);
    auto cur_item_path = cur_item->getPath();
    emit emitUpdateShift(cur_item_path);
    this->setCurrentItem(cur_item);
}

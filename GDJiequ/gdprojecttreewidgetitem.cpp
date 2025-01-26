#include "gdprojecttreewidgetitem.h"
#include "const.h"
GDProjectTreeWidgetItem::GDProjectTreeWidgetItem(QTreeWidget *treeview, QString name, QString path, int type)
    : QTreeWidgetItem(treeview, type),m_name(name),m_path(path),m_root(this),m_previousItem(nullptr),m_nextItem(nullptr)
{

    this->setData(0, Qt::DisplayRole, name);
    this->setData(0, Qt::ToolTipRole, path);
}

GDProjectTreeWidgetItem::GDProjectTreeWidgetItem(QTreeWidgetItem *parent, QString name, QString path, QTreeWidgetItem *root, int type)
    : QTreeWidgetItem(parent, type),m_name(name),m_path(path),m_root(root), m_previousItem(nullptr),m_nextItem(nullptr)
{

    this->setData(0, Qt::DisplayRole, name);
    this->setData(0, Qt::ToolTipRole, path);
}

GDProjectTreeWidgetItem::~GDProjectTreeWidgetItem()
{

}

QString GDProjectTreeWidgetItem::getName() const
{
    return m_name;
}

void GDProjectTreeWidgetItem::setName(const QString &newName)
{
    m_name = newName;
}

QString GDProjectTreeWidgetItem::getPath() const
{
    return m_path;
}

void GDProjectTreeWidgetItem::setPath(const QString &newPath)
{
    m_path = newPath;
}

GDProjectTreeWidgetItem *GDProjectTreeWidgetItem::getPreviousItem()
{
    return dynamic_cast<GDProjectTreeWidgetItem*>(m_previousItem);
}

GDProjectTreeWidgetItem *GDProjectTreeWidgetItem::getNextItem()
{
    return dynamic_cast<GDProjectTreeWidgetItem*>(m_nextItem);
}

void GDProjectTreeWidgetItem::setPreviousItem(QTreeWidgetItem *item)
{
    m_previousItem = item;
}

void GDProjectTreeWidgetItem::setNextItem(QTreeWidgetItem *item)
{
    m_nextItem = item;
}

GDProjectTreeWidgetItem *GDProjectTreeWidgetItem::getLastPicChild()
{ // 得到项目的最后一个图片节点
    if(this->type() == TreeItemPic) { // 不是项目节点
        return nullptr;
    }

    int count = this->childCount();
    if(count <= 0) { // 空项目
        return nullptr;
    }

    for(int i = count-1; i >= 0; i--) {
        auto lastItem = this->child(i);
        auto proLastItem = dynamic_cast<GDProjectTreeWidgetItem*>(lastItem);
        if(proLastItem->type() == TreeItemPic)  {
            return proLastItem;
        }
        auto lastProItem = proLastItem->getLastPicChild();
        if(!lastProItem) { // 递归返回值为空
            continue;
        }
        return lastProItem;
    }
    return nullptr;
}

GDProjectTreeWidgetItem *GDProjectTreeWidgetItem::getFirstPicChild()
{ // 得到项目的第一个图片节点
    if(this->type() == TreeItemPic) {
        return nullptr;
    }

    int count = this->childCount();
    if(count <= 0) {
        return nullptr;
    }

    for(int i = 0; i < count; i++) {
        auto firstItem = this->child(i);
        auto proFirstItem = dynamic_cast<GDProjectTreeWidgetItem*>(firstItem);
        if(proFirstItem->type() == TreeItemPic) {
            return proFirstItem;
        }
        auto firstProItem = proFirstItem->getFirstPicChild();
        if(!firstProItem) {
            return nullptr;
        }
        return firstProItem;
    }
    return nullptr;
}

void GDProjectTreeWidgetItem::setRoot(QTreeWidgetItem *item)
{
    this->m_root = item;
}

GDProjectTreeWidgetItem *GDProjectTreeWidgetItem::getRoot()
{
    return dynamic_cast<GDProjectTreeWidgetItem*>(m_root);
}

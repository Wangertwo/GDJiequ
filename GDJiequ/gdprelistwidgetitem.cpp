#include "gdprelistwidgetitem.h"

GDPreListWidgetItem::GDPreListWidgetItem(const QIcon &icon, const QString &text, int index, QListWidget *listview, int type)
    : QListWidgetItem(icon, "", listview, type), m_icon(icon), m_path(text), m_index(index)
{
    this->setIcon(m_icon);
    this->setToolTip(m_path);

}

GDPreListWidgetItem::~GDPreListWidgetItem()
{

}

int GDPreListWidgetItem::getIndex() const
{
    return m_index;
}

QString GDPreListWidgetItem::getPath() const
{
    return m_path;
}

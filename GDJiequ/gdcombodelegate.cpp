#include "gdcombodelegate.h"

GDComboDelegate::GDComboDelegate() {}

GDComboDelegate::~GDComboDelegate()
{}

void GDComboDelegate::setItem(bool isEditable, QStringList itemList)
{
    this->m_itemList = itemList;
    this->m_Editable = isEditable;
}

QWidget *GDComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    for(int i = 0; i < m_itemList.size(); i++) {
        editor->addItem(m_itemList.at(i));
    }
    editor->setEnabled(m_Editable);
    return editor;
}

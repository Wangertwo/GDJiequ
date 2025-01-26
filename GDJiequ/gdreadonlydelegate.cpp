#include "gdreadonlydelegate.h"

GDReadOnlyDelegate::GDReadOnlyDelegate() {}

GDReadOnlyDelegate::~GDReadOnlyDelegate()
{}

QWidget *GDReadOnlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{ // 只读
    return nullptr;
}
void setEditorData(QWidget *editor, const QModelIndex &index) {
    // 不执行任何操作，保持数据只读
}

void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) {
    // 不执行任何操作，保持数据只读
}

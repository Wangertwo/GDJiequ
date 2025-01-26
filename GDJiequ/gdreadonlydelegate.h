#ifndef GDREADONLYDELEGATE_H
#define GDREADONLYDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QStyledItemDelegate>

class GDReadOnlyDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    GDReadOnlyDelegate();
    ~GDReadOnlyDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index);
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index);

};

#endif // GDREADONLYDELEGATE_H

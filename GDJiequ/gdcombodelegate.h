#ifndef GDCOMBODELEGATE_H
#define GDCOMBODELEGATE_H

#include <QObject>
#include <QWidget>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QComboBox>
class GDComboDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    GDComboDelegate();
    ~GDComboDelegate();
    void setItem(bool isEditable, QStringList itemList);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    bool m_Editable;
    QStringList m_itemList;

};

#endif // GDCOMBODELEGATE_H

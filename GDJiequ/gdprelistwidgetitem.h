#ifndef GDPRELISTWIDGETITEM_H
#define GDPRELISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QWidget>

class GDPreListWidgetItem : public QListWidgetItem
{
public:
    GDPreListWidgetItem(const QIcon &icon, const QString &text, int index,
                        QListWidget *listview = nullptr, int type = Type);

    ~GDPreListWidgetItem();

    int getIndex() const;

    QString getPath() const;

private:
    QIcon m_icon;
    QString m_path;
    int m_index;

};

#endif // GDPRELISTWIDGETITEM_H

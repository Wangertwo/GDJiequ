#ifndef GDLOGINDIALOG_H
#define GDLOGINDIALOG_H
/* 循环编译问题
 * 原因: 两个.h文件都包含彼此的头文件
 * 方式: 在b的一个.cpp文件中添加a的.h文件，将b的.h文件中a的.h文件去除
*/
#include "gdregisterdialog.h"
#include <QDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
namespace Ui {
class GDLoginDialog;
}

class GDLoginDialog : public QDialog
{
    Q_OBJECT

protected:
    // 用于鼠标拖动窗口的鼠标事件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    explicit GDLoginDialog(QWidget *parent = nullptr);
    ~GDLoginDialog();
    void initForm();
    void initMapNoList();
    bool judgeUniqueness(QString username);

    QMap<QString, int> getUniqueElementMap() const;
    void setUniqueElementMap(const QMap<QString, int> &newUniqueElementMap);

private slots:
    void pBtnLoginTriggered();
    void pBtnRegisterTriggered();

private:
    Ui::GDLoginDialog *ui;
    bool m_moving = false; // 窗口是否在鼠标操作下移动
    QPoint m_lastPos; // 上一次的鼠标位置
    int tryCount = 0; // 记录错误登录次数
    QMap<QString, int> uniqueElementMap;
};

#endif // GDLOGINDIALOG_H

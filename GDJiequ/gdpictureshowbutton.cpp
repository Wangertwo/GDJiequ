#include "gdpictureshowbutton.h"

GDPictureShowButton::GDPictureShowButton(QWidget *parent) {

}

GDPictureShowButton::~GDPictureShowButton()
{

}

void GDPictureShowButton::setIcons(const QString &normal, const QString &hover, const QString &press)
{ // 设置按钮当前状态下的图标（正常状态下）
    m_normal = normal;
    m_hover = hover;
    m_press = press;

    QPixmap icon;
    icon.load(normal);
    this->resize(icon.size()); // 设置按钮的大小
    this->setIcon(icon);
    this->setIconSize(icon.size()); // 设置图标的大小，防止失帧
}

void GDPictureShowButton::setNormol()
{
    QPixmap icon;
    icon.load(m_normal);
    this->setIcon(icon);
}

void GDPictureShowButton::setHover()
{
    QPixmap icon;
    icon.load(m_hover);
    this->setIcon(icon);
}

void GDPictureShowButton::setPress()
{
    QPixmap icon;
    icon.load(m_press);
    this->setIcon(icon);
}

bool GDPictureShowButton::event(QEvent *e)
{ // 设置按钮事件
    switch(e->type()) {
    case QEvent::Enter:
        this->setHover();
        break;
    case QEvent::MouseButtonPress:
        this->setPress();
        break;
    case QEvent::MouseButtonRelease:
        this->setHover();
        break;
    case QEvent::Leave:
        this->setNormol();
        break;
    default:
        break;
    }
    return QPushButton::event(e); // 子类调用基类的虚函数，要把基类的虚函数给返回
}

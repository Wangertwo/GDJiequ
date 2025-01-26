#include "gdpicturestatebutton.h"
#include "const.h"
GDPictureStateButton::GDPictureStateButton(QWidget *parent)
    : QPushButton(parent)
{

}

GDPictureStateButton::~GDPictureStateButton()
{

}

void GDPictureStateButton::setIcons(const QString &play_normal, const QString &play_hover, const QString &play_press, const QString &pause_normal, const QString &pause_hover, const QString &pause_press)
{ // 设置按钮图标
    m_play_normal = play_normal;
    m_play_hover = play_hover;
    m_play_press = play_press;
    m_pause_normal = pause_normal;
    m_pause_hover = pause_hover;
    m_pause_press = pause_press;

    QPixmap icon;
    icon.load(m_pause_normal);
    this->resize(icon.size());
    this->setIcon(icon);
    this->setIconSize(icon.size());
    m_currentStateType = BtnPause;
}

int GDPictureStateButton::currentStateType() const
{
    return m_currentStateType;
}

void GDPictureStateButton::setPlayNormal()
{
    QPixmap icon;
    icon.load(m_play_normal);
    this->setIcon(icon);
    m_currentStateType = BtnPlay;
}

void GDPictureStateButton::setPlayHover()
{
    QPixmap icon;
    icon.load(m_play_hover);
    this->setIcon(icon);
    m_currentStateType = BtnPlay;

}

void GDPictureStateButton::setPlayPress()
{
    QPixmap icon;
    icon.load(m_play_press);
    this->setIcon(icon);
    m_currentStateType = BtnPause;

}

void GDPictureStateButton::setPauseNormal()
{
    QPixmap icon;
    icon.load(m_pause_normal);
    this->setIcon(icon);
    m_currentStateType = BtnPause;

}

void GDPictureStateButton::setPauseHover()
{
    QPixmap icon;
    icon.load(m_pause_hover);
    this->setIcon(icon);
    m_currentStateType = BtnPause;

}

void GDPictureStateButton::setPausePress()
{
    QPixmap icon;
    icon.load(m_pause_press);
    this->setIcon(icon);
    m_currentStateType = BtnPlay;

}

bool GDPictureStateButton::event(QEvent *e)
{ // 重写按钮状态事件
    switch(e->type()) {
        case QEvent::Enter:
            if(m_currentStateType == BtnPlay) {
                this->setPlayHover();
            }else if(m_currentStateType == BtnPause) {
                this->setPauseHover();
            }
            break;
        case QEvent::MouseButtonRelease:
            if(m_currentStateType == BtnPlay) {
                this->setPlayNormal();
            }else if(m_currentStateType == BtnPause) {
                this->setPauseNormal();
            }
            break;
        case QEvent::MouseButtonPress:
            if(m_currentStateType == BtnPlay) {
                this->setPlayPress();
            }else if(m_currentStateType == BtnPause) {
                this->setPausePress();
            }
            break;
        case QEvent::Leave:
            if(m_currentStateType == BtnPlay) {
                this->setPlayNormal();
            }else if(m_currentStateType == BtnPause) {
                this->setPauseNormal();
            }
        default:
            break;
    }
    return QPushButton::event(e);
}





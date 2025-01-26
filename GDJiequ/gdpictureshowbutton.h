#ifndef GDPICTURESHOWBUTTON_H
#define GDPICTURESHOWBUTTON_H
/* 按钮的正常显示，悬浮显示，点击显示*/
#include <QPushButton>
#include <QEvent>
class GDPictureShowButton : public QPushButton
{
public:
    GDPictureShowButton(QWidget *parent = nullptr);
    ~GDPictureShowButton();
    void setIcons(const QString &normal, const QString &hover, const QString &Press);

private:
    void setNormol();
    void setHover();
    void setPress();
    QString m_normal;
    QString m_hover;
    QString m_press;

protected:
    bool event(QEvent *e) override;

};

#endif // GDPICTURESHOWBUTTON_H

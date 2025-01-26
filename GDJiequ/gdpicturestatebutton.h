#ifndef GDPICTURESTATEBUTTON_H
#define GDPICTURESTATEBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QEvent>
class GDPictureStateButton : public QPushButton
{
    Q_OBJECT
public:
    GDPictureStateButton(QWidget *parent = nullptr);
    ~GDPictureStateButton();
    void setIcons(const QString &play_normal, const QString &play_hover, const QString &play_press,
                  const QString &pause_normal, const QString &pause_hover, const QString &pause_press);

    int currentStateType() const;
    void setPlayNormal();
    void setPlayHover();
    void setPlayPress();
    void setPauseNormal();
    void setPauseHover();
    void setPausePress();
private:
    int m_currentStateType;
    QString m_play_normal;
    QString m_play_hover;
    QString m_play_press;
    QString m_pause_normal;
    QString m_pause_hover;
    QString m_pause_press;


protected:
    bool event(QEvent *e) override;
};

#endif // GDPICTURESTATEBUTTON_H

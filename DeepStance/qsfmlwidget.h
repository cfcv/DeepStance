#ifndef QSFMLWIDGET_H
#define QSFMLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <SFML/Graphics.hpp>

class QSFMLWidget : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
    private :
        QTimer timer_;
        bool initialized_;

    protected slots:
        virtual void zoomFactorChanged(QString arg);

    public:
        explicit QSFMLWidget(QWidget *parent = nullptr);
        virtual QPaintEngine *paintEngine() const;

        virtual void showEvent(QShowEvent *event);
        virtual void paintEvent(QPaintEvent *event);
        virtual void onInit();
        virtual void onUpdate();

};

#endif // QSFMLWIDGET_H

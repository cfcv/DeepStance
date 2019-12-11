#include "qsfmlwidget.h"

void QSFMLWidget::zoomFactorChanged(QString arg)
{
    //To be overwritten
}

QSFMLWidget::QSFMLWidget(QWidget *parent) : QWidget(parent), initialized_(false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);
}

QPaintEngine *QSFMLWidget::paintEngine() const
{
    return nullptr;
}

void QSFMLWidget::showEvent(QShowEvent *event)
{
    if(!initialized_)
    {
        sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()));
        onInit();

        connect(&timer_, SIGNAL(timeout()), this, SLOT(repaint()));
        timer_.start();
        initialized_ = true;
    }
}

void QSFMLWidget::paintEvent(QPaintEvent *event)
{
    RenderWindow::clear();
    onUpdate();
    RenderWindow::display();
}

void QSFMLWidget::onInit()
{
    //To be overwritten
}

void QSFMLWidget::onUpdate()
{
    //To be overwritten
}



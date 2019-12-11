#include "sfmlviewwidget.h"
#include <QDebug>


SFMLViewWidget::SFMLViewWidget(QWidget *parent) : QSFMLWidget(parent)
{
    isimageSet_ = false;
}

void SFMLViewWidget::onInit()
{

}

void SFMLViewWidget::onUpdate()
{
    elapsedTime_ = clock_.getElapsedTime();
    clock_.restart();

    RenderWindow::clear(sf::Color(0, 0, 0));
    if(isimageSet_) {
        float w = static_cast<float>(size().width()/background_.getLocalBounds().width);
        float h = background_.getLocalBounds().height * w;
        background_.setScale(w, w);
        background_.setPosition(0, (size().height() - h)/2.f);
        RenderWindow::draw(background_);
    }
}

void SFMLViewWidget::setBackgroundTexture(std::string fname)
{
    textBackground_.loadFromFile(fname);
    background_.setTexture(textBackground_);
    isimageSet_ = true;
}

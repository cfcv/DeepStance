#include "sfmlviewwidget.h"
#include "rectangle.h"
#include "utils.h"
#include <QDebug>


SFMLViewWidget::SFMLViewWidget(QWidget *parent) : QSFMLWidget(parent)
{
    isimageSet_ = false;
    font_.loadFromFile("../rc/bahnschrift.ttf");
}

void SFMLViewWidget::onInit()
{

}

void SFMLViewWidget::onUpdate()
{
    elapsedTime_ = clock_.getElapsedTime();
    clock_.restart();

    Rectangle r(50, 50, 200, 300, "Desc.");

    RenderWindow::clear(sf::Color(0, 0, 0));
    if(isimageSet_) {
        float w = static_cast<float>(size().width()/background_.getLocalBounds().width);
        float h = background_.getLocalBounds().height * w;
        background_.setScale(w, w);
        background_.setPosition(0, (size().height() - h)/2.f);
        RenderWindow::draw(background_);
        r.draw(this, font_);
    }
}

void SFMLViewWidget::setBackgroundTexture(std::string fname)
{
    textBackground_.loadFromFile(fname);
    background_.setTexture(textBackground_);
    isimageSet_ = true;
}

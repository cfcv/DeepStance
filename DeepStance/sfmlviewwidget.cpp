#include "sfmlviewwidget.h"

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



    RenderWindow::clear(sf::Color(0, 0, 0));
    if(isimageSet_) {
        std::string cmd = "pythonw ../scripts/haar_cascade.pyw -p" + fname_;
        std::wstring widecmd = std::wstring(cmd.begin(), cmd.end());
        std::string results = Utility::runCmd(widecmd.c_str());
        std::vector<Rectangle> recs = parseBB(results);

        float w = static_cast<float>(size().width()/background_.getLocalBounds().width);
        float h = background_.getLocalBounds().height * w;
        delta_ = (size().height() - h)/2.f;
        background_.setScale(w, w);
        background_.setPosition(0, delta_);
        RenderWindow::draw(background_);
        for(auto &r:recs)
            r.draw(this, font_);
    }
}

void SFMLViewWidget::setBackgroundTexture(std::string fname)
{
    textBackground_.loadFromFile(fname);
    background_.setTexture(textBackground_);
    isimageSet_ = true;
    fname_ = fname;
}

std::vector<Rectangle> SFMLViewWidget::parseBB(std::string str)
{
    std::vector<Rectangle> res;
    std::vector<std::string> rectangles = Utility::split(str, "\r\n");

    for(auto s:rectangles) {
        s = s.substr(1, s.size() - 2);
        std::vector<std::string> params = Utility::split(s, ",");
        params[4] = params[4].substr(1, params[4].size() - 1);
        res.emplace_back(std::stoi(params[0]), std::stoi(params[1]) + delta_, std::stoi(params[2]), std::stoi(params[3]), params[4]);
    }

    return res;
}

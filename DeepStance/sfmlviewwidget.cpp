#include "sfmlviewwidget.h"

#include "utils.h"
#include <QDebug>


SFMLViewWidget::SFMLViewWidget(QWidget *parent) : QSFMLWidget(parent)
{
    isimageSet_ = false;
    paused_ = false;
    font_.loadFromFile("../rc/bahnschrift.ttf");
    method_ = 0;
}

void SFMLViewWidget::onInit()
{

}

void SFMLViewWidget::onUpdate()
{
    elapsedTime_ = clock_.getElapsedTime();
    clock_.restart();

    if(isimageSet_) {
        RenderWindow::clear(sf::Color(0, 0, 0));
        if(!paused_) {
            std::string cmd;

            if(method_ == 0)
                cmd = "pythonw ../scripts/haar_cascade.pyw -p" + fname_;
            else
                cmd = "";

            std::wstring widecmd = std::wstring(cmd.begin(), cmd.end());
            std::string results = "";

            recs_.clear();
            if(cmd != "") {
                results = Utility::runCmd(widecmd.c_str());
                recs_ = parseBB(results);
            }
        }


        ratio_ = static_cast<float>(size().width()/background_.getLocalBounds().width);
        float h = background_.getLocalBounds().height * ratio_;
        delta_ = (size().height() - h)/2.f;

        background_.setScale(ratio_, ratio_);
        background_.setPosition(0, delta_);
        RenderWindow::draw(background_);

        for(auto &r:recs_)
            r.draw(this, font_);
    }
}

void SFMLViewWidget::setBackgroundTexture(std::string fname)
{
    textBackground_.loadFromFile(fname);
    background_.setTexture(textBackground_);
    isimageSet_ = true;
    paused_ = false;
    fname_ = fname;
}

std::vector<Rectangle> SFMLViewWidget::parseBB(std::string str)
{
    std::vector<Rectangle> res;
    std::vector<std::string> rectangles = Utility::split(str, "\r\n");

    for(auto s:rectangles) {
        if(s[0] == '$') {
            qDebug() << QString::fromStdString(s);
            s = s.substr(1);
            std::vector<std::string> params = Utility::split(s, ",");
            params[4] = params[4].substr(1, params[4].size() - 1);
            res.emplace_back(std::stoi(params[0]) * ratio_,
                    std::stoi(params[1])*ratio_ + delta_,
                    std::stoi(params[2])* ratio_,
                    std::stoi(params[3])*ratio_,
                    params[4]);
        }

    }

    return res;
}

void SFMLViewWidget::setPause()
{
    paused_ = !paused_;
}

void SFMLViewWidget::setMethod(int ind)
{
    method_ = ind;
}

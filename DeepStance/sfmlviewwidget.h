#ifndef SFMLVIEWWIDGET_H
#define SFMLVIEWWIDGET_H



#include "qsfmlwidget.h"
#include "rectangle.h"

#include <vector>

class SFMLViewWidget : public QSFMLWidget
{
public:
    SFMLViewWidget(QWidget *parent);

    void onInit() override;
    void onUpdate() override;
    void setBackgroundTexture(std::string fname);

    std::vector<Rectangle> parseBB(std::string str);

    void setPause();
    void setMethod(int ind);

private:
    sf::Texture textBackground_;
    sf::Sprite background_;
    sf::Font font_;

    bool isimageSet_;
    std::string fname_;

    sf::Vector2f mousePosition_;

    sf::Time elapsedTime_;
    sf::Clock clock_;

    float delta_, ratio_;
    int method_;
    bool paused_;
    std::vector<Rectangle> recs_;
};

#endif // SFMLVIEWWIDGET_H

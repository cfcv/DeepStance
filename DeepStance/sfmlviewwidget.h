#ifndef SFMLVIEWWIDGET_H
#define SFMLVIEWWIDGET_H



#include "qsfmlwidget.h"


class SFMLViewWidget : public QSFMLWidget
{
public:
    SFMLViewWidget(QWidget *parent);

    void onInit() override;
    void onUpdate() override;
    void setBackgroundTexture(std::string fname);

private:
    sf::Texture textBackground_;
    sf::Sprite background_;
    sf::Font font_;

    bool isimageSet_;

    sf::Vector2f mousePosition_;

    sf::Time elapsedTime_;
    sf::Clock clock_;
};

#endif // SFMLVIEWWIDGET_H

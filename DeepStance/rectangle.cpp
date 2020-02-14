#include "rectangle.h"


Rectangle::Rectangle()
{
    x_ = 0;
    y_ = 0;
    w_ = 0;
    h_ = 0;
    description_ = "";
}

Rectangle::Rectangle(float x, float y, float w, float h)
{
    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;
    description_ = "";
}

Rectangle::Rectangle(float x, float y, float w, float h, std::string description)
{
    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;
    description_ = description;
}

void Rectangle::setDescrition(std::string desc)
{
    description_ = desc;
}

void Rectangle::setPosition(float x, float y)
{
    x_ = x;
    y_ = y;
}

void Rectangle::setScale(float w, float h)
{
    w_ = w;
    h_ = h;
}

void Rectangle::draw(sf::RenderWindow *window, sf::Font &f)
{
    sf::RectangleShape rec, desc;
    sf::Text desc_text;

    desc_text.setFont(f);
    desc_text.setFillColor(sf::Color::White);
    desc_text.setString(description_);
    desc_text.setCharacterSize(16);

    desc_text.setPosition(x_ + 5 - 3, y_ - 19);


    rec.setPosition(x_, y_);
    rec.setSize(sf::Vector2f(w_, h_));

    rec.setFillColor(sf::Color::Transparent);
    rec.setOutlineThickness(3);
    rec.setOutlineColor(sf::Color(0, 165, 0));


    desc.setPosition(x_ - 3, y_ - 20);
    desc.setSize(sf::Vector2f(desc_text.getGlobalBounds().width + 10, 20));
    desc.setFillColor(sf::Color(0, 165, 0));

    window->draw(rec);
    window->draw(desc);
    window->draw(desc_text);
}


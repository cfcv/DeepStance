#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <SFML/Graphics.hpp>

class Rectangle {
    private:
        float x_, y_, w_, h_;
        std::string description_;
    public:
        Rectangle();
        Rectangle(float x, float y, float w, float h);
        Rectangle(float x, float y, float w, float h, std::string description);


        void setDescrition(std::string desc);
        void setPosition(float x, float y);
        void setScale(float w, float h);

        void draw(sf::RenderWindow *window, sf::Font &f);
};

#endif // RECTANGLE_H

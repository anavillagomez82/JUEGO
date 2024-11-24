#ifndef BULLET_H
#define BULLET_H
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
using namespace std;
using namespace sf;

class Bullet : public GameObject {
public:
    Bullet(sf::Vector2f position, sf::Vector2f direction, float rotation, sf::Texture& texture);
    void Update() override; // Implementación del método Update
    sf::Vector2f GetPosition() const override; // Implementación del método GetPosition
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
};

#endif // BULLET_H

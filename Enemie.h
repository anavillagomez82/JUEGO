#ifndef ENEMIE_H
#define ENEMIE_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Enemie : public GameObject {
public:
    Enemie(sf::Vector2f position, sf::Texture& texture);
    void Update(sf::Vector2f playerPosition, int dist) override; // Implementación del método Update
    sf::Vector2f GetPosition() const override; // Implementación del método GetPosition
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Sprite sprite;
    float speed;
};

#endif // ENEMIE_H

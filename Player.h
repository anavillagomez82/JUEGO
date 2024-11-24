#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player : public GameObject {
public:
    Player(sf::Texture&);
    void Update(sf::RenderWindow&, sf::View&) override; // Implementación del método Update
    std::pair<bool, sf::Vector2f> AnswerShoot(sf::RenderWindow&);
    float GetRotation();
    sf::Vector2f GetPosition() const override; // Implementación del método GetPosition
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Sprite sprite;
    float vel;
    int cadence = 8;
    void Movement(sf::View&);
    void Aim(sf::RenderWindow&);
};

#endif // PLAYER_H

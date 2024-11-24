#include "Enemie.h"

Enemie::Enemie(sf::Vector2f position, sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    speed = 1.0f; // Velocidad del enemigo
}

void Enemie::Update(sf::Vector2f playerPosition, int dist) {
    sf::Vector2f direction = playerPosition - sprite.getPosition();
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction /= length; // Normalizar la dirección
        sprite.move(direction * speed); // Mover el enemigo hacia el jugador
    }
}

sf::Vector2f Enemie::GetPosition() const {
    return sprite.getPosition();
}

void Enemie::draw(sf::RenderTarget &rt, sf::RenderStates rs) const {
    rt.draw(sprite, rs);
}

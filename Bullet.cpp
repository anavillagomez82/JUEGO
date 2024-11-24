#include "Bullet.h"
#include "GameObject.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, float rotation, sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setRotation(rotation);
    velocity = direction * 5.0f; // Velocidad de la bala
}

void Bullet::Update() {
    sprite.move(velocity); // Mover la bala
}

sf::Vector2f Bullet::GetPosition() const {
    return sprite.getPosition();
}

void Bullet::draw(sf::RenderTarget &rt, sf::RenderStates rs) const {
    rt.draw(sprite, rs);
}

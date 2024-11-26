#include "Player.h"

Player::Player(Texture &texture) : Character(texture, Vector2f(0, 0)) {
    sprite.setTextureRect(IntRect(0, 115, 250, 115));
    sprite.setScale(0.35, 0.35);
    sprite.setOrigin((250 / 2) / 2, 115 / 2);
    sprite.setPosition(0, 0);
    vel = 2.5;
    Hp = 100; // Asignar HP inicial
}

void Player::Update(RenderWindow &rw, View &view) {
    // Implementación del movimiento
    if (Keyboard::isKeyPressed(Keyboard::W) && sprite.getPosition().y > -485) {
        sprite.move(0, -vel);
        view.move(0, -vel);
    }
    if (Keyboard::isKeyPressed(Keyboard::S) && sprite.getPosition().y < 485) {
        sprite.move(0, vel);
        view.move(0, vel);
    }
    if (Keyboard::isKeyPressed(Keyboard::D) && sprite.getPosition().x < 735) {
        sprite.move(vel, 0);
        view.move(vel, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::A) && sprite.getPosition().x > -735) {
        sprite.move(-vel, 0);
        view.move(-vel, 0);
    }
}

void Player::apuntar(RenderWindow &rw) {
    sprite.setRotation(atan2(Mouse::getPosition(rw).y - rw.mapCoordsToPixel(sprite.getPosition()).y,
                              Mouse::getPosition(rw).x - rw.mapCoordsToPixel(sprite.getPosition()).x) * 180 / 3.14159265f);
}

pair<bool, Vector2f> Player::AnswerShoot(RenderWindow &rw) {
    Vector2f direc = Vector2f(Mouse::getPosition(rw)) - Vector2f(rw.mapCoordsToPixel(sprite.getPosition()));
    Vector2f dirNorm = Vector2f(direc.x / sqrt(pow(direc.x, 2) + pow(direc.y, 2)), direc.y / sqrt(pow(direc.x, 2) + pow(direc.y, 2)));

    // Implementación de la lógica de disparo
    return {false, dirNorm}; // Placeholder, deberías implementar la lógica de disparo
}

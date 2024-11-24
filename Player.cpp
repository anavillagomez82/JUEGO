#include "Player.h"
#include "GameObject.h"

Player::Player(sf::Texture &texture) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 115, 250, 115));
    sprite.setScale(0.35, 0.35);
    sprite.setOrigin((250 / 2) / 2, 115 / 2);
    sprite.setPosition(0, 0);
    vel = 2;
}

void Player::Update(sf::RenderWindow &rw, sf::View &view) {
    Movement(view);
    Aim(rw);
}

void Player::Movement(sf::View &view) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getPosition().y > -485) {
        sprite.move(0, -vel);
        view.move(0, -vel);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprite.getPosition().y < 485) {
        sprite.move(0, vel);
        view.move(0, vel);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprite.getPosition().x < 735) {
        sprite.move(vel, 0);
        view.move(vel, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sprite.getPosition().x > -735) {
        sprite.move(-vel, 0);
        view.move(-vel, 0);
    }
}

void Player::Aim(sf::RenderWindow &rw) {
    sprite.setRotation(atan2(sf::Mouse::getPosition(rw).y - rw.mapCoordsToPixel(sprite.getPosition()).y, 
                              sf::Mouse::getPosition(rw).x - rw.mapCoordsToPixel(sprite.getPosition()).x) * 180 / 3.14159265f);
}

std::pair<bool, sf::Vector2f> Player::AnswerShoot(sf::RenderWindow &rw) {
    sf::Vector2f dir = sf::Vector2f(sf::Mouse::getPosition(rw)) - sf::Vector2f(rw.mapCoordsToPixel(sprite.getPosition()));
    sf::Vector2f dirNorm = sf::Vector2f(dir.x / sqrt(pow(dir.x, 2) + pow(dir.y, 2)), 
                                             dir.y / sqrt(pow(dir.x, 2) + pow(dir.y, 2)));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cadence >= 8) {
        cadence = 1;
        sprite.setTextureRect(sf::IntRect(0, 0, 250, 115));
        return {true, dirNorm};
    }
    cadence++;
    if (cadence == 4) sprite.setTextureRect(sf::IntRect(0, 115, 250, 115));

    return {false, dirNorm};
}

float Player::GetRotation() {
    return sprite.getRotation();
}

sf::Vector2f Player::GetPosition() const {
    return sprite.getPosition();
}

void Player::draw(sf::RenderTarget &rt, sf::RenderStates rs) const {
    rt.draw(sprite, rs);
}

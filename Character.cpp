#include "Character.h"

Character::Character(Texture& texture, Vector2f pos) {
    sprite.setTexture(texture);
    sprite.setPosition(pos);
}

void Character::TakeHp(int damage) {
    Hp -= damage;
}

int Character::ConsultHp() const {
    return Hp;
}

void Character::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}

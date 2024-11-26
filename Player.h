#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
public:
    Player(Texture&);
    void Update(RenderWindow &rw, View &view) override; // Implementación del método
    void apuntar(RenderWindow &rw);
    pair<bool, Vector2f> AnswerShoot(RenderWindow &rw);
    float GetRotation();
};

#endif

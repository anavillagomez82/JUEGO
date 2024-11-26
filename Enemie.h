#ifndef ENEMIE_H
#define ENEMIE_H

#include "Character.h"

class Enemie : public Character {
public:
    Enemie(Vector2f pos, Texture &texture);
    void Update(Vector2f posPlayer, int dista) override; // Implementación del método
};

#endif

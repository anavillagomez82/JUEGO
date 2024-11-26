#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Character : public Drawable {
protected:
    Sprite sprite;
    float vel;
    int Hp;
    Vector2f position;

public:
    Character(Texture& texture, Vector2f pos);
    virtual void Update(Vector2f playerPos, int dist) = 0; // Método virtual puro
    virtual Vector2f GetPosition() const { return sprite.getPosition(); }
    virtual void TakeHp(int damage);
    virtual int ConsultHp() const;
    virtual void draw(RenderTarget &target, RenderStates states) const override;
};

#endif

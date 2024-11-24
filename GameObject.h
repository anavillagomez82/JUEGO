#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject : public sf::Drawable {
public:
    virtual void Update(sf::RenderWindow&, sf::View&) = 0; // Método virtual puro para Player
    virtual void Update(sf::Vector2f, int) = 0; // Método virtual puro para Enemie
    virtual sf::Vector2f GetPosition() const = 0; // Método virtual puro para obtener la posición
};

#endif // GAMEOBJECT_H

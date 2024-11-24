#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject : public sf::Drawable {
public:
    virtual void Update() = 0; // Método virtual puro para actualizar el objeto
    virtual sf::Vector2f GetPosition() const = 0; // Método virtual puro para obtener la posición
};

#endif // GAMEOBJECT_H

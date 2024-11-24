#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemie.h"
#include "UISounds.h"
#include "Menu.h"
#include "GameObject.h" // Incluir la clase base GameObject

using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(1000, 650), "Rebel Shooter");
    window.setFramerateLimit(60);

    // Crear el menú
    Menu menu;

    // Variable para controlar el estado del juego
    bool inMenu = true;
    bool live = true;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();

            // Manejar la entrada del menú
            if (inMenu) {
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Up) {
                        menu.MoveUp();
                    }
                    if (event.key.code == Keyboard::Down) {
                        menu.MoveDown();
                    }
                    if (event.key.code == Keyboard::Enter) {
                        if (menu.isStartPressed()) {
                            inMenu = false; // Iniciar el juego
                        } else {
                            window.close(); // Salir del juego
                        }
                    }
                }
            }
        }

        window.clear();

        if (inMenu) {
            menu.draw(window); // Dibujar el menú
        } else {
            View view;
            view.setSize(1000, 650);
            view.setCenter(0, 0);

            // Cargar texturas
            Texture playerTexture;
            Texture enemyTexture;
            Texture bulletTexture;
            Texture backgroundTexture;

            if (!playerTexture.loadFromFile("player.png")) {
                cout << "Error al cargar la textura del jugador" << endl;
            }
            if (!enemyTexture.loadFromFile("enemy.png")) {
                cout << "Error al cargar la textura del enemigo" << endl;
            }
            if (!bulletTexture.loadFromFile("bullet.png")) {
                cout << "Error al cargar la textura de la bala" << endl;
            }
            if (!backgroundTexture.loadFromFile("background.png")) {
                cout << "Error al cargar la textura del fondo" << endl;
            }

            Sprite background;
            background.setTexture(backgroundTexture);
            background.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
            background.setPosition(0, 0);

            UISounds uisounds;
            Player player(playerTexture);
            vector<Enemie*> enemies; // Usar punteros a Enemie
            vector<GameObject*> bulletsPlayer; // Usar punteros a GameObject
            Vector2f bulletPosition;
            Vector2f playerPos;
            Vector2f enemiePos;
            bool live = true;
            int dist = 350;
            int score = 0;

            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) window.close();
                }

                if (live) {
                    srand(time(NULL));
                    while ((int)enemies.size() < 60) {
                        IntRect backgroundRect(player.GetPosition().x - 500, player.GetPosition().y - 325, 1000, 650);
                        int x = rand() % 1450 - 725; 
                        int y = rand() % 950 - 475;
                        if (!backgroundRect.contains(x, y)) {
                            enemies.push_back(new Enemie(Vector2f(x, y), enemyTexture)); // Crear enemigos con new
                        }
                    }

                    player.Update(window, view); // Actualizar jugador

                    for (auto enemy : enemies) {
                        enemy->Update(player.GetPosition(), dist); // Llamar a Update de cada enemigo
                    }

                    playerPos = Vector2f(window.mapCoordsToPixel(player.GetPosition()));
                    IntRect playerRect(playerPos.x - 10, playerPos.y - 10, 25, 25);
                    for (auto enemy : enemies) {
                        enemiePos = enemy->GetPosition();
                        IntRect enemiesRect(enemiePos.x - 10, enemiePos.y - 10, 25, 25);
                        if (enemiesRect.intersects(playerRect)) live = false; // Si colisiona con un enemigo
                    }

                    pair<bool, Vector2f> infoBullet = player.AnswerShoot(window);
                    if (infoBullet.first) {
                        bulletsPlayer.push_back(new Bullet(Vector2f(player.GetPosition().x + infoBullet.second.x * 10, player.GetPosition().y + infoBullet.second.y * 10), bulletTexture, infoBullet.second)); // Crear una nueva bala
                    }

                    for (auto bullet : bulletsPlayer) {
                        bullet->Update(); // Actualizar cada bala
                    }

                    window.clear();
                    window.setView(view);
                    window.draw(background); // Dibujar fondo
                    window.draw(player); // Dibujar jugador

                    for (auto enemy : enemies) {
                        window.draw(*enemy); // Dibujar enemigos
                    }

                    for (auto bullet : bulletsPlayer) {
                        window.draw(*bullet); // Dibujar balas
                    }

                    window.display();
                } else {
                    // Lógica para manejar el fin del juego
                    // Aquí puedes mostrar un mensaje de "Game Over" o similar
                }
            }

            // Liberar memoria
            for (auto enemy : enemies) {
                delete enemy; // Liberar memoria de enemigos
            }
            for (auto bullet : bulletsPlayer) {
                delete bullet; // Liberar memoria de balas
            }
        }

        window.display();
    }

    return 0;
}

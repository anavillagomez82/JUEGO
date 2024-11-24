#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Bullet.h"
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

            Texture playerTexture;
            Texture enemieTexture;
            Texture bulletTexture;
            Texture bloodTexture;
            Texture backgroundTexture;

            if (!playerTexture.loadFromFile("player.png")) {
                cout << "Error al cargar la textura" << endl;
            }
            if (!enemieTexture.loadFromFile("enemie.png")) {
                cout << "Error al cargar la textura" << endl;
            }
            if (!bulletTexture.loadFromFile("bullet.png")) {
                cout << "Error al cargar la textura" << endl;
            }
            if (!bloodTexture.loadFromFile("blood.png")) {
                cout << "Error al cargar la textura" << endl;
            }
            if (!backgroundTexture.loadFromFile("background.png")) {
                cout << "Error al cargar la textura" << endl;
            }

            Sprite background;
            background.setTexture(backgroundTexture);
            background.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
            background.setPosition(0, 0);

            UISounds uisounds;
            Player player(playerTexture);
            vector<GameObject*> enemies; // Usar punteros a GameObject
            vector<GameObject*> bulletsPlayer; // Usar punteros a GameObject
            vector<pair<Sprite, float>> bloodEnemies;
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
                            enemies.push_back(new Enemie(Vector2f(x, y), enemieTexture)); // Crear enemigos con new
                        }
                    }

                    player.Update(window, view);

                    for (auto enemy : enemies) {
                        enemy->Update(player.GetPosition(), dist); // Llamar a Update de cada enemigo
                    }

                    playerPos = Vector2f(window.mapCoordsToPixel(player.GetPosition()));
                    IntRect playerRect(playerPos.x - 10, playerPos.y - 10, 25, 25);
                    for (auto enemy : enemies) {
                        enemiePos = enemy->GetPosition();
                        IntRect enemiesRect(enemiePos.x - 10, enemiePos.y - 10, 25, 25);
                        if (enemiesRect.intersects(playerRect)) live = false;
                    }

                    pair<bool, Vector2f> infoBullet = player.AnswerShoot(window);
                    if (infoBullet.first ) {
                        bulletsPlayer.push_back(new Bullet(Vector2f(player.GetPosition().x + infoBullet.second.x * 40, player.GetPosition().y + infoBullet.second.y * 40), infoBullet.second, player.GetRotation(), bulletTexture)); // Crear balas con new
                    }

                    for (auto bullet : bulletsPlayer) {
                        bullet->Update(); // Llamar a Update de cada bala
                    }

                    // Dibujo
                    window.draw(background);
                    for (auto enemy : enemies) {
                        window.draw(*enemy); // Dibujar cada enemigo
                    }
                    for (auto bullet : bulletsPlayer) {
                        window.draw(*bullet); // Dibujar cada bala
                    }
                    window.draw(player); // Dibujar al jugador
                } else {
                    // Lógica para manejar el fin del juego
                }

                window.display();
            }

            // Liberar memoria
            for (auto enemy : enemies) {
                delete enemy;
            }
            for (auto bullet : bulletsPlayer) {
                delete bullet;
            }
        }

        window.display();
    }

    return 0;
}

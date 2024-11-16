#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <vector>
#include <iostream>
#include "menu.h"
#include "maze.h"
#include "inventory.h"
#include "player.h"
#include "enemy.h"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

int SCORE = 0;

using namespace sf;

class Game {
private:
    SoundBuffer buffer;
    Sound sound;

public:
    Game() {
        buffer.loadFromFile("sounds/Startup.mp3");
        sound.setBuffer(buffer);
    }

    void start_game() {
        int count = 0;
        std::vector<std::pair<int, int>> shortestPath;

        sound.play();
        sound.setLoop(true);

        RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Enchanted Lybrinth");

        Maze maze(WINDOW_HEIGHT / CELL_SIZE, 900 / CELL_SIZE); // Adjusted maze dimensions
        Player player(CELL_SIZE / 2.0f);

        // enemies
        Enemy enemy;

        Inventory inventory;
        inventory.generateObjects(maze, 6);

        player.setPosition(Vector2f(20, 600));

        Texture backgroundTexture;
        backgroundTexture.loadFromFile("images/Inventory (3) (1).png");
        Sprite background(backgroundTexture);
        background.setScale(2, 2);

        while (window.isOpen()) {
            Event event;
            // enemy movement 
            if (count > 3) {
                enemy.move(maze, Vector2f(player.getPositionY(), player.getPositionX()), player, window); // Corrected call with player position
                count = 0;
            }
            else {
                count += 1;
            }
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::KeyPressed) {

                    int playerCellX = static_cast<int>(player.getPositionX() / CELL_SIZE);
                    int playerCellY = static_cast<int>(player.getPositionY() / CELL_SIZE);

                    if (event.key.code == sf::Keyboard::Up && playerCellY > 0 && !maze.isWall(playerCellY - 1, playerCellX))
                        player.move(0, -CELL_SIZE);
                    else if (event.key.code == sf::Keyboard::Down && playerCellY < maze.getRows() - 1 && !maze.isWall(playerCellY + 1, playerCellX))
                        player.move(0, CELL_SIZE);
                    else if (event.key.code == sf::Keyboard::Left && playerCellX > 0 && !maze.isWall(playerCellY, playerCellX - 1))
                        player.move(-CELL_SIZE, 0);
                    else if (event.key.code == sf::Keyboard::Right && playerCellX < maze.getCols() - 1 && !maze.isWall(playerCellY, playerCellX + 1))
                        player.move(CELL_SIZE, 0);
                    else if (event.key.code == Keyboard::H) {
                        int rows = maze.getRows();
                        int cols = maze.getCols();
                        Graph graph(rows, cols, maze); // Corrected constructor parameters
                        shortestPath = graph.shortestPath(playerCellY, playerCellX, maze.getExitY(), maze.getExitX(), maze);

                        /*if (!shortestPath.empty()) {
                            std::cout << "Shortest path from start to end: ";
                            for (const auto& cell : shortestPath) {
                                std::cout << "(" << cell.first << ", " << cell.second << ") ";
                            }
                            std::cout << std::endl;
                        }
                        else {
                            std::cout << "No path found from start to end." << std::endl;
                        }*/
                    }

                }
                inventory.collectInventory(player, event);
            }

            window.clear();
            window.draw(background);
            maze.draw(window);
            player.collectedItems.displayInventoryOnScreen(player.collectedItems.root, window);
            maze.printScore(player.score, window);
            enemy.draw(window);
            player.draw(window);
            inventory.drawObjects(window);
            maze.drawShortestPath(window, shortestPath);
            if (maze.isWon(static_cast<int>(player.getPositionY() / CELL_SIZE), static_cast<int>(player.getPositionX() / CELL_SIZE))) {
                GameOver go;
                go.displayGameOverWindow(window, player.score);
            }
            SCORE = player.score;

            window.display();
        }
    }
};

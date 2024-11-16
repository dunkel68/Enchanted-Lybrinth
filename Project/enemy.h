#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath> 
#include "maze.h"
#include "gameEnd.h"

using namespace std;
using namespace sf;

class Node4 {
public:
    Texture invTexture;
    Sprite invSprite;
    Vector2f position;
    int points;

    Node4() {
        int posX = rand() % 40 + 2;
        int posY = rand() % 35 + 2;

        position = Vector2f(posX, posY);

        invTexture.loadFromFile("images/enemy.png");
        invSprite.setTexture(invTexture);
        invSprite.setScale(0.05f, 0.05f);
        points = 40;

    }

    // setters getters 
    void setPosition(Vector2f pos) {
        position = pos;
    }

    int getPositionX() const {
        return position.x;
    }

    int getPositionY() const {
        return position.y;
    }

    // Move the enemy by the given offsets
    void incPosition(int offsetX, int offsetY) {
        position.x += offsetX;
        position.y += offsetY;

    }

    bool checkAndRemoveIfPlayerNearby(const Vector2f& playerPosition) {
        int playerCellX = static_cast<int>(playerPosition.x / CELL_SIZE);
        int playerCellY = static_cast<int>(playerPosition.y / CELL_SIZE);

        if (static_cast<int>(position.y) == playerCellX && static_cast<int>(position.x) == playerCellY) {
            // Player and enemy are at the same position, remove the enemy
            return true;
        }

        return false;

    }
};


class Enemy {
private:

    Node4* enemies;
    int noof;


public:
    Enemy() {
        noof = 3;
        enemies = new Node4[noof];
    }

    ~Enemy() {
        delete[] enemies;
    }


    void move(const Maze& maze, const Vector2f& playerPosition, Player& player, RenderWindow& window) {
        // Vector to store the shortest paths for each enemy
        vector<vector<pair<int, int>>> shortestPaths(noof);
        vector<int> enemiesToRemove;

        // Check for collision and mark enemies to be removed
        for (int i = 0; i < noof; i++) {

            int playerCellX = static_cast<int>(playerPosition.x / CELL_SIZE);
            int playerCellY = static_cast<int>(playerPosition.y / CELL_SIZE);

            if (Vector2f(enemies[i].getPositionY(), enemies[i].getPositionX()) == Vector2f(playerCellX, playerCellY)) {
                player.score -= enemies[i].points;
                if (player.score < 0) {
                    GameOver go;
                    go.displayGameOverWindow(window, player.score);
                }
                // Add the index of the enemy to be removed
                enemiesToRemove.push_back(i);
                continue; // Skip processing this enemy
            }

            // Find the shortest path from the enemy's position to the player's position
            Graph graph(maze.getRows(), maze.getCols(), maze);
            shortestPaths[i] = graph.shortestPath(enemies[i].position.y, enemies[i].position.x, playerCellX, playerCellY, maze);

        }

        // Remove enemies marked for removal
        for (int index : enemiesToRemove) {
            // Shift elements to the left to remove the enemy from the array
            for (int j = index; j < noof - 1; j++) {
                enemies[j] = enemies[j + 1];
            }
            noof--;
        }

        // Check if any two enemies have the same shortest path
        /*for (int i = 0; i < noof - 1; i++) {
            for (int j = i + 1; j < noof; j++) {
                if (shortestPaths[i] == shortestPaths[j]) {
                    shortestPaths[j] = generateNewPath(shortestPaths[j]);
                }
            }
        }*/

        for (int i = 0; i < noof; i++) {
            // Move the enemy along the shortest path if one exists
            if (!shortestPaths[i].empty() && shortestPaths[i].size() > 1) {
                // The next position along the shortest path is the second element in the path vector
                pair<int, int> nextPosition = shortestPaths[i][1];
                // Calculate the direction vector to move towards the next position
                Vector2f direction(nextPosition.second - enemies[i].position.x, nextPosition.first - enemies[i].position.y);

                // Normalize the direction vector to ensure constant speed
                float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                if (length != 0) {
                    direction /= length;
                }

                // Move the enemy towards the next position
                enemies[i].position += direction;
            }
        }



        //else {
        //    Vector2f direction(0, 0);
        //    int minDistance = std::numeric_limits<int>::max();

        //    //
        //    //if (playerCellY < position.y && !maze.isWall(position.y - 1, position.x)) {
        //    //    int distance = position.y - 1 - playerCellY + abs(position.x - playerCellX);
        //    //    if (distance < minDistance) {
        //    //        minDistance = distance;
        //    //        direction.x = 0;
        //    //        direction.y = -1; // Move up
        //    //    }
        //    //}
        //    //else if (playerCellY > position.y && !maze.isWall(position.y + 1, position.x)) {
        //    //    int distance = playerCellY - position.y - 1 + abs(position.x - playerCellX);
        //    //    if (distance < minDistance) {
        //    //        minDistance = distance;
        //    //        direction.x = 0;
        //    //        direction.y = 1; // Move down
        //    //    }
        //    //}
        //    //else if (playerCellX < position.x && !maze.isWall(position.y, position.x - 1)) {
        //    //    int distance = position.x - 1 - playerCellX + abs(position.y - playerCellY);
        //    //    if (distance < minDistance) {
        //    //        minDistance = distance;
        //    //        direction.x = -1; // Move left
        //    //        direction.y = 0;
        //    //    }
        //    //}
        //    //else if (playerCellX > position.x && !maze.isWall(position.y, position.x + 1)) {
        //    //    int distance = playerCellX - position.x - 1 + abs(position.y - playerCellY);
        //    //    if (distance < minDistance) {
        //    //        minDistance = distance;
        //    //        direction.x = 1; // Move right
        //    //        direction.y = 0;
        //    //    }
        //    //}
        //    //else {
        //    if (!maze.isWall(position.y - 1, position.x)) {
        //        int distance = position.y - 1 - playerCellY + abs(position.x - playerCellX);
        //        if (distance < minDistance) {
        //            minDistance = distance;
        //            direction.x = 0;
        //            direction.y += -1; // Move up
        //        }
        //    }
        //    if (!maze.isWall(position.y + 1, position.x)) {
        //        int distance = playerCellY - position.y - 1 + abs(position.x - playerCellX);
        //        if (distance < minDistance) {
        //            minDistance = distance;
        //            direction.x = 0;
        //            direction.y += 1; // Move down
        //        }
        //    }
        //    if (!maze.isWall(position.y, position.x - 1)) {
        //        int distance = position.x - 1 - playerCellX + abs(position.y - playerCellY);
        //        if (distance < minDistance) {
        //            minDistance = distance;
        //            direction.x += -1; // Move left
        //            direction.y = 0;
        //        }
        //    }
        //    if (!maze.isWall(position.y, position.x + 1)) {
        //        int distance = playerCellX - position.x - 1 + abs(position.y - playerCellY);
        //        if (distance < minDistance) {
        //            minDistance = distance;
        //            direction.x += 1; // Move right
        //            direction.y = 0;
        //        }
        //    }


        //    // Update the enemy's position with the chosen direction
        //    position += direction;
        //}


    }

    vector<pair<int, int>> generateNewPath(const vector<pair<int, int>>& oldPath) {
        vector<pair<int, int>> newPath;

        // Offset the new path by a random amount
        for (const auto& node : oldPath) {
            // Add a random offset to each node in the path
            pair<int, int> newNode;
            do {
                newNode.first = node.first + rand() % 3 - 1; // Offset the y-coordinate by -1, 0, or 1
                newNode.second = node.second + rand() % 3 - 1; // Offset the x-coordinate by -1, 0, or 1
            } while (newNode == node); // Ensure the new node is different from the old one
            newPath.push_back(newNode);
        }

        return newPath;
    }



    // Draw the enemy sprite
    void draw(RenderWindow& window) {
        for (int i = 0; i < noof; i++) {
            enemies[i].invSprite.setPosition(enemies[i].position.x * 20.0, enemies[i].position.y * 20.0);
            window.draw(enemies[i].invSprite);
        }
    }



};

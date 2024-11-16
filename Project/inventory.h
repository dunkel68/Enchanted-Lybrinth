#ifndef INVENTORY_H
#define INVENTORY_H
#include <SFML/Graphics.hpp>
//#include <vector>
#include <iostream>
#include "player.h"
#include "avl.h"
using namespace std;
using namespace sf;

//class Inventory {
//private:
//    int rows, cols;
//    std::vector<std::vector<bool>> grid;
//    std::vector<sf::Vector2i> objectPositions; // Positions of objects in the maze
//
//public:
//    Inventory(int rows, int cols) : rows(rows), cols(cols) {
//        // Initialize grid with all walls
//        grid.resize(rows, std::vector<bool>(cols, true));
//
//        // Generate objects in the maze
//        generateObjects();
//    }
//
//    void generateObjects() {
//        // Generate objects at random positions in the maze
//        std::srand(std::time(nullptr));
//        for (int i = 0; i < 5; ++i) { // Generate 5 objects
//            int posX = std::rand() % (cols - 2) + 1; // Random x-coordinate within the maze boundaries
//            int posY = std::rand() % (rows - 2) + 1; // Random y-coordinate within the maze boundaries
//
//            // Check if the position is not already occupied by another object
//            if (!grid[posY][posX]) {
//                objectPositions.push_back(sf::Vector2i(posX, posY));
//            }
//        }
//    }
//
//    std::vector<sf::Vector2i> getObjectPositions() const {
//        return objectPositions;
//    }
//
//    void drawObjects(sf::RenderWindow& window) {
//        sf::CircleShape objectShape(CELL_SIZE / 3); // Size of the object
//
//        // Draw objects at their positions
//        for (const auto& position : objectPositions) {
//            objectShape.setFillColor(sf::Color::Yellow); // Set color of the object
//            objectShape.setPosition(position.x * CELL_SIZE + CELL_SIZE / 3, position.y * CELL_SIZE + CELL_SIZE / 3); // Center object in cell
//            window.draw(objectShape);
//        }
//    }
//};

//class Inventory {
//private:
//    int rows, cols;
//    bool** grid;
//    sf::Vector2i* objectPositions;
//    int objectCount;
//
//public:
//    Inventory(int rows, int cols) : rows(rows), cols(cols) {
//        // Initialize grid with all walls
//        grid = new bool* [rows];
//        for (int i = 0; i < rows; ++i) {
//            grid[i] = new bool[cols];
//            for (int j = 0; j < cols; ++j) {
//                grid[i][j] = true;
//            }
//        }
//
//        // Generate objects in the maze
//        generateObjects();
//    }
//
//    ~Inventory() {
//        for (int i = 0; i < rows; ++i) {
//            delete[] grid[i];
//        }
//        delete[] grid;
//        delete[] objectPositions;
//    }
//
//    void generateObjects() {
//        // Generate objects at random positions in the maze
//        std::srand(static_cast<unsigned int>(std::time(nullptr)));
//        objectCount = 5; // Generate 5 objects
//        objectPositions = new sf::Vector2i[objectCount];
//
//        for (int i = 0; i < objectCount; ++i) {
//            int posX = std::rand() % (cols - 2) + 1; // Random x-coordinate within the maze boundaries
//            int posY = std::rand() % (rows - 2) + 1; // Random y-coordinate within the maze boundaries
//
//            // Check if the position is not already occupied by another object
//            if (!grid[posY][posX]) {
//                objectPositions[i] = sf::Vector2i(posX, posY);
//            }
//            else {
//                --i; // Decrement the loop counter to try again
//            }
//        }
//    }
//
//    sf::Vector2i* getObjectPositions() const {
//        return objectPositions;
//    }
//
//    int getObjectCount() const {
//        return objectCount;
//    }
//
//    void drawObjects(sf::RenderWindow& window) {
//        sf::CircleShape objectShape(CELL_SIZE / 3); // Size of the object
//
//        // Draw objects at their positions
//        for (int i = 0; i < objectCount; ++i) {
//            objectShape.setFillColor(sf::Color::Yellow); // Set color of the object
//            objectShape.setPosition(objectPositions[i].x * CELL_SIZE + CELL_SIZE / 3, objectPositions[i].y * CELL_SIZE + CELL_SIZE / 3); // Center object in cell
//            window.draw(objectShape);
//        }
//    }
//};

//class Inventory {
//private:
//    sf::CircleShape shape;
//    sf::Vector2f position;
//    float radius;
//
//public:
//    Inventory(float radius) : radius(radius) {
//        shape.setRadius(radius);
//        shape.setFillColor(sf::Color::Blue);
//    }
//
//    void setPosition(sf::Vector2f pos) {
//        position = pos;
//        shape.setPosition(position);
//    }
//
//    float getPositionX() const {
//        return position.x;
//    }
//
//    float getPositionY() const {
//        return position.y;
//    }
//
//    void move(float offsetX, float offsetY) {
//        position.x += offsetX;
//        position.y += offsetY;
//        shape.setPosition(position);
//    }
//
//    void draw(sf::RenderWindow& window) {
//        window.draw(shape);
//    }
//};

class invNode {
    int posX, posY;
public:
    int data;
    string category;
    Texture invTexture;
    Sprite invSprite;
    invNode* next;
    invNode(int x = -1, int y = -1) {
        next = NULL;
        posX = x;
        posY = y;
        data = 0;
        /*invTexture.loadFromFile("images/por2.jpeg");
        invSprite.setTexture(invTexture);
        invSprite.setScale(0.05f, 0.05f);*/
    }
    int getPositionX() const {
        return posX;
    }

    int getPositionY() const {
        return posY;
    }

    void setPositionX(int x) {
        posX = x;
    }

    void setPsoitionY(int y) {
        posY = y;
    }
};

class Inventory {
private:
    invNode* head;
    /*Texture invTexture;
    Sprite invSprite;*/
    sf::Vector2i* objectPositions;
    int objectCount;

public:
    Inventory() : objectPositions(nullptr), objectCount(0) {
        head = NULL;
        /*invTexture.loadFromFile("images/por1.jpeg");
        invSprite.setTexture(invTexture);
        invSprite.setScale(0.05f, 0.05f);*/
    }

    ~Inventory() {
        delete[] objectPositions;
    }

    invNode* getHead() {
        if (!head)
            return NULL;
        else
            return head;
    }

    void insert(int x, int y) {
        if (!head) {
            head = new invNode(x, y);
            makeSprite();
            return;
        }
        else {
            invNode* current = head;
            invNode* temp = new invNode(x, y);
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = temp;
            makeSprite();
            current = NULL;
            temp = NULL;
            delete current, temp;
            return;
        }
    }

    void generateObjects(const Maze& maze, int numObjects) {
        objectCount = numObjects;
        objectPositions = new sf::Vector2i[numObjects];

        for (int i = 0; i < numObjects; ++i) {
            int posX = rand() % maze.getSize().y;  //rand() % maze.getCols();
            int posY = rand() % maze.getSize().x;  //rand() % maze.getRows();

            // Check if the position is not a wall
            while (maze.isWall(posY, posX) || posX < 2 || posY < 2 || posX > 40 || posY > 35) {
                posX = rand() % maze.getSize().y;  //std::rand() % maze.getCols();
                posY = rand() % maze.getSize().x;  //std::rand() % maze.getRows();
            }

            objectPositions[i] = sf::Vector2i(posX, posY);
            insert(posX, posY);
        }
    }

    sf::Vector2i* getObjectPositions() const {
        return objectPositions;
    }

    /*float getPositionX(int i) const {
        return objectPositions[i].x;
    }

    float getPositionY(int i) const {
        return objectPositions[i].y;
    }*/

    int getObjectCount() const {
        return objectCount;
    }

    void drawObjects(sf::RenderWindow& window) {
        //sf::CircleShape objectShape(CELL_SIZE / 3); // Size of the object
        //objectShape.setFillColor(sf::Color::Black);
        /*invNode* current = head;
        if (!head) {
            for (int i = 0; i < objectCount; ++i) {
                head->invSprite.setPosition(objectPositions[i].x * CELL_SIZE + (CELL_SIZE / 4), objectPositions[i].y * CELL_SIZE + (CELL_SIZE / 4));
                window.draw(head->invSprite);
            }
        }*/
        invNode* current = head;
        for (int i = 0; i < objectCount; ++i) {
            current->invSprite.setPosition(objectPositions[i].x * CELL_SIZE + (CELL_SIZE / 4), objectPositions[i].y * CELL_SIZE + (CELL_SIZE / 4));
            window.draw(current->invSprite);
            current = current->next;
        }
        /*while (current) {
            current->invSprite.setPosition(current->getPositionX() * CELL_SIZE + (CELL_SIZE / 4), current->getPositionY() * CELL_SIZE + (CELL_SIZE / 4));
            window.draw(current->invSprite);
        }*/
    }

    void removeObject(int x, int y) {
        invNode* current = head;
        bool remove = 0;
        if (!head)
            return;
        else if (head->getPositionX() == x && head->getPositionY() == y) {
            invNode* temp = head;
            head = head->next;
            delete temp;
            temp = NULL;
            remove = 1;
        }
        else {
            while (current->next) {
                if (current->next->getPositionX() == x && current->next->getPositionY() == y) {
                    invNode* temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                    current = NULL;
                    delete current;
                    remove = 1;
                    break;
                }
                current = current->next;
            }
        }
        if (remove) {
            for (int i = 0; i < objectCount; ++i) {
                if (x == objectPositions[i].x && y == objectPositions[i].y) {
                    objectPositions[i].x = -1;
                    objectPositions[i].y = -1;
                    for (int k = i; k < objectCount; k++) {
                        objectPositions[k] = objectPositions[k + 1];
                    }
                    objectCount--;
                    break;
                }
            }
        }
        return;
    }

    void makeSprite() {
        invNode* current = head;
        int cnt = 1;
        while (current->next) {
            current = current->next;
            cnt++;
        }
        if (current == NULL)
            return;
        else if (current == head) {      // key
            head->invTexture.loadFromFile("images/key.png");
            head->invSprite.setTexture(head->invTexture);
            head->invSprite.setScale(0.07f, 0.07f);
            head->data = 90;
            head->category = "key";
        }
        else if (cnt == 2) {        // swrord - I
            current->invTexture.loadFromFile("images/sword1.png");
            current->invSprite.setTexture(current->invTexture);
            current->invSprite.setScale(0.08f, 0.08f);
            current->data = 60;
            current->category = "sword-1";
        }
        else if (cnt == 3) {        // swrord - II
            current->invTexture.loadFromFile("images/sword2.png");
            current->invSprite.setTexture(current->invTexture);
            current->invSprite.setScale(0.08f, 0.08f);
            current->data = 40;
            current->category = "sword-2";
        }
        else if (cnt == 4) {          // portions 1
            current->invTexture.loadFromFile("images/orange.png");
            current->invSprite.setTexture(current->invTexture);
            current->invSprite.setScale(0.05f, 0.05f);
            current->data = 30;
            current->category = "portion-1";
        }
        else if (cnt == 5) {          // portions 2
            current->invTexture.loadFromFile("images/green.png");
            current->invSprite.setTexture(current->invTexture);
            current->invSprite.setScale(0.02f, 0.02f);
            current->data = 20;
            current->category = "portion-2";
        }
        else if (cnt == 6) {          // portions 3
            current->invTexture.loadFromFile("images/blue.png");
            current->invSprite.setTexture(current->invTexture);
            current->invSprite.setScale(0.03f, 0.03f);
            current->data = 10;
            current->category = "portion-3";
        }
    }

    void collectInventory(Player& player, Event& event) {
        invNode* current = head;
        int posX = player.getPositionX() / CELL_SIZE, posY = player.getPositionY() / CELL_SIZE;
        while (current) {
            if (inventoryCheck(posX, posY, current->getPositionX(), current->getPositionY(), event)) {
                addToPlayerInventory(current, player);
                removeObject(current->getPositionX(), current->getPositionY());
                return;
            }
            current = current->next;
        }
        display(player);
        /*cout << "Player--> x: " << (player.getPositionX() /CELL_SIZE) << " y: " << (player.getPositionY()/CELL_SIZE) << endl;
        invNode* temp = head;
        while (temp) {
            cout << "x: " << temp->getPositionX() << " y: " << temp->getPositionY() << endl;
            temp = temp->next;
        }
        cout << "count: " << objectCount << endl;
        for (int i = 0; i < objectCount; ++i) {
            cout << "objectPosition--> x: " << objectPositions[i].x << " y: " << objectPositions[i].y << endl;
        }*/
        return;
        /*for (int i = 0; i < objectCount; i++) {
            if (player.getPositionX() == getPositionX(i) && player.getPositionY() == getPositionY(i)) {
                removeObject(getPositionX(i), getPositionY(i));
            }
        }*/
    }
    bool inventoryCheck(int px, int py,int ix, int iy, Event& event) {
        if (event.key.code == sf::Keyboard::Up && py == iy && px == ix)
            return true;
        else if (event.key.code == sf::Keyboard::Down && py == iy && px == ix)
            return true;
        else if (event.key.code == sf::Keyboard::Right && py == iy && px == ix)
            return true;
        else if (event.key.code == sf::Keyboard::Left && py == iy && px == ix)
            return true;
        else
            return false;
    }

    void addToPlayerInventory(invNode* node, Player &player) {
        player.collectedItems.insertNode(player.collectedItems.root, node->data, node->category);
        player.score += node->data;
    }
    void display(Player& player) {
        cout << "Inventory On Maze: " << endl;
        invNode* temp = head;
        while (temp) {
            cout << "x: " << temp->getPositionX() << " y: " << temp->getPositionY() << endl;
            temp = temp->next;
        }
        cout << "count: " << objectCount << endl;
        cout << "Inventory with player: \n";
        player.collectedItems.inorderTraversal(player.collectedItems.root);
        cout << endl;
        return;
    }
};

#endif
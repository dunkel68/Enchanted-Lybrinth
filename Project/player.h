#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
//#include <vector>
#include <iostream>
#include "avl.h"
#include "inventory.h"
using namespace std;
using namespace sf;

class Player {
private:
    CircleShape shape;
    Vector2f position;
    int posX, posY;
    float radius;

public:
    AVL collectedItems;
    int score;

    Player(float radius) : radius(radius) {
        shape.setRadius(radius);
        shape.setFillColor(Color::Blue);
        posX = 0;
        posY = 0;
        score = 0;
    }

    void setPosition(Vector2f pos) {
        position = pos;
        shape.setPosition(position);
    }

    /*void setPosition(int x, int y) {
        setPositionX(x);
    }*/

    float getPositionX() const {
        return position.x;
    }

    float getPositionY() const {
        return position.y;
    }

    /*void setPositionX(int x) {
        posX = x;
    }

    void setPositionY(int y) {
        posY = y;
    }*/

    void move(float offsetX, float offsetY) {
        position.x += offsetX;
        position.y += offsetY;
        shape.setPosition(position);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    /*void AddToInventory(invNode* &node) {
        collectedItems.insertNode(collectedItems.root, node->data, node->category);
        score += node->data;
    }*/

};

#endif
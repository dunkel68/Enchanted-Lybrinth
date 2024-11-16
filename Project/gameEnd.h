/* Name : Fatima  (22i-1074) - C
            Umama (22i-2386) - C */

#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <SFML/Graphics/Color.hpp>
            //#include "game.h"

using namespace std;
using namespace sf;

class GameOver {
private:
    int i;
    int score;
    Text gameOverTxt[3];
    Font font;
public:

    // default constructor 
    GameOver() {

        i = 0;
        score = 0;

        if (!font.loadFromFile("fonts/arial.ttf")) {
            cout << "Error loading font!" << endl;                                      // handling font loading error here
        }

        // for pause window printing
        gameOverTxt[0].setFont(font);                                                                          // set font 
        gameOverTxt[0].setCharacterSize(35);                                                                   // set size of font 
        gameOverTxt[0].sf::Text::setFillColor(sf::Color::Red);
        gameOverTxt[0].setStyle(sf::Text::Bold);                                                               // bolding the text
        gameOverTxt[0].setString("      GAME OVER      ");                                                   // string to print
        gameOverTxt[0].setPosition(sf::Vector2f((1200 / 2) - 190, (800 / (3 + 1) * 1)));                     // position


        gameOverTxt[2].setFont(font);                                                                          // set font 
        gameOverTxt[2].setCharacterSize(35);                                                                   // set size of font 
        gameOverTxt[2].sf::Text::setFillColor(sf::Color::White);
        gameOverTxt[2].setStyle(sf::Text::Bold);                                                               // bolding the text
        gameOverTxt[2].setString(" EXIT ");                                                                   // string to print
        gameOverTxt[2].setPosition(sf::Vector2f((1200 / 2) - 70, (800 / (4 + 1) * 3)));                                // position
    }

    void Moveup();
    void moveDown();
    int GetPressedItem();
    void displayGameOverWindow(sf::RenderWindow& window, int);
    void DrawGameOver(sf::RenderWindow& window);
    virtual void printScores(sf::RenderWindow& window, int);
};



void GameOver::displayGameOverWindow(sf::RenderWindow& window, int score) {

    Sprite background;                              // pause screen background sprite
    Texture bg_texture;
    bg_texture.loadFromFile("img/GameOver2.jpg");      // image uploading background
    background.setTexture(bg_texture);


    //displaying pause screen here
    Clock clock;
    float timer = 0;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        sf::Event ee;

        while (window.pollEvent(ee)) {

            switch (ee.type) {
            case sf::Event::KeyReleased:
                switch (ee.key.code) {
                case sf::Keyboard::Up:
                    Moveup();
                    break;
                case sf::Keyboard::Down:
                    moveDown();
                    break;
                case sf::Keyboard::Return:
                    switch (GetPressedItem()) {

                    case 2:
                        window.close();                                         // exit game
                        break;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }


        }


        window.clear(Color::Black);
        window.draw(background);
        printScores(window, score);
        DrawGameOver(window);
        window.display();


    }


}


// cursor movement 
void GameOver::Moveup() {
    if (i - 1 >= 2) {
        gameOverTxt[i].sf::Text::setFillColor(sf::Color::White);                       // changing text color
        i--;
        gameOverTxt[i].sf::Text::setFillColor(sf::Color::Red);

    }
}
void GameOver::moveDown() {
    if (i + 1 <= 3) {
        gameOverTxt[i].sf::Text::setFillColor(sf::Color::White);
        i++;
        gameOverTxt[i].sf::Text::setFillColor(sf::Color::Red);

    }
}

int GameOver::GetPressedItem() {                          // getting key
    return i;
}

void GameOver::DrawGameOver(sf::RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        window.draw(gameOverTxt[i]);
    }
}

void GameOver::printScores(sf::RenderWindow& window, int scores) {

    gameOverTxt[1].setFont(font);                                                                          // set font 
    gameOverTxt[1].setCharacterSize(35);                                                                   // set size of font 
    gameOverTxt[1].sf::Text::setFillColor(sf::Color::White);
    gameOverTxt[1].setStyle(sf::Text::Bold);                                                               // bolding the text
    std::stringstream ss2;                                                                            // #include <sstream>
    ss2 << scores;
    gameOverTxt[1].setString(ss2.str().c_str());
    gameOverTxt[1].setPosition(sf::Vector2f((1200 / 2) - 60, (800 / 4 + 1) * 2));                        // position
    window.draw(gameOverTxt[1]);

}
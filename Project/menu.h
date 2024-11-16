#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/System.hpp"
#include "game.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;


class HihestScores {
public:
    HihestScores();                                         // Construc
    void addScore(int score);
    const int* getHighScores() const;

    // file handling here 
    void saveScoresToFile(const char* fileName) const;
    void loadScoresFromFile(const char* fileName);
    size_t getMaxScores() const;

    Sprite background;                                      // high scores background sprite
    Texture bg_texture;
private:
    const int maxScores = 5;
    int scores[5];
    void sortScores();
};


HihestScores::HihestScores() {
    loadScoresFromFile("scores.txt");
}

void HihestScores::addScore(int score) {                    // adding scores 

    scores[maxScores - 1] = score;
    sortScores();                                           // sorting 
    saveScoresToFile("scores.txt");                         // finally saving
}

// sorting ftn decreasing order
void HihestScores::sortScores() {
    for (int i = 0; i < maxScores - 1; ++i) {
        for (int j = 0; j < maxScores - i - 1; ++j) {
            if (scores[j] < scores[j + 1]) {
                //swaping
                int temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }
}

const int* HihestScores::getHighScores() const {
    return scores;                                                              // getter
}

void HihestScores::saveScoresToFile(const char* fileName) const {               // saving scores ftn 
    std::ofstream file(fileName);

    if (file.is_open()) {
        for (size_t i = 0; i < maxScores; ++i) {
            file << scores[i] << '\n';
        }

        file.close();
    }
    else {
        cout << "Error in opening file" << endl;
    }
}

void HihestScores::loadScoresFromFile(const char* fileName) {               // loading scores 
    std::ifstream file(fileName);

    if (file.is_open()) {
        for (size_t i = 0; i < maxScores; ++i) {
            file >> scores[i];
        }

        file.close();
    }
    else {
        std::cout << "Error in opening file" << std::endl;
    }
}

size_t HihestScores::getMaxScores() const {                                     // max score getter 
    return maxScores;
}


class Menu {
private:
    int IndexItem;
    const int MaxItem = 5;
    const int Helpindex = 10;
    Font font;
    Text menu[5];                   // 5 menu items 
    Text help[10];                  // 10 help items 
    bool GameNew;
public:

    //add menu attributes here


    Menu(float width, float height)
    {
        IndexItem = 0;
        GameNew = false;
        //constructors body
        if (!font.loadFromFile("fonts/arial.ttf")) {
            cout << "Error loading font!" << endl;
        }

        // for main menu window printing
        menu[0].setFont(font);                                                                          // set font 
        menu[0].setCharacterSize(40);                                                                   // set size of font 
        menu[0].sf::Text::setFillColor(sf::Color::Red);
        menu[0].setStyle(sf::Text::Bold);                                                               // bolding the text
        menu[0].setString("NEW GAME");                                                          // string to print
        menu[0].setPosition(sf::Vector2f((width / 2) - 120, height / (MaxItem + 1) * 1));               // position

        menu[1].setFont(font);
        menu[1].setCharacterSize(35);
        menu[1].sf::Text::setFillColor(sf::Color::White);
        menu[1].setStyle(sf::Text::Bold);
        menu[1].setString("HIGHEST SCORE");
        menu[1].setPosition(sf::Vector2f((width / 2) - 150, height / (MaxItem + 1) * 2));

        menu[2].setFont(font);
        menu[2].setCharacterSize(35);
        menu[2].sf::Text::setFillColor(sf::Color::White);
        menu[2].setStyle(sf::Text::Bold);
        menu[2].setString("HELP");
        menu[2].setPosition(sf::Vector2f((width / 2) - 60, height / (MaxItem + 1) * 3));

        menu[3].setFont(font);
        menu[3].setCharacterSize(35);
        menu[3].sf::Text::setFillColor(sf::Color::White);
        menu[3].setStyle(sf::Text::Bold);
        menu[3].setString("EXIT");
        menu[3].setPosition(sf::Vector2f((width / 2) - 60, height / (MaxItem + 1) * 4));

        menu[4].setFont(font);
        menu[4].setCharacterSize(35);
        menu[4].sf::Text::setFillColor(sf::Color::White);
        menu[4].setStyle(sf::Text::Bold);
        menu[4].setString("CONTINUE");
        menu[4].setPosition(sf::Vector2f((width / 2) - 75, height / (MaxItem + 1) * 5));


        // for help window string printing
        help[1].setFont(font);                                                                                  // set font
        help[1].setCharacterSize(25);                                                                           // set size of font
        help[1].sf::Text::setFillColor(sf::Color::White);                                                       // set color
        help[1].setStyle(sf::Text::Bold);                                                                       // bolding the text
        help[1].setString("* Navigate the Enchanted Labyrinth to find treasures");                                                       // string to print
        help[1].setPosition(sf::Vector2f((width / 2) - 400, (height / (Helpindex + 1) * 3) - 15));              // position

        help[2].setFont(font);
        help[2].setCharacterSize(25);
        help[2].sf::Text::setFillColor(sf::Color::White);
        help[2].setStyle(sf::Text::Bold);
        help[2].setString("* Use arrow keys for movement, spacebar to interact");
        help[2].setPosition(sf::Vector2f((width / 2) - 400, (height / (Helpindex + 1) * 4) - 15));

        help[3].setFont(font);
        help[3].setCharacterSize(25);
        help[3].sf::Text::setFillColor(sf::Color::White);
        help[3].setStyle(sf::Text::Bold);
        help[3].setString("* Collect items, solve puzzles, manage health");
        help[3].setPosition(sf::Vector2f((width / 2) - 400, (height / (Helpindex + 1) * 5) - 15));

        help[4].setFont(font);
        help[4].setCharacterSize(25);
        help[4].sf::Text::setFillColor(sf::Color::White);
        help[4].setStyle(sf::Text::Bold);
        help[4].setString("* Explore thoroughly, manage inventory wisely, stay observant");
        help[4].setPosition(sf::Vector2f((width / 2) - 400, (height / (Helpindex + 1) * 6) - 15));

        help[5].setFont(font);
        help[5].setCharacterSize(25);
        help[5].sf::Text::setFillColor(sf::Color::White);
        help[5].setStyle(sf::Text::Bold);
        help[5].setString("* Press H to get help");
        help[5].setPosition(sf::Vector2f((width / 2) - 400, (height / (Helpindex + 1) * 7) - 15));

        help[6].setFont(font);
        help[6].setCharacterSize(25);
        help[6].sf::Text::setFillColor(sf::Color::White);
        help[6].setStyle(sf::Text::Bold);
        help[6].setString("Good Luck!!!");
        help[6].setPosition(sf::Vector2f((width / 2) - 200, (height / (Helpindex + 1) * 8) - 15));

    }



    void display_menu(sf::RenderWindow& window) {
        Sprite background;                          // high scores background sprite
        Texture bg_texture;
        bg_texture.loadFromFile("bg2.jpeg");      // image uploading background
        background.setTexture(bg_texture);

        //display menu screen here

        Game* g = new Game;

        while (window.isOpen()) {

            sf::Event event;

            while (window.pollEvent(event)) {

                switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                    case sf::Keyboard::Up:
                        Moveup();
                        break;
                    case sf::Keyboard::Down:
                        moveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (GetPressedItem()) {
                        case 0:
                            // cout << "Play button has been pressed " << endl;
                            if (GameNew = true) {
                                g = new Game;
                            }

                            g->start_game();                                     // game start
                            break;

                        case 1:
                            displayHighScores(SCORE);
                            break;
                        case 2:
                            helpMsg();
                            break;

                        case 3:
                            window.close();                                                     // exit 
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

            // window.clear(Color::Black);
            DrawM1(window);
            window.display();

        }


    }

    // drwing menus 
    void DrawM1(sf::RenderWindow& window) {
        for (int i = 0; i < MaxItem - 1; i++) {
            window.draw(menu[i]);
        }
    }

    void DrawM2(sf::RenderWindow& window) {
        for (int i = 0; i < MaxItem; i++) {
            window.draw(menu[i]);
        }
    }

    void helpMsg() {
        RenderWindow helpWind(VideoMode(1200, 800), "HELP");                     // making help window

        Sprite background2;                          // high scores background sprite
        Texture bg_texture;
        bg_texture.loadFromFile("bg2.jpeg");      // image uploading background
        background2.setTexture(bg_texture);
        Event e;

        while (helpWind.isOpen()) {

            while (helpWind.pollEvent(e))
            {
                if ((e.type == Event::Closed) || (e.type == Event::TextEntered)) {
                    helpWind.close();
                    break;
                }
            }
            helpWind.clear(Color::Black);
            helpWind.draw(background2);

            for (int i = 0; i < Helpindex - 1; i++) {
                helpWind.draw(help[i]);                                             // drawing help window 
            }
            helpWind.display();
        }
    }



    // cursor movement 
    void Moveup() {
        if (IndexItem - 1 >= 0) {
            menu[IndexItem].sf::Text::setFillColor(sf::Color::White);                       // changing text color
            IndexItem--;
            menu[IndexItem].sf::Text::setFillColor(sf::Color::Red);

        }
    }
    void moveDown() {
        if (IndexItem + 1 <= MaxItem) {
            menu[IndexItem].sf::Text::setFillColor(sf::Color::White);
            IndexItem++;
            menu[IndexItem].sf::Text::setFillColor(sf::Color::Red);

        }
    }

    int GetPressedItem() {                          // getting key
        return IndexItem;
    }

    void displayHighScores(int scores) {
        Sprite background;                          // high scores background sprite
        Texture bg_texture;
        bg_texture.loadFromFile("bg2.jpeg");      // image uploading background
        background.setTexture(bg_texture);

        HihestScores HS;
        HS.addScore(scores);
        const int* highScores = HS.getHighScores();

        if (*highScores < scores) {
            HS.addScore(scores);                        // adding scores here 
        }

        sf::RenderWindow highScoresWindow(sf::VideoMode(1200, 800), "High Scores");

        highScoresWindow.clear(Color::Black);
        highScoresWindow.draw(background);

        sf::Font font;
        font.loadFromFile("fonts/arial.ttf");                 // font 

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);

        // Display high scores
        for (int i = 0; i < 5; ++i) {
            text.setString("Score " + std::to_string(i + 1) + ": " + std::to_string(highScores[i]));
            text.setPosition(250, 50 + i * 30);
            highScoresWindow.draw(text);
        }

        highScoresWindow.display();

        sf::Event event;
        while (highScoresWindow.isOpen()) {
            while (highScoresWindow.pollEvent(event)) {
                if ((event.type == sf::Event::Closed) || (event.type == sf::Event::TextEntered)) {
                    highScoresWindow.close();
                }
            }
        }
    }


};



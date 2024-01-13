#include <SFML/Graphics.hpp>
#include"tetrimino.h";
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;
int main() {
    int highestScore = 0;
    ifstream file("highest_score.txt");
    if (file.is_open()) {
        file >> highestScore;
        file.close();
    }
  


    //gamestarting.
    RenderWindow window(VideoMode(600, 800), "Tetris Game");
  
    Gameboard gameBoard;
    tetrimino* Ctetrimino = new LShape(4, 0);
    Font name;
    RectangleShape Box(Vector2f(200, 150));
    name.loadFromFile("ARLRDBD.ttf");
   
   Box.setPosition(320, 100);
   Box.setFillColor(sf::Color::Black);
        Box.setOutlineThickness(3);
    Box.setOutlineColor(sf::Color::Yellow);
        RectangleShape BoxScore(Vector2f(200, 100));
        BoxScore.setPosition(320, 270);
        BoxScore.setFillColor(sf::Color::Black);
        BoxScore.setOutlineThickness(3);
        BoxScore.setOutlineColor(sf::Color::Magenta);
        RectangleShape BoxLines(Vector2f(200, 100));
        BoxLines.setPosition(320, 400);
        BoxLines.setFillColor(sf::Color::Black);
        BoxLines.setOutlineThickness(3);
        BoxLines.setOutlineColor(sf::Color::Red);
        RectangleShape BoxL(Vector2f(200, 100));
        BoxL.setPosition(320, 550);
        BoxL.setFillColor(sf::Color::Black);
        BoxL.setOutlineThickness(3);
        BoxL.setOutlineColor(sf::Color::Cyan);
        Font lines;
        lines.loadFromFile("ARLRDBD.ttf");
        Text line;
        line.setFont(lines);
        line.setCharacterSize(30);
       line.setFillColor(sf::Color::White);
       line.setPosition(330, 410);
       Text level;
       level.setFont(name);
       level.setCharacterSize(24);
       level.setFillColor(sf::Color::White);
       level.setPosition(330, 560);
    Text text;
    text.setFont(name);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(330, 160);
    Text name2;
   name2.setFont(name);
    name2.setCharacterSize(24);
    name2.setFillColor(sf::Color::White);
    name2.setPosition(330, 110);
   name2.setString("Player Name " );
    Font scoreg;
    scoreg.loadFromFile("ARLRDBD.ttf");
    Text scoreText;
    scoreText.setFont(scoreg);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(330, 280);
    RectangleShape BoxHighscore(Vector2f(250, 100));
    BoxHighscore.setPosition(320, 680);
    BoxHighscore.setFillColor(sf::Color::Black);
    BoxHighscore.setOutlineThickness(3);
    BoxHighscore.setOutlineColor(sf::Color::Magenta);
    Text high;
    high.setFont(lines);
    high.setCharacterSize(30);
    high.setFillColor(sf::Color::White);
    high.setPosition(330, 690);

   

    int score = 0;
    int l = 0;
    int levelg = 1;
    line.setString("Lines: " + std::to_string(l));
    scoreText.setString("Score: " + std::to_string(score));
    level.setString("Level# " + std::to_string(levelg));
    if (file.is_open()) {
        file >> highestScore;
        file.close();
    }
    high.setString("HighSco: " + std::to_string(highestScore));

    cout << "Game start" << endl;

    Clock clock;
    bool gameOver = false;
    float speed = 0.9f;
    float initialFallTime = 1.0f; // Initial fall time for level 1
    float fallTime = initialFallTime;
    while (window.isOpen() && !gameOver)
    {
        //Events
        Event event;

        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed) {
                window.close();
            }
           
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    text.setString(text.getString() + static_cast<char>(event.text.unicode));
                }
            }

                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Left) {
                        Ctetrimino->moveLeft();
                        if (Ctetrimino->IsColliding(Ctetrimino->x, Ctetrimino->y, 0, gameBoard.board)) { Ctetrimino->moveRight(); }
                    }

                    else if (event.key.code == sf::Keyboard::Right) {
                        Ctetrimino->moveRight();
                        if (Ctetrimino->IsColliding(Ctetrimino->x, Ctetrimino->y, 0, gameBoard.board)) { Ctetrimino->moveLeft(); }
                    }

                    else if (event.key.code == sf::Keyboard::Up) {
                        Ctetrimino->rotate(gameBoard.board);
                    }

                    else if (event.key.code == sf::Keyboard::Down) {
                        Ctetrimino->moveDown();
                        if (Ctetrimino->IsColliding(Ctetrimino->x, Ctetrimino->y, 0, gameBoard.board)) {
                            score=placeTetrimino(Ctetrimino, window, gameBoard, score,l);
                            
                            scoreText.setString("Score: " + std::to_string(score));

                            line.setString("Lines: " + std::to_string(l));
                            Ctetrimino = getNew(window);
                            
                            if (score > 1000 )
                            {
                               
                                    fallTime *= speed;
                                    levelg++;
                                    level.setString("Level#" + std::to_string(levelg));
                                    speed = 0;
                                
                                clock.restart();
                                speed = 0;
                            }
                            
                            if (Ctetrimino->IsColliding(Ctetrimino->x, Ctetrimino->y, 0, gameBoard.board)) {
                                gameOver = true;
                            }

                        }
                    }
                }
        }
            window.clear();
            Time elapsed = clock.getElapsedTime();
            if (elapsed.asSeconds() >= fallTime)
            {
                if (Ctetrimino->moveDown(gameBoard.board)) {
                    score=placeTetrimino(Ctetrimino, window, gameBoard, score,l);
                    scoreText.setString("Score: " + std::to_string(score));
                    line.setString("Lines: " + std::to_string(l));

                    if (score > 1000)
                    {

                        fallTime *= speed;
                        levelg++;
                        level.setString("Level#" + std::to_string(levelg));
                        speed = 0;

                        clock.restart();
                        speed = 0;
                    }
                  
                    
                    Ctetrimino = getNew(window);
                    if (Ctetrimino->IsColliding(Ctetrimino->x, Ctetrimino->y, 0, gameBoard.board)) {
                        gameOver = true;
                    }
                  
                }

                clock.restart();
            }
            gameBoard.drawBoard(window);
            Ctetrimino->draw(window);
            window.draw(Box);
            window.draw(text);
            window.draw(BoxScore);
            window.draw(scoreText);
            window.draw(BoxLines);
            window.draw(line);
            window.draw(name2);
            window.draw(BoxHighscore);
            window.draw(high);
            
            window.draw(BoxL);
            window.draw(level);
            if (score > highestScore) {
                ofstream outputFile("highest_score.txt");
                if (outputFile.is_open()) {
                    outputFile << score;
                    outputFile.close();
                }
            }

            //Render UI
            window.display();
     }
     delete[]Ctetrimino;
        return 0;

    }
    

  
    



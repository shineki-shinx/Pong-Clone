/*
 * Copyright 2024 Abrar Fahim <adibabrarfahim@gmail.com>
 * All rights reserved.
 */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void game() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
  sf::CircleShape gameball(20.0f);
  sf::Vector2f Velocity;
  sf::Clock clock;
  Velocity.x = -3.5f;
  Velocity.y = 3.5f;
  gameball.setFillColor(sf::Color::Red);
  const float MaxSpeed = 150.0f;
  int Score = 0;
  bool running = false;
  // Player Attributes
  sf::RectangleShape player1;
  player1.setSize(sf::Vector2f(20, 100));
  player1.setPosition(sf::Vector2f(10, 0));
  player1.setFillColor(sf::Color::White);

  sf::RectangleShape player2;
  player2.setSize(sf::Vector2f(20, 100));
  player2.setPosition(sf::Vector2f(770, 10));
  player2.setFillColor(sf::Color::White);

  sf::RectangleShape line;
  line.setSize(sf::Vector2f(800, 5));
  line.rotate(90);
  line.setPosition(400, 0);
  line.setFillColor(sf::Color::White);

  sf::Font font;
  if (!font.loadFromFile("ARCADECLASSIC.TTF")) {
    std::cout << "Error loading font\n";
  }

  sf::Text text;
  text.setFont(font);
  text.setString("Pong  Clone");
  text.setFillColor(sf::Color::White);
  text.setStyle(sf::Text::Bold);
  text.setPosition(sf::Vector2f(250, 10));
  text.setCharacterSize(50);

  sf::Text ScoreBoard;
  ScoreBoard.setFont(font);
  ScoreBoard.setFillColor(sf::Color::White);
  ScoreBoard.setPosition(sf::Vector2f(80, 10));
  ScoreBoard.setString('0');
  ScoreBoard.setCharacterSize(60);

  sf::Text retry;
  retry.setFont(font);
  retry.setFillColor(sf::Color::White);
  retry.setCharacterSize(40);
  retry.setPosition(100,400);
  retry.setString("Press  Space  to  start! Smiley<3");

  sf::SoundBuffer ballBuffer;
  if (!ballBuffer.loadFromFile("ball.wav")) {
    std::cout << "Error loading file" << std::endl;
  }
  sf::Sound ballSound;
  ballSound.setBuffer(ballBuffer);

  while (window.isOpen()) {

    int playervel = 0;
    bool collides =
        player1.getGlobalBounds().intersects(gameball.getGlobalBounds());
    bool second_player_collision =
        player2.getGlobalBounds().intersects(gameball.getGlobalBounds());
    float delta = clock.restart().asSeconds();
    sf::Event event;
    window.setFramerateLimit(75u);
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    if (event.type == sf::Event::KeyPressed) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        playervel = -40;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        playervel = 40;
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      running = true;
    }
    if (gameball.getPosition().x < 9.0f) {
      gameball.setPosition(sf::Vector2f(400, 200));
      running = false;
    }
    if (gameball.getPosition().y < 0.0f) {
      gameball.setPosition(gameball.getPosition().x, 0.0f);
      Velocity.y *= -1;
    }
    if (gameball.getPosition().y + gameball.getGlobalBounds().height > 600.0f) {
      gameball.setPosition(gameball.getPosition().x,
                           (600.0f - Velocity.y) -
                               gameball.getGlobalBounds().height);
      Velocity.y *= -1;
    }
    if (player1.getPosition().y < 10.0f) {
      player1.setPosition(10, 0.0f);
    }
    if (player1.getPosition().y + player1.getGlobalBounds().height > 600.0f) {
      player1.setPosition(10, (600.0f + playervel) -
                                  player1.getGlobalBounds().height);
    }
    if (player2.getPosition().y < 0.0f) {
      player2.setPosition(770, 0.0f);
    }
    if (player2.getPosition().y + player2.getGlobalBounds().height > 600.0f) {
      player2.setPosition(770, (600.0f + playervel) -
                                   player2.getGlobalBounds().height);
    }
    if (collides) {
      if(Velocity.x < 0) Velocity.x = Velocity.x - Score/3;
      else Velocity.x += Score/3;

      Velocity.x *= -1;
      Score++;
      ballSound.play();
    }
    if (second_player_collision) {
      Velocity.x *= -1;
      ballSound.play();
    }
    player2.setPosition(770 /* the second players x axis*/,
                        gameball.getPosition().y);
    player1.move(0, playervel);
    ScoreBoard.setString(std::to_string(Score));
    window.clear();
    if (running) {
      window.draw(line);
      gameball.move(Velocity); // making the ball move
      window.draw(ScoreBoard);
    }
    window.draw(gameball);
    if (!running){
      window.draw(text);
      window.draw(retry);
      Score = 0;
    }
    window.draw(player1);
    window.draw(player2);
    window.display();
  }
}

int main() { game(); }

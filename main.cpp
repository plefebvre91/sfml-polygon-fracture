/* MIT License

Copyright (c) 2022 Pierre Lefebvre

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */


#include <SFML/Graphics.hpp>
#include "fracturable.hpp"

int main() {
  // Create the main window
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML window", sf::Style::Default, settings);
  window.setFramerateLimit(30);

  sf::ConvexShape convexes[3];
  convexes[0].setPointCount(5);
  convexes[0].setPosition(sf::Vector2f(400.0, 200.0));
  convexes[0].setPoint(0, sf::Vector2f(10.f, 10.f));
  convexes[0].setPoint(1, sf::Vector2f(150.f, 10.f));
  convexes[0].setPoint(2, sf::Vector2f(120.f, 90.f));
  convexes[0].setPoint(3, sf::Vector2f(30.f, 100.f));
  convexes[0].setPoint(4, sf::Vector2f(10.f, 50.f));
  convexes[0].setFillColor(sf::Color(200, 200, 0));
  convexes[0].setOutlineThickness(3.0);
  convexes[0].setOutlineColor(sf::Color(100, 100, 0));

  convexes[1].setPointCount(3);
  convexes[1].setPosition(sf::Vector2f(600.0, 100.0));
  convexes[1].setPoint(0, sf::Vector2f(300.f, 10.f));
  convexes[1].setPoint(1, sf::Vector2f(150.f, 100.f));
  convexes[1].setPoint(2, sf::Vector2f(320.f, 90.f));
  convexes[1].setFillColor(sf::Color(0, 200, 0));
  convexes[1].setOutlineThickness(3.0);
  convexes[1].setOutlineColor(sf::Color(0, 100, 0));


  convexes[2].setPointCount(4);
  convexes[2].setPosition(sf::Vector2f(100.0, 200.0));
  convexes[2].setPoint(0, sf::Vector2f(40.f, 250.f));
  convexes[2].setPoint(1, sf::Vector2f(250.f, 400.f));
  convexes[2].setPoint(2, sf::Vector2f(200.f, 90.f));
  convexes[2].setPoint(3, sf::Vector2f(10.f, 100.f));
  convexes[2].setFillColor(sf::Color(0, 0, 200));
  convexes[2].setOutlineThickness(3.0);
  convexes[2].setOutlineColor(sf::Color(0, 0, 100));

  FracturableShape yellow(convexes[0]);
  FracturableShape red(convexes[1]);
  FracturableShape blue(convexes[2]);

  sf::Clock clock;

  // Start the game loop
  while (window.isOpen())
  {
    sf::Time dt = clock.restart();

    // Process events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
          yellow.fracture();
          red.fracture();
          blue.fracture();
        }
      }
    }

    // Clear screen
    window.clear();

    // Draw shapes
    yellow.draw(window);
    red.draw(window);
    blue.draw(window);

    // Updates sprites
    yellow.update(dt.asSeconds());
    red.update(dt.asSeconds());
    blue.update(dt.asSeconds());

    // Update the window
    window.display();
  }
  return EXIT_SUCCESS;
}

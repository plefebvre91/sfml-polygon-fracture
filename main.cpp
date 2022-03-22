
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include "utils.hpp"

class FracturableShape {
public:
  FracturableShape(const sf::ConvexShape& shape): _fragments(), _points(), _directions(), _center(), fractured(false) {
    std::size_t nbPoints = shape.getPointCount();
    sf::Vector2f position = shape.getPosition();
    _original = shape;

    for(std::size_t i=0; i<nbPoints; i++) {
      _fragments.push_back(sf::ConvexShape());
      _points.push_back(shape.getPoint(i));
    }

    _center = utils::getCenter(_points);
    _center += position;

    for(auto& fragment: _fragments) {
      fragment.setPointCount(3);
      fragment.setPoint(0, _center);
      fragment.setFillColor(shape.getFillColor());
      fragment.setOutlineThickness(shape.getOutlineThickness());
      fragment.setOutlineColor(shape.getOutlineColor());
    }


    for(std::size_t i=1; i<nbPoints; i++) {
      _fragments[i-1].setPoint(1, _points[i-1] + position);
      _fragments[i-1].setPoint(2, _points[i] + position);
    }
    _fragments.back().setPoint(1, _points.back() + position);
    _fragments.back().setPoint(2, _points[0] + position);

    for(std::size_t i=0; i<_fragments.size(); i++) {
      sf::Vector2f center = utils::getCenter(_fragments[i]);
      _directions.push_back(utils::nv(center, _center));
    }
  }

  void update(float delta) {
    if (!fractured)
      return;

    for(std::size_t i=0; i<_fragments.size(); i++)
      _fragments[i].move(_directions[i]*delta*100.0f);
  }

  void fracture() {
    fractured = true;
  }

  void draw(sf::RenderWindow& window) {
    if (!fractured)
      window.draw(_original);
    else for(auto& fragment: _fragments)
      window.draw(fragment);
  }

private:
  sf::ConvexShape _original;
  std::vector<sf::ConvexShape> _fragments;
  std::vector<sf::Vector2f> _points;
  std::vector<sf::Vector2f> _directions;
  sf::Vector2f _center;
  bool fractured;

};

int main() {
  // Create the main window
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML window", sf::Style::Default, settings);

  window.setFramerateLimit(30);
  sf::Clock clock;

  // create an empty shape
  sf::ConvexShape convex[3];
  convex[0].setPointCount(5);
  convex[0].setPosition(sf::Vector2f(400.0, 200.0));
  convex[0].setPoint(0, sf::Vector2f(0.f, 0.f));
  convex[0].setPoint(1, sf::Vector2f(150.f, 10.f));
  convex[0].setPoint(2, sf::Vector2f(120.f, 90.f));
  convex[0].setPoint(3, sf::Vector2f(30.f, 100.f));
  convex[0].setPoint(4, sf::Vector2f(0.f, 50.f));
  convex[0].setFillColor(sf::Color(200, 200, 0));
  convex[0].setOutlineThickness(3.0);
  convex[0].setOutlineColor(sf::Color(100, 100, 0));

  convex[1].setPointCount(3);
  convex[1].setPosition(sf::Vector2f(600.0, 100.0));
  convex[1].setPoint(0, sf::Vector2f(300.f, 0.f));
  convex[1].setPoint(1, sf::Vector2f(150.f, 100.f));
  convex[1].setPoint(2, sf::Vector2f(320.f, 90.f));
  convex[1].setFillColor(sf::Color(0, 200, 0));
  convex[1].setOutlineThickness(3.0);
  convex[1].setOutlineColor(sf::Color(0, 100, 0));


  convex[2].setPointCount(4);
  convex[2].setPosition(sf::Vector2f(100.0, 200.0));
  convex[2].setPoint(0, sf::Vector2f(40.f, 250.f));
  convex[2].setPoint(1, sf::Vector2f(250.f, 400.f));
  convex[2].setPoint(2, sf::Vector2f(200.f, 90.f));
  convex[2].setPoint(3, sf::Vector2f(10.f, 100.f));
  convex[2].setFillColor(sf::Color(0, 0, 200));
  convex[2].setOutlineThickness(3.0);
  convex[2].setOutlineColor(sf::Color(0, 0, 100));

  FracturableShape s(convex[0]);
  FracturableShape s1(convex[1]);
  FracturableShape s2(convex[2]);

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
          s.fracture();
          s1.fracture();
          s2.fracture();
        }
      }
    }

    // Clear screen
    window.clear();

    s.draw(window);
    s1.draw(window);
    s2.draw(window);

    // Updates sprites
    s.update(dt.asSeconds());
    s1.update(dt.asSeconds());
    s2.update(dt.asSeconds());

    // Update the window
    window.display();
  }
  return EXIT_SUCCESS;
}

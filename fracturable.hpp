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


#ifndef FRACTURABLE_HPP
#define FRACTURABLE_HPP

#include <SFML/Graphics.hpp>

#define SPEED 100.0f

class FracturableShape {
public:
  /**
   * Constructor
   * @param the parent shape
   */
  FracturableShape(const sf::ConvexShape& shape);

  /**
   * Update shape movement (called at each frame)
   * @param ellapsed time since last update
   */
  void update(float delta);

  /**
   * Split the shape
   */
  void fracture();

  /**
   * Draw the shape
   * @param SFML window
   */
  void draw(sf::RenderWindow& window);

private:
  sf::ConvexShape _original;
  std::vector<sf::ConvexShape> _fragments;
  std::vector<sf::Vector2f> _points;
  std::vector<sf::Vector2f> _directions;
  sf::Vector2f _center;
  bool _fractured;
};

#endif

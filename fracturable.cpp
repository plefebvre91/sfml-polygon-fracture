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


#include "fracturable.hpp"
#include "utils.hpp"

FracturableShape::FracturableShape(const sf::ConvexShape& shape):
    _fragments(), _points(), _directions(), _center(), _fractured(false) {

  // Store original shape and retrieve its geometry properties
  std::size_t nbPoints = shape.getPointCount();
  sf::Vector2f position = shape.getPosition();
  _original = shape;

  // Store the shape points in a vector, and create empty fragments
  for(std::size_t i=0; i<nbPoints; i++) {
    _points.push_back(shape.getPoint(i));

    sf::ConvexShape fragment;
    fragment.setPointCount(3);
    fragment.setFillColor(_original.getFillColor());
    fragment.setOutlineThickness(_original.getOutlineThickness());
    fragment.setOutlineColor(_original.getOutlineColor());

    _fragments.push_back(fragment);
  }

  // Compute its center position
  _center = utils::getCenter(_points);
  _center += position;

  // Create the first N-1 fragments points...
  for(std::size_t i=1; i<nbPoints; i++) {
    _fragments[i-1].setPoint(0, _center);
    _fragments[i-1].setPoint(1, _points[i-1] + position);
    _fragments[i-1].setPoint(2, _points[i] + position);
  }

  // ... and the last one
  _fragments.back().setPoint(0, _center);
  _fragments.back().setPoint(1, _points.back() + position);
  _fragments.back().setPoint(2, _points.front() + position);

  // Compute direction for each fragment
  for(std::size_t i=0; i<_fragments.size(); i++) {
    sf::Vector2f center = utils::getCenter(_fragments[i]);
    _directions.push_back(utils::nv(center, _center));
  }
}

void FracturableShape::update(float delta) {
  // Nothing to do if shape is not fractured
  if (!_fractured)
    return;

  // Move the fragment along its direction vector
  for(std::size_t i=0; i<_fragments.size(); i++)
    _fragments[i].move(_directions[i]*delta*SPEED);
}

void FracturableShape::fracture() {
  _fractured = true;
}

void FracturableShape::draw(sf::RenderWindow& window) {
  // Draw the original form...
  if (!_fractured)
    window.draw(_original);
  // ... or the fragments if it has been fractured
  else for(auto& fragment: _fragments)
    window.draw(fragment);
}

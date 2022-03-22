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


#include <numeric>
#include <cmath>
#include <execution>
#include "utils.hpp"

namespace utils {
  float sd(const sf::Vector2f& a, const sf::Vector2f& b) {
    auto x = a.x - b.x;
    auto y = a.y - b.y;
    return x*x + y*y;
  }

  // Build vecotr from 2 points
  sf::Vector2f v(const sf::Vector2f& a, const sf::Vector2f& b) {
    return b - a;
  }

  // Build a normalize vector
  sf::Vector2f nv(const sf::Vector2f& a, const sf::Vector2f& b) {
    auto u = v(b,a);
    auto n = std::hypotf(u.x, u.y);

    return u/n;
  }

  // Get isobarycenter from a set of points
  sf::Vector2f getCenter(const std::vector<sf::Vector2f>& points) {

    // Sum points coordinates
    sf::Vector2f center = std::reduce(points.begin(), points.end(), sf::Vector2f(0,0));

    // Get the mean coordinate
    center /= (float)points.size();

    return center;
  }

  // Get isobarycenter from a shape
  sf::Vector2f getCenter(const sf::ConvexShape& shape) {
    std::vector<sf::Vector2f> points;

    for(std::size_t i=0; i<shape.getPointCount(); i++)
      points.push_back(shape.getPoint(i));

    return getCenter(points);
  }
}

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

  sf::Vector2f getCenter(const std::vector<sf::Vector2f>& points) {
    sf::Vector2f center = std::reduce(points.begin(), points.end(), sf::Vector2f(0,0));
    center /= (float)points.size();
    return center;
  }

  sf::Vector2f getCenter(const sf::ConvexShape& shape) {
    std::vector<sf::Vector2f> points;

    for(std::size_t i=0; i<shape.getPointCount(); i++) {
      points.push_back(shape.getPoint(i));
    }

    return getCenter(points);
  }
}

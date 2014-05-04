#ifndef LIFEBAR_H_
#define LIFEBAR_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

class LifeBar {
private:
  bool	_d;
  sf::RectangleShape _bar;
public:
  LifeBar(int, bool);
  void Set(int);
  void SetColor(sf::Color);
  const sf::RectangleShape& Get();
};

#endif

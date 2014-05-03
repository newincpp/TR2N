#ifndef LIFEBAR_H_
#define LIFEBAR_H_

#include <SFML/Graphics.hpp>

class LifeBar {
private:
  bool	_d;
  sf::RectangleShape _bar;
public:
  LifeBar(int, bool);
  void Set(int);
  const sf::RectangleShape& Get();
};

#endif

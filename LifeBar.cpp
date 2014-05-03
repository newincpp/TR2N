#include "LifeBar.hpp"

void	LifeBar::Set(int size)
{
  _bar.setSize(sf::Vector2f(size * 8, 20));
  if (_d)
    _bar.setSize(sf::Vector2f(size * -8, 20));
}

const sf::RectangleShape& LifeBar::Get()
{
  return (_bar);
}

LifeBar::LifeBar(int pos, bool sens) : _d(sens)
{
    _bar.setFillColor(sf::Color::Transparent);
    _bar.setOutlineColor(sf::Color::Red);
    _bar.setOutlineThickness(5);
    _bar.setPosition(pos, 20);
}

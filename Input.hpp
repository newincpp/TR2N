#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Attack.hpp"
#include "Player.hpp"

class Input {
private:
  std::string	_move;
  unsigned int	_i;
  inline char mask(char a)
  {
    if (a == '2')
      return (1);
    if (a == '4')
      return (2);
    if (a == '6')
      return (4);
    if (a == '8')
      return (8);
    return (0);
  }
  inline char	_keyPressed() {
    char	lol;
    
    lol = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
      lol |= mask('2');
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
      lol |= mask('4');
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
      lol |= mask('6');
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
      lol |= mask('8');
    return(lol);
  }
public:
  Input(std::string);
  bool check(); 
};

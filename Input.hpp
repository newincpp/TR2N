#ifndef INPUT_H_
#define INPUT_H_

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>

class Input {
private:
  std::string	_move;
  unsigned int	_i;
  unsigned int  _f;
  unsigned int  _t;
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
  inline char	_keyPressed(int a) {
    char	lol;
    
    lol = 0; 
    if(sf::Joystick::isButtonPressed(a, 1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
     lol |= mask('2');
    if(sf::Joystick::isButtonPressed(a, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      lol |= mask('4');
    if(sf::Joystick::isButtonPressed(a, 3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      lol |= mask('6');
    if(sf::Joystick::isButtonPressed(a, 2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      lol |= mask('8');
    return(lol);
  }
public:
  Input(std::string, unsigned int);
  bool check(int); 
};

#endif

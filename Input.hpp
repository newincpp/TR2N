#ifndef INPUT_H_
#define INPUT_H_

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>

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
  inline char	_keyPressed() {
    char	lol;
    
    lol = 0; 
    if(sf::Joystick::isButtonPressed(0, 1))
     lol |= mask('2');
    if(sf::Joystick::isButtonPressed(0, 0))
      lol |= mask('4');
    if(sf::Joystick::isButtonPressed(0, 3))
      lol |= mask('6');
    if(sf::Joystick::isButtonPressed(0, 2))
      lol |= mask('8');
    return(lol);
  }
public:
  Input(std::string, unsigned int);
  bool check(); 
};

#endif

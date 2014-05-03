#include "Input.hpp"

bool Input::check()
{
  char	c;

  c = _keyPressed();
  if (c & mask(_move[_i]))
    _i++;
  else if (_i > 0)
    if (c ^ mask(_move[_i - 1]) && c != 0)
      _i = 0;
  if (_i == _move.size())
    return (true);
  return (false);
}

Input::Input(std::string a) : _move(a), _i(0)
{
}

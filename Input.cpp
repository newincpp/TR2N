#include "Input.hpp"

bool	Input::check(int a)
{
  char	c;

  _t++;
  if (_i == _move.size())
    _i = 0;
  c = _keyPressed(a);
  if (c & mask(_move[_i]))
    {    
      _i++;
      _t = 0;
    }
  else if (_i > 0 )
    if (c ^ mask(_move[_i - 1]) && c != 0)
      {      
	_i = 0;
	_t = 0;
      }
  if (_t > _f)
    _i = 0;
  if (_i == _move.size())
    return (true);
  return (false);
}

void	Input::clear()
{
  _i = 0;
}
Input::Input(std::string a, unsigned int frame) : _move(a), _i(0), _f(frame), _t(0)
{
}

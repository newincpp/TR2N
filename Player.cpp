#include <iostream>
#include "Player.hpp"

Player::Player(Attack &a) : _life(100), _otherPlayer(NULL), _currentAttack(0), _shouldStop(false), _position(0, 0, 32, 32), _attack(a) {
}

Player::Player(Player *other, Attack &a) : _life(100), _otherPlayer(other), _currentAttack(0), _shouldStop(false), _position(0, 0, 32, 32), _attack(a) {
}

Player::~Player() {
}

int Player::getLife() const {
    return (_life);
}

void Player::setLife(int life) {
    _life = life;
}

void Player::addAttack(Attack &newAttack, int attackLife, Animation &getAnimation, Input i) {
    _attack = newAttack;
    _animationList.push_back(getAnimation);
    _attackLife.push_back(attackLife);
    _inputList.push_back(i);
}

void Player::tryAttack() {
    unsigned int i = 0;
    bool res;

    if (_animationList.size() > 0 && _otherPlayer != NULL) {
	for (unsigned int j = 0; j < _inputList.size(); ++j) {
	    if ((res = _inputList[j].check()) == true) {
		i = j;
		j = _inputList.size();
	    }
	}
	if (res == true) {
	    _attack.play(_position, _animationList[i]);
	    _shouldStop = false;
	    _currentAttack = i;
	    if (_attack.update(_otherPlayer->getPosition()) == false) {
	        _otherPlayer->setLife(_otherPlayer->getLife() - _attackLife[i]);
	        _shouldStop = true;
	    }
	}
    }
}

bool Player::update() {
    if (!_otherPlayer) {
	std::cerr << "FUCK YOU SERIOUSLY  FUCK ! YOU !" << std::endl;
	return false;
    }
    if (_life <= 0) {
	return (false);
    }
    if (_shouldStop == false) {
	_attack.getAnimatedSprite().move(_position.left, _position.top);
	std::cout << "move" << std::endl;
    }
    if (_attack.isPlaying() == false) {
	_shouldStop = true;
	tryAttack();
    }
    if (_attack.update(_otherPlayer->getPosition()) == false) {
	_otherPlayer->setLife(_otherPlayer->getLife() - _attackLife[_currentAttack]);
	_shouldStop = true;
    }
    return (true);
}

sf::IntRect const &Player::getPosition() const {
    return (_position);
}

void Player::setPosition(int x, int y) {
    _position.top = x;
    _position.left = y;
    _attack.getAnimatedSprite().move(_position.left, _position.top);
}

AnimatedSprite Player::getASprite() const {
    return (_attack.getAnimatedSprite());
}

void Player::setVs(Player* other) {
    _otherPlayer = other;
}

void Player::start(int i) {
    _attack.play(_position, _animationList[i]);
    _currentAttack = i;
}

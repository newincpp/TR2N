#include <iostream>
#include "Player.hpp"

Player::Player(Attack &a, int x, int y, int joystick) : _life(100), _otherPlayer(NULL), _currentAttack(0), _shouldStop(false), _position(x, y, 450, 450), _attack(a), _joy(joystick), _isStun(false), _stunFrame(0) {
}

Player::Player(Attack &a, int x, int y,int joystick, Player *other) : _life(100), _otherPlayer(other), _currentAttack(0), _shouldStop(false), _position(x, y, 450, 450), _attack(a), _joy(joystick), _isStun(false), _stunFrame(0) {
}

Player::~Player() {
}

int Player::getLife() const {
    return (_life);
}

void Player::setLife(int life) {
    _life = life;
}

void Player::addAttack(Attack &newAttack, int attackLife, Animation &getAnimation, Input i, std::pair<int, int> move) {
    _attack = newAttack;
    _animationList.push_back(std::make_pair(getAnimation, i));
    _moveLife.push_back(std::make_pair(move, attackLife));
}

void Player::tryAttack() {
    unsigned int i = 0;
    bool res;

    if (_animationList.size() > 0 && _otherPlayer != NULL) {
	for (unsigned int j = 0; j < _animationList.size(); ++j) {
	    if ((res = _animationList[j].second.check(_joy)) == true) {
		i = j;
		j = _animationList.size();
		for (unsigned int k = 0; k < _animationList.size(); ++k) {
		    _animationList[k].second.clear();
		}
	    }
	}
	_attack.play(_position, _animationList[i].first);
	_shouldStop = false;
	_currentAttack = i;
	if (_attack.update(_otherPlayer->getPosition()) == true) {
	    _otherPlayer->setLife(_otherPlayer->getLife() - _moveLife[i].second);
	    if (_moveLife[i].second != 0)
		_otherPlayer->setStun(true);
	    _shouldStop = true;
	}
    }
}

void Player::setStun(bool stun) {
    _isStun = stun;
    _stunFrame = 0;
    _attack.play(_position, _animationList[1].first);
}

bool Player::update() {
    bool dec;

    if (!_otherPlayer) {
	return false;
    }
    if (_life <= 0) {
	return (false);
    }
    if (_isStun == true && _stunFrame < 40) {
	_attack.update(_otherPlayer->getPosition());
	++_stunFrame;
    } else if (_isStun == true) {
	_isStun = false;
	_stunFrame = 0;
	_attack.stop();
    }
    if (_isStun == false) {
	if (_attack.isPlaying() == false || (_currentAttack == 0)) {
	    _shouldStop = true;
	    tryAttack();
	}
	dec = false;
	if (_attack.isPlaying() == true && _attack.testHitbox(_otherPlayer->getPosition()) == false) {
	    _position.top += _moveLife[_currentAttack].first.first;
	    _position.left += _moveLife[_currentAttack].first.second;
	    _attack.updateOffset(_position);
	    if (_attack.testHitbox(_otherPlayer->getPosition()) == false) {
		_attack.getAnimatedSprite().move(_moveLife[_currentAttack].first.second, _moveLife[_currentAttack].first.first);
	    } else {
		dec = true;
	    }
	}
	if (_shouldStop == false && _attack.update(_otherPlayer->getPosition()) == true) {
	    _otherPlayer->setLife(_otherPlayer->getLife() - _moveLife[_currentAttack].second);
	    if (_moveLife[_currentAttack].second != 0)
		_otherPlayer->setStun(true);
	    _shouldStop = true;
	} else if (_shouldStop == true) {
	    _attack.update(_otherPlayer->getPosition());
	}
	if (dec == true) {
	    _position.top -= _moveLife[_currentAttack].first.first;
	    _position.left -= _moveLife[_currentAttack].first.second;
	    _attack.updateOffset(_position);
	}
    }
    return (true);
}

sf::IntRect const &Player::getPosition() const {
    return (_position);
}

void Player::setPosition(int x, int y) {
    _position.top += x;
    _position.left += y;
    _attack.getAnimatedSprite().move(y, x);
}

AnimatedSprite Player::getASprite() const {
    return (_attack.getAnimatedSprite());
}

void Player::setVs(Player* other) {
    _otherPlayer = other;
}

void Player::start(int i) {
    _attack.play(_position, _animationList[i].first);
    _currentAttack = i;
}

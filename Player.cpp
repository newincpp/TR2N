#include <iostream>
#include "Player.hpp"

Player::Player(sf::Texture &texture) : _life(100), _otherPlayer(NULL), _currentAttack(0), _shouldStop(false), _texture(texture, sf::IntRect(32, 0, 32, 32)), _position(0, 0, 32, 32) {
}

Player::Player(sf::Texture &texture, Player *other) : _life(100), _otherPlayer(other), _currentAttack(0), _shouldStop(false), _texture(texture, sf::IntRect(32, 0, 32, 32)), _position(0, 0, 32, 32) {
}

Player::~Player() {
}

int Player::getLife() const {
    return (_life);
}

void Player::setLife(int life) {
    _life = life;
}

void Player::addAttack(Attack &newAttack, int attackLife) {
    newAttack.setInpact(attackLife);
    _attackList.push_back(newAttack);
}

void Player::tryAttack(/*inputSet &input*/) {
    int i = 0;

    if (_attackList.size() > 0 && _otherPlayer != NULL) {
	//if (_attackInput.find(input)) {
	_attackList[i].play(_texture.getTextureRect());
	_shouldStop = false;
	_currentAttack = i;
	if (_attackList[i].update(_otherPlayer->getPosition()) == true) {
	    _otherPlayer->setLife(_otherPlayer->getLife() - _attackList[i].getInpact());
	    _shouldStop = true;
	}
	//}
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
    _otherPlayer->getPosition();
    const sf::IntRect& r = _otherPlayer->getPosition();
    if (_attackList[_currentAttack].update(_otherPlayer->getPosition()) == true) {
	_otherPlayer->setLife(_otherPlayer->getLife() - _attackList[_currentAttack].getInpact());
	_shouldStop = true;
    }
    return (true);
}

sf::IntRect const &Player::getPosition() {
    return (_position);
}

AnimatedSprite const &Player::getASprite() const {
    return (_attackList[_currentAttack].getAnimatedSprite());
}

void Player::setVs(Player* other) {
    _otherPlayer = other;
}

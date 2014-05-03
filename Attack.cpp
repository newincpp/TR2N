#include <iostream>
#include "Attack.hpp"

Attack::Attack(AnimatedSprite &a, int collisionFrame, sf::IntRect rect) : _animatedSprite(a), _collisionFrame(collisionFrame), _currentFrame(0), _rect(rect) {
    _animatedSprite.setLooped(false);
}

Attack::Attack(Attack const &src) : _animatedSprite(src.getAnimatedSprite()), _collisionFrame(src.getCollisionFrame()), _currentFrame(0), _rect(src.getRect()) {
    _animatedSprite.setLooped(false);
}

Attack const &Attack::operator=(Attack const &src) {
    _animatedSprite = src.getAnimatedSprite();
    _collisionFrame = src.getCollisionFrame();
    _currentFrame = 0;
    _rect = src.getRect();
    return (*this);
}

Attack::~Attack() {
}

int Attack::getCollisionFrame() const {
    return (_collisionFrame);
}

sf::IntRect const &Attack::getRect() const {
    return (_rect);
}

bool Attack::testHitbox(sf::IntRect const &collisionRect) {
    bool ret;

    _rect.left = _offset.left;
    _rect.top = _offset.top;
    ret = _rect.intersects(collisionRect);
    return (ret);
}

void Attack::updateOffset(sf::IntRect const &offset) {
    _offset.left = offset.left;
    _offset.top = offset.top;
}

bool Attack::update(sf::IntRect const &collisionRect) {
    bool ret = false;

    ++_currentFrame;
    if (_currentFrame == _collisionFrame) {
	ret = testHitbox(collisionRect);
    }
    _animatedSprite.update(_clock.restart());
    return (ret);
}

void Attack::stop() {
    _animatedSprite.stop();
    _currentFrame = 0;
}

void Attack::play(sf::IntRect const &offset, Animation &animation) {
    _currentFrame = 0;
    _offset = offset;
    _animatedSprite.play(animation);
    _animatedSprite.setPosition(offset.left, offset.top);
}

AnimatedSprite &Attack::getAnimatedSprite() const {
    return (_animatedSprite);
}

int Attack::getCurrentFrame() const {
    return (_currentFrame);
}

bool Attack::isPlaying() const {
    return (_animatedSprite.isPlaying());
}

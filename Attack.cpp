#include <iostream>
#include "Attack.hpp"

Attack::Attack(AnimatedSprite &a, int collisionFrame, sf::IntRect rect) : _animatedSprite(a), _collisionFrame(collisionFrame), _currentFrame(0), _rect(rect) {
    _animatedSprite.setLooped(false);
    _animatedSprite.play();
}

Attack::Attack(Attack const &src) : _animatedSprite(src.getAnimatedSprite()), _collisionFrame(src.getCollisionFrame()), _currentFrame(0), _rect(src.getRect()) {
    _animatedSprite.setLooped(false);
    _animatedSprite.play();
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

    std::cout << "hey" << std::endl;
    std::cout << "rect: l=" << _rect.left << " t=" << _rect.top << " w=" << _rect.width << " h=" << _rect.height << std::endl;
    std::cout << "offset: l=" << collisionRect.left << " t=" << collisionRect.top << " w=" << collisionRect.width << " h=" << collisionRect.height << std::endl;
    _rect.left += _offset.left;
    std::cout << "int:" << std::endl;
    ret = _rect.intersects(collisionRect);
    std::cout << "int ok!" << std::endl;
    _rect.left -= _offset.left;
    return (ret);
}

bool Attack::update(sf::IntRect const &collisionRect) {
    bool ret = false;

    ++_currentFrame;
    if (_currentFrame == _collisionFrame) {
    std::cout << "test" << std::endl;
	ret = testHitbox(collisionRect);
    }
    std::cout << "hay2" << std::endl;
    _animatedSprite.update(_clock.restart());
    std::cout << "hay3" << std::endl;
    return (ret);
}

void Attack::stop() {
    _animatedSprite.stop();
    _currentFrame = 0;
}

void Attack::play(sf::IntRect const &offset) {
    _currentFrame = 0;
    _offset = offset;
    _animatedSprite.play();
}

AnimatedSprite &Attack::getAnimatedSprite() const {
    return (_animatedSprite);
}

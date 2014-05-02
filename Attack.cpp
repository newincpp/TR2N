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

bool Attack::testHitbox(sf::IntRect &collisionRect) {
    bool ret;

    _rect.left += _offset.left;
    ret = _rect.intersects(collisionRect);
    _rect.left -= _offset.left;
    return (ret);
}

bool Attack::update(sf::IntRect collisionRect) {
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

void Attack::play(sf::IntRect const &offset) {
    _currentFrame = 0;
    _offset = offset;
    _animatedSprite.play();
}

AnimatedSprite &Attack::getAnimatedSprite() const {
    return (_animatedSprite);
}

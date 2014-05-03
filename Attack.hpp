#ifndef ATTACK_H_
# define ATTACK_H_

#include "AnimatedSprite.hpp"
#include <SFML/Graphics.hpp>

class Attack {
    private:
	AnimatedSprite &_animatedSprite;
	int _collisionFrame;
	int _currentFrame;
	sf::IntRect _offset;
	sf::Clock _clock;
	sf::IntRect _rect;
    public:
	explicit Attack(AnimatedSprite &, int, sf::IntRect);
	Attack(Attack const &);
	Attack const &operator=(Attack const &);
	~Attack();
	bool testHitbox(sf::IntRect &);
	int getCollisionFrame() const;
	sf::IntRect const &getRect() const;
	void stop();
	void play(sf::IntRect const &);
	bool update(sf::IntRect);
	AnimatedSprite &getAnimatedSprite() const;
};

#endif /* !ATTACK_H_ */

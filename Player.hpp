#ifndef PLAYER_H_
# define PLAYER_H_

#include "Input.hpp"
#include "Attack.hpp"
#include "AnimatedSprite.hpp"

class Player {
    private:
	int _life;
	Player *_otherPlayer;
	int _currentAttack;
	bool _shouldStop;
	sf::IntRect _position;
	Attack &_attack;
	int _currentFrame;
	std::vector<std::pair<Animation, Input>> _animationList;
	std::vector<std::pair<std::pair<int, int>, int>> _moveLife;
	Player();
	Player(Player const &);
	Player const &operator=(Player const &);
    public:
	Player(Attack &, int, int);
	Player(Attack &, int, int, Player *);
	~Player();
	void setVs(Player*);
	int getLife() const;
	void setLife(int);
	void addAttack(Attack &, int, Animation &, Input, std::pair<int, int>);//attack and life other player will eventually loose
	void tryAttack();
	bool update(); //return false when player is dead
	sf::IntRect const &getPosition() const;
	void setPosition(int x, int y);
	AnimatedSprite getASprite() const;
	void start(int);
};

#endif /* !PLAYER_H_ */

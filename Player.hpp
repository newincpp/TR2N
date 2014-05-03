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
	std::vector<Animation> _animationList;
	std::vector<int> _attackLife;
	std::vector<Input> _inputList;
	Player();
	Player(Player const &);
	Player const &operator=(Player const &);
    public:
	Player(Attack &);
	Player(Player *, Attack &);
	~Player();
	void setVs(Player*);
	int getLife() const;
	void setLife(int);
	void addAttack(Attack &, int, Animation &, Input);//attack and life other player will eventually loose
	void tryAttack();
	bool update(); //return false when player is dead
	sf::IntRect const &getPosition() const;
	void setPosition(int x, int y);
	AnimatedSprite getASprite() const;
	void start(int);
};

#endif /* !PLAYER_H_ */

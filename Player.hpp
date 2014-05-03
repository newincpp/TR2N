#ifndef PLAYER_H_
# define PLAYER_H_

#include "Attack.hpp"
#include "AnimatedSprite.hpp"

class Player {
    private:
	int _life;
	Player *_otherPlayer;
	int _currentAttack;
	bool _shouldStop;
	sf::Sprite _texture;
	sf::IntRect _position;
	std::vector<Attack> _attackList;
	//std::vector<inputSet&> _attackInput;
	Player();
	Player(Player const &);
	Player const &operator=(Player const &);
    public:
	Player(sf::Texture &);
	Player(sf::Texture &, Player *);
	~Player();
	void setVs(Player*);
	int getLife() const;
	void setLife(int);
	void addAttack(Attack &, int); //+inputSet
	void addPlayer(Attack &, int);//attack and life other player will eventually loose
	void tryAttack();
	bool update(); //return false when player is dead
	sf::IntRect const &getPosition();
	AnimatedSprite const &getASprite() const;
};

#endif /* !PLAYER_H_ */

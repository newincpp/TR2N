#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <unistd.h>
#include <list>
#include "Attack.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include <iostream>

int main() {
    // setup window
    sf::Vector2i screenDimensions(1920,1080);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setFramerateLimit(60);

    // load texture (spritesheet)
    sf::Texture texture;
    if (!texture.loadFromFile("anim.png"))
    {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));
    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    AnimatedSprite animatedSprite1(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions.x / 2 + 30, screenDimensions.y / 2));
    animatedSprite1.setPosition(sf::Vector2f(screenDimensions.x / 2 - 30, screenDimensions.y / 2));

    sf::Clock frameClock;

    Attack c(animatedSprite, 2, sf::IntRect(0, 0, 0, 0));
    Attack d(animatedSprite1, 2, sf::IntRect(0, 0, 0, 0));
    Player player1(c, screenDimensions.x / 2 + 30, screenDimensions.y / 2);
    Player player2(d, screenDimensions.x / 2 - 30, screenDimensions.y / 2, &player1);
    Input i1("248", 60);
    Input i2("268", 60);
    player1.setVs(&player2);
    Attack a(animatedSprite, 2, player1.getPosition());
    Attack b(animatedSprite1, 2, player2.getPosition());
    player1.addAttack(a, 10, walkingAnimationRight, i1, std::make_pair(0, 1));
    player1.addAttack(a, 10, walkingAnimationLeft, i2, std::make_pair(0, -1));
    player2.addAttack(b, 10, walkingAnimationLeft, i1, std::make_pair(0, -1));
    player2.addAttack(b, 10, walkingAnimationRight, i2, std::make_pair(0, 1));

    player1.start(0);
    player2.start(0);

    //cool music is cool

    std::list<std::string> musicList;
    musicList.push_back("deadlyClass.ogg");
    musicList.push_back("testflight.ogg");
    std::list<std::string>::const_iterator lit(musicList.begin());
    sf::Music music;
    if (!music.openFromFile(*lit))
      return -1; // erreur
    music.play();

    while (window.isOpen())
    {
      if (music.getStatus() == sf::SoundSource::Status::Stopped)
	{
	  lit++;
	  //if (!music.openFromFile(*lit))
	  if (lit == musicList.end()) {
	    lit = musicList.begin();
	  }
	  music.play();
	}
	sf::Event event;
	while (window.pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window.close();
	    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		window.close();
	}
	if (player1.update() == false) {
	    std::cout << "player 2 won" << std::endl;
	    window.close();
	    return (0);
	}
	if (player2.update() == false) {
	    std::cout << "player 1 won" << std::endl;
	    window.close();
	    return (0);
	}
	//sf::Vector2f movement(0.f, 0.f);
	// draw
	window.clear();
	window.draw(player1.getASprite());
	window.draw(player2.getASprite());
	window.display();
    }
}

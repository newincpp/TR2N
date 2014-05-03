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

    Animation walkingAnimationDown1;
    walkingAnimationDown1.setSpriteSheet(texture);
    walkingAnimationDown1.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown1.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown1.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown1.addFrame(sf::IntRect( 0, 0, 32, 32));
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    AnimatedSprite animatedSprite1(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));
    animatedSprite1.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    Attack c(animatedSprite, 2, sf::IntRect(0, 0, 0, 0));
    Attack d(animatedSprite1, 2, sf::IntRect(0, 0, 0, 0));
    Player player1(c);
    Player player2(&player1, d);
    Input i1("248", 60);
    Input i2("268", 60);
    player1.setVs(&player2);
    Attack a(animatedSprite, 2, player1.getPosition());
    Attack b(animatedSprite1, 2, player2.getPosition());
    player1.addAttack(a, 90, walkingAnimationDown, i1);
    player2.addAttack(b, 90, walkingAnimationDown1, i2);
    player1.setPosition(0, 1);
    player2.setPosition(0, -1);

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

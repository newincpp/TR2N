#include <SFML/Graphics.hpp>
#include "Attack.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include <iostream>

int main() {
    // setup window
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setFramerateLimit(60);

    // load texture (spritesheet)
    sf::Texture texture;
    if (!texture.loadFromFile("anim.png"))
    {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }

    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    Player player1(texture);
    Player player2(texture, &player1);
    player1.setVs(&player2);
    animatedSprite.setPosition(50, 50);
    Attack a(animatedSprite, 2, player1.getPosition());
    player1.addAttack(a, 10);

    player1.tryAttack();
    while (window.isOpen())
    {
	sf::Event event;
	while (window.pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window.close();
	    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		window.close();
	}
	//	player1.update();
	
	bool  movecheck;
	Input lol("248");
	while (42)
	  {
	    movecheck = lol.check();
	    if (movecheck != false)
	      std::cout<<movecheck<<std::endl;
	  }
	
	// if a key was pressed set the correct animation and move correctly
	sf::Vector2f movement(0.f, 0.f);
	// draw
	window.clear();
	window.draw(player1.getASprite());
	window.display();
    }
}

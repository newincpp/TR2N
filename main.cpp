#include <SFML/Graphics.hpp>
#include <unistd.h>
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

    Attack c(animatedSprite, 2, sf::IntRect(0, 0, 0, 0));
    Attack d(animatedSprite, 2, sf::IntRect(0, 0, 0, 0));
    Player player1(c);
    Player player2(&player1, c);
    Input i1("248", 60);
    Input i2("268", 60);
    player1.setVs(&player2);
    Attack a(animatedSprite, 2, player1.getPosition());
    Attack b(animatedSprite, 2, player2.getPosition());
    player1.addAttack(a, 10, walkingAnimationDown, i1);
    player2.addAttack(b, 10, walkingAnimationDown, i2);

    player1.start(0);
    player2.start(0);
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
	player1.update();
	player2.update();
	//sf::Vector2f movement(0.f, 0.f);
	// draw
	window.clear();
	window.draw(player1.getASprite());
	window.draw(player2.getASprite());
	window.display();
    }
}

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/System/Time.hpp>
#include <unistd.h>
#include <list>
#include "Attack.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include "LifeBar.hpp"
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
    
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("bg.png"))
    {
	std::cout << "Failed to load ta mere(bg)!" << std::endl;
	return 1;
    }

    sf::Texture texta;
    if (!texta.loadFromFile("blends/AtkAnimSprites.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation AtkAnim;
    AtkAnim.setSpriteSheet(texta);
    for (int i = 0; i < 10017; i += 626) {
	AtkAnim.addFrame(sf::IntRect(i, 0, 626, 724));
    }
    sf::Texture textb;
    if (!textb.loadFromFile("blends/AtkAnimSpritesBlue.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation AtkAnimBlue;
    AtkAnimBlue.setSpriteSheet(textb);
    for (int i = 0; i < 10017; i += 626) {
	AtkAnimBlue.addFrame(sf::IntRect(i, 0, 626, 724));
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
    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    AnimatedSprite animatedSprite(sf::seconds(0.01), true, false);
    AnimatedSprite animatedSprite1(sf::seconds(0.01), true, false);
    animatedSprite.setPosition(sf::Vector2f(100, 200));
    animatedSprite1.setScale(-1, 1);
    animatedSprite1.setPosition(sf::Vector2f(1400, 200));

    sf::Clock frameClock;

    Attack c(animatedSprite, 2, sf::IntRect(0, 0, 0, 0));
    Attack d(animatedSprite1, 2, sf::IntRect(0, 0, 0, 0));
    Player player1(c, 100, 200, 0);
    Player player2(d, 1400, 200, 2, &player1);
    Input i1("248", 60);
    Input i2("268", 60);
    Input i3("464", 60);
    Input i4("646", 60);
    player1.setVs(&player2);
    Attack a(animatedSprite, 2, player1.getPosition());
    Attack b(animatedSprite1, 2, player2.getPosition());
    player1.addAttack(a, 0, AtkAnim, i1, std::make_pair(0, 1));
    player1.addAttack(a, 0, walkingAnimationLeft, i2, std::make_pair(0, -1));
    player1.addAttack(a, 0, walkingAnimationUp, i3, std::make_pair(0, 0));
    player1.addAttack(a, 0, walkingAnimationDown, i4, std::make_pair(0, 0));
    player2.addAttack(b, 10, AtkAnimBlue, i1, std::make_pair(0, -1));
    player2.addAttack(b, 10, walkingAnimationRight, i2, std::make_pair(0, 1));
    player2.addAttack(b, 0, walkingAnimationUp, i3, std::make_pair(0, 0));
    player2.addAttack(b, 0, walkingAnimationDown, i4, std::make_pair(0, 0));

    player1.start(0);
    player2.start(0);

    //cool music is cool

    std::list<std::string> musicList;
    musicList.push_back("testflight.ogg");
    musicList.push_back("deadlyClass.ogg");
    musicList.push_back("deadlyClass.ogg");
    std::list<std::string>::const_iterator lit(musicList.begin());
    sf::Music music;
    if (!music.openFromFile(*lit))
	return -1; // erreur
    music.setLoop(false);
    music.play();

    LifeBar Lb1(20, 0);
    LifeBar Lb2(1890, 1);

    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTexture);

    while (window.isOpen())
    {
      Lb1.Set(player1.getLife());
      Lb2.Set(player2.getLife());

	if (music.getStatus() == sf::SoundSource::Status::Stopped)
	{
	    lit++;
	    if (lit == musicList.end())
		lit = musicList.begin();
	    if (!music.openFromFile(*lit))
		return (-1);
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
	window.draw(bgSprite);
	window.draw(Lb1.Get());
	window.draw(Lb2.Get());
	window.draw(player1.getASprite());
	window.draw(player2.getASprite());
	window.display();
    }
}

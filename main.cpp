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
    window.setVerticalSyncEnabled(true);

    sf::Font tr;

    tr.loadFromFile("Tr2n.ttf");
    sf::Text loading("loading", tr, 100);
    loading.setColor(sf::Color::Cyan);
    loading.setPosition(750, 490);

    window.clear();
    window.draw(loading);
    window.display();


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
    for (int i = 0; i < 6464; i += 404) {
	AtkAnim.addFrame(sf::IntRect(i, 0, 404, 404));
    }
    sf::Texture textb;
    if (!textb.loadFromFile("blends/AtkAnimSpritesBlue.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation AtkAnimBlue;
    AtkAnimBlue.setSpriteSheet(textb);
    for (int i = 0; i < 6464; i += 404) {
	AtkAnimBlue.addFrame(sf::IntRect(i, 0, 404, 404));
    }
    sf::Texture textc;
    if (!textc.loadFromFile("blends/dashAnimSprites.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation DashAnim;
    DashAnim.setSpriteSheet(textc);
    for (int i = 0; i < 6464; i += 404) {
	DashAnim.addFrame(sf::IntRect(i, 0, 404, 404));
    }
    sf::Texture textd;
    if (!textd.loadFromFile("blends/dashAnimSpritesBlue.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation DashAnimBlue;
    DashAnimBlue.setSpriteSheet(textd);
    for (int i = 0; i < 6464; i += 404) {
	DashAnimBlue.addFrame(sf::IntRect(i, 0, 404, 404));
    }
    sf::Texture texte;
    if (!texte.loadFromFile("blends/standAnim.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation standAnim;
    standAnim.setSpriteSheet(texte);
    for (int i = 0; i < 6464; i += 404) {
	standAnim.addFrame(sf::IntRect(i, 0, 404, 404));
    }
    sf::Texture textf;
    if (!textf.loadFromFile("blends/standAnimBlue.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation standAnimBlue;
    standAnimBlue.setSpriteSheet(textf);
    for (int i = 0; i < 6464; i += 404) {
	standAnimBlue.addFrame(sf::IntRect(i, 0, 404, 404));
    }
    sf::Texture textg;
    if (!textg.loadFromFile("redStun.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation stun;
    stun.setSpriteSheet(textg);
    stun.addFrame(sf::IntRect(0, 0, 400, 400));
    sf::Texture texth;
    if (!texth.loadFromFile("blueStun.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation stunBlue;
    stunBlue.setSpriteSheet(texth);
    stunBlue.addFrame(sf::IntRect(0, 0, 400, 400));
    sf::Texture texti;
    if (!texti.loadFromFile("blends/spritesFastAtkAnimBlue.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation fastAtkBlue;
    fastAtkBlue.setSpriteSheet(texti);
    for (int i = 0; i < 2424; i += 404) {
	fastAtkBlue.addFrame(sf::IntRect(i, 0, 404, 404));
    }
    sf::Texture textj;
    if (!textj.loadFromFile("blends/spritesFastAtkAnim.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation fastAtk;
    fastAtk.setSpriteSheet(textj);
    for (int i = 0; i < 2424; i += 404) {
	fastAtk.addFrame(sf::IntRect(i, 0, 404, 404));
    }
    sf::Texture textk;
    if (!textk.loadFromFile("blends/Atk2Sprites.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation Atk2Anim;
    Atk2Anim.setSpriteSheet(textk);
    for (int i = 0; i < 6464; i += 404) {
	Atk2Anim.addFrame(sf::IntRect(i, 0, 404, 404));
    }
    sf::Texture textl;
    if (!textl.loadFromFile("blends/Atk2SpritesBlue.png")) {
	std::cout << "Failed to load player spritesheet!" << std::endl;
	return 1;
    }
    Animation Atk2AnimBlue;
    Atk2AnimBlue.setSpriteSheet(textl);
    for (int i = 0; i < 6464; i += 404) {
	Atk2AnimBlue.addFrame(sf::IntRect(i, 0, 404, 404));
    }

    AnimatedSprite animatedSprite(sf::seconds(0.01), true, false);
    AnimatedSprite animatedSprite1(sf::seconds(0.01), true, false);
    animatedSprite.setPosition(sf::Vector2f(450, 500));
    animatedSprite1.setScale(-1, 1);
    animatedSprite1.setPosition(sf::Vector2f(1450, 500));

    sf::Clock frameClock;

    Attack c(animatedSprite, 2, sf::IntRect(0, 0, 0, 0));
    Attack d(animatedSprite1, 2, sf::IntRect(0, 0, 0, 0));
    Player player1(c, 550, 500, 0);
    Player player2(d, 1550, 500, 2, &player1);
    Input i("2525252525", 60);
    Input i1("254585", 60);
    Input i2("258", 60);
    Input i3("454545", 60);
    Input i4("656565", 60);
    Input i5("4525652", 60);
    player1.setVs(&player2);
    Attack a(animatedSprite, 2, player1.getPosition());
    Attack b(animatedSprite1, 2, player2.getPosition());
    player1.addAttack(a, 0, standAnim, i, std::make_pair(0, 0));
    player1.addAttack(a, 0, stun, i, std::make_pair(0, 0));
    player1.addAttack(a, 10, AtkAnim, i1, std::make_pair(0, 1));
    player1.addAttack(a, 0, DashAnim, i3, std::make_pair(0, -4));
    player1.addAttack(a, 0, DashAnim, i4, std::make_pair(0, 4));
    player1.addAttack(a, 5, fastAtk, i2, std::make_pair(0, 4));
    player1.addAttack(a, 50, Atk2Anim, i5, std::make_pair(0, 4));
    player2.addAttack(b, 0, standAnimBlue, i, std::make_pair(0, 0));
    player2.addAttack(b, 0, stunBlue, i, std::make_pair(0, 0));
    player2.addAttack(b, 10, AtkAnimBlue, i1, std::make_pair(0, -1));
    player2.addAttack(b, 0, DashAnimBlue, i3, std::make_pair(0, 4));
    player2.addAttack(b, 0, DashAnimBlue, i4, std::make_pair(0, -4));
    player2.addAttack(b, 5, fastAtkBlue, i2, std::make_pair(0, -4));
    player2.addAttack(b, 50, Atk2AnimBlue, i5, std::make_pair(0, -4));

    player1.start(0);
    player2.start(0);

    sf::Text akai("AKAI", tr, 40);
    sf::Text ao("AO", tr, 40);
    akai.setColor(sf::Color::Red);
    ao.setColor(sf::Color::Cyan);
    akai.setPosition(18, 50);
    ao.setPosition(1840, 50);

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
    Lb2.SetColor(sf::Color::Cyan);

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
	window.draw(akai);
	window.draw(ao);
	window.draw(Lb1.Get());
	window.draw(Lb2.Get());
	window.draw(player1.getASprite());
	window.draw(player2.getASprite());
	window.display();
    }
}

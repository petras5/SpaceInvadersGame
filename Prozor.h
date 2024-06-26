#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Prozor {
public:
	Prozor();
	Prozor(const std::string&, const sf::Vector2u&);
	void prebaciNaCijeli();
	void ocisti();
	void crtaj(sf::Drawable&);
	void prikazi();
	void update();
	~Prozor();
	bool jelGotov() const {
		return gotov;
	}
	bool jelCijeli() const {
		return cijeliZaslon;
	}
	sf::Vector2u dohvatiVelicinu() const {
		return velicina;
	}
private:
	void Stvori();
	void Unisti();
	void Postavi(const std::string&, const sf::Vector2u&);
	sf::RenderWindow prozor;
	sf::Vector2u velicina;
	std::string naslov;
	bool gotov;
	bool cijeliZaslon;
};

void Prozor::update() {
	sf::Event event;
	while (prozor.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			gotov = true;
		else if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::F5)
			prebaciNaCijeli();
	}
}

void Prozor::prebaciNaCijeli() {
	cijeliZaslon = !cijeliZaslon;
	Unisti();
	Stvori();
}

Prozor::Prozor(const std::string& n,
	const sf::Vector2u& v) {
	Postavi(n, v);
}

Prozor::Prozor() {
	Postavi("Prozor", sf::Vector2u(640, 480));
}

Prozor::~Prozor() {
	Unisti();
}

void Prozor::Postavi(const std::string& n,
	const sf::Vector2u& v) {
	naslov = n;
	velicina = v;
	cijeliZaslon = false;
	gotov = false;
	//otvaranje prozora nakon popunjavanja postavki
	Stvori();
}

void Prozor::Stvori() {
	auto stil = (cijeliZaslon ? sf::Style::Fullscreen
		: sf::Style::Default);
	prozor.create(sf::VideoMode(velicina.x,
		velicina.y, 32), naslov, stil);
}

void Prozor::Unisti() {
	prozor.close();
}

void Prozor::ocisti() {
	prozor.clear(sf::Color(200, 200, 200, 255));
}

void Prozor::crtaj(sf::Drawable& d) {
	prozor.draw(d);
}

void Prozor::prikazi() {
	prozor.display();
}

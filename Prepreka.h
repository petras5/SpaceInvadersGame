#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Prozor.h"

class Prepreka
{
public:
	Prepreka(float, int, int);
	~Prepreka();
	int DohvatiBrojUdaraca();
	void PovecajBrojUdaraca();
	sf::IntRect DohvatiPravokutnik();
	void Renderiraj(Prozor*);
private:
	float velicinaBloka;
	int koordinataX;
	int koordinataY;
	int brojUdaraca;
	sf::Texture tekstura;
	sf::Sprite sprite;
};

void Prepreka::Renderiraj(Prozor* p) {
	sprite.setTexture(tekstura);
	sprite.setTextureRect(sf::IntRect(brojUdaraca * velicinaBloka * 3, 2*velicinaBloka, velicinaBloka*3, velicinaBloka*2));
	sprite.setPosition(koordinataX * velicinaBloka, koordinataY * velicinaBloka);
	p->crtaj(sprite);
}

int Prepreka::DohvatiBrojUdaraca()
{
	return brojUdaraca;
}

void Prepreka::PovecajBrojUdaraca()
{
	brojUdaraca++;
}

sf::IntRect Prepreka::DohvatiPravokutnik()
{
	sf::Vector2i pozicija(static_cast<int>(koordinataX * velicinaBloka), static_cast<int>(koordinataY * velicinaBloka));
	sf::Vector2i velicina(static_cast<int>(velicinaBloka*3), static_cast<int>(velicinaBloka*2));
	sf::IntRect preprekaArea(pozicija, velicina);
	return preprekaArea;
}

Prepreka::Prepreka(float v, int x, int y):
	velicinaBloka(v),
	koordinataX(x),
	koordinataY(y),
	brojUdaraca(0)
{
	tekstura.loadFromFile("space.png");
}
Prepreka::~Prepreka() { }
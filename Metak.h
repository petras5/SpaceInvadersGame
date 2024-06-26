#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "Prozor.h"
#include "Smjer.h"

class Metak
{
public:
	Metak(bool, float, int, int);
	sf::IntRect DohvatiPravokutnik();
	void Renderiraj(Prozor*);
	void Pomakni();
	Smjer DohvatiSmjer();
	int DohvatiKoordinatuY();
private:
	Smjer smjer; // if igracev = true: smjer == Smjer::Gore, inace smjer == Smjer::Dolje
	bool igracev; // true ako je igracev, false ako je protivnikov
	int koordinataX;
	int koordinataY;
	int pozX;
	float velicinaBloka;
	sf::Texture tekstura;
	sf::Sprite sprite;
};

Metak::Metak(bool igr, float v, int x, int y):
	igracev(igr),
	velicinaBloka(v),
	koordinataX(x),
	koordinataY(y)
{
	tekstura.loadFromFile("space.png");
	if (igracev)
	{
		smjer = Smjer::Gore;
		pozX = 0;
	}
	else
	{
		smjer = Smjer::Dolje;
		pozX = 1;
	}
}

void Metak::Renderiraj(Prozor* p) {
	sprite.setTexture(tekstura);
	sprite.setTextureRect(sf::IntRect(pozX * velicinaBloka, velicinaBloka, velicinaBloka, velicinaBloka));
	sprite.setPosition(koordinataX * velicinaBloka, koordinataY * velicinaBloka);
	p->crtaj(sprite);
}
sf::IntRect Metak::DohvatiPravokutnik()
{
	sf::Vector2i pozicija(static_cast<int>(koordinataX * velicinaBloka), static_cast<int>(koordinataY * velicinaBloka));
	sf::Vector2i velicina(static_cast<int>(velicinaBloka), static_cast<int>(velicinaBloka));
	sf::IntRect metakArea(pozicija, velicina);
	return metakArea;
}

void Metak::Pomakni()
{
	if (smjer == Smjer::Gore)
	{
		koordinataY--;
	}
	if (smjer == Smjer::Dolje)
	{
		koordinataY++;
	}
}

Smjer Metak::DohvatiSmjer()
{
	return smjer;
}

int Metak::DohvatiKoordinatuY()
{
	return koordinataY;
}
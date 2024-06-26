#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Prozor.h"
#include "Smjer.h"

class Igrac
{
public:
	Igrac(float, int, int);
	~Igrac();
	void Reset();
	bool Izgubio();
	void PostaviIzgubio(bool);
	Smjer DohvatiSmjer();
	void PostaviSmjer(Smjer);
	float DohvatiBrzinu();
	void Korak();
	void Pomakni();
	sf::Vector2i DohvatiKoordinate();
	int DohvatiBrojZivota();
	void SmanjiBrojZivota();
	int DohvatiBodove();
	void PovecajBodove(int);
	void Renderiraj(Prozor*); // da nacrta brod na prozor
	sf::IntRect DohvatiPravokutnik();
private:
	Smjer smjer; // u kojem se sljedecem smjeru igrac pomice 
	int brZivota; 
	int bodovi;
	bool izgubio;
	float brzina;
	float velBloka; // dimenzija bloka(kvadratica) 
	int maxKoordinataX, maxKoordinataY;
	int koordinataX, koordinataY;
	sf::Texture tekstura;
	sf::Sprite sprite;
	sf::Sprite spriteZivoti;
};

Igrac::Igrac(float v, int maxX, int maxY):
	velBloka(v),
	maxKoordinataX(maxX),
	maxKoordinataY(maxY),
	brZivota(3),
	bodovi(0),
	izgubio(false),
	koordinataX(maxKoordinataX / 2),
	koordinataY(maxKoordinataY - 1)
{
	tekstura.loadFromFile("space.png");
	Reset();
}

Igrac::~Igrac() {}

void Igrac::Reset()
{
	if (izgubio)
	{
		brZivota = 3;
		bodovi = 0;
		koordinataX = maxKoordinataX / 2;
		koordinataY = maxKoordinataY - 1;
		izgubio = false;
	}
	smjer = Smjer::Nema;
	brzina = 15;
}

void Igrac::PostaviSmjer(Smjer s) { // primit ce smjer s obzirom na korisnikov ulaz
	smjer = s;
}

Smjer Igrac::DohvatiSmjer() {
	return smjer;
}

bool Igrac::Izgubio()
{
	return izgubio;
}

void Igrac::PostaviIzgubio(bool b)
{
	izgubio = b;
}

float Igrac::DohvatiBrzinu() {
	return brzina;
}

void Igrac::Korak()
{
	if (smjer != Smjer::Nema) {
		Pomakni();
	}
}

void Igrac::Pomakni()
{
	if (smjer == Smjer::Lijevo)
		koordinataX--;
	else if (smjer == Smjer::Desno)
		koordinataX++;

	if (koordinataX < 0)
		koordinataX++;
	if (koordinataX >= maxKoordinataX)
		koordinataX--;
	smjer = Smjer::Nema;
}


sf::Vector2i Igrac::DohvatiKoordinate() { 
	return sf::Vector2i(koordinataX, koordinataY);
}
int Igrac::DohvatiBrojZivota() {
	return brZivota;
}

void Igrac::SmanjiBrojZivota() {
	brZivota--;
}
int Igrac::DohvatiBodove() {
	return bodovi;
}

void Igrac::PovecajBodove(int b) { 
	bodovi += b;
}

void Igrac::Renderiraj(Prozor* p) {
	int i;
	spriteZivoti.setTexture(tekstura);
	spriteZivoti.setScale(2.0f, 2.0f);
	spriteZivoti.setTextureRect(sf::IntRect(2 * velBloka, velBloka, velBloka, velBloka));
	for (i = 0; i < brZivota;i++)
	{
		spriteZivoti.setPosition((float)(maxKoordinataX - 4 + i) * velBloka, 0.0f);
		p->crtaj(spriteZivoti);
	}
	spriteZivoti.setTextureRect(sf::IntRect(3 * velBloka, velBloka, velBloka, velBloka));
	for (i = 0; i < 3-brZivota; i++)
	{
		spriteZivoti.setPosition((float)(maxKoordinataX - 2 - i) * velBloka, 0.0f);
		p->crtaj(spriteZivoti);
	}

	sprite.setTexture(tekstura);
	sprite.setTextureRect(sf::IntRect(0, 0, velBloka, velBloka));
	sprite.setPosition((float)koordinataX * velBloka, (float)koordinataY * velBloka);
	p->crtaj(sprite);
}

sf::IntRect Igrac::DohvatiPravokutnik()
{
	sf::Vector2i pozicija(static_cast<int>(koordinataX * velBloka), static_cast<int>(koordinataY * velBloka));
	sf::Vector2i velicina(static_cast<int>(velBloka), static_cast<int>(velBloka));
	sf::IntRect igracArea(pozicija, velicina);
	return igracArea;
}
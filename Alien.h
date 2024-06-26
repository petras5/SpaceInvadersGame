#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "Prozor.h"
#include "Smjer.h"

enum class VrstaAliena { Zeleni = 0, Rozi = 3, Zuti = 6 };

class Alien
{
public:
	Alien(float, int, int, int);
	~Alien();
	void Reset();
	bool Pogoden();
	void PostaviPogoden(bool);
	void PostaviSmjer(Smjer);
	void Pomakni(bool);
	void PostaviPozicijuTeksture();
	sf::Vector2i DohvatiKoordinate();
	sf::IntRect DohvatiPravokutnik();
	void Renderiraj(Prozor*);
	int DohvatiBodove();
private:
	int pozX;
	bool pogoden;
	float velicinaBloka;
	int bodovi; // svaka vrsta aliena æe nositi drugi iznos bodova i po tome cemo ih razlikovati
	int pocetnaKoordinataX, pocetnaKoordinataY;
	int koordinataX, koordinataY;
	sf::Texture tekstura;
	sf::Sprite sprite;
	VrstaAliena vrsta;
	Smjer smjer;
};

Alien::Alien(float velBloka, int b, int kX, int kY) :
	velicinaBloka(velBloka),
	bodovi(b),
	pocetnaKoordinataX(kX),
	pocetnaKoordinataY(kY)
{
	tekstura.loadFromFile("space.png");
	Reset();
}
void Alien::Reset()
{
	if (bodovi == 10)
		vrsta = VrstaAliena::Zeleni;
	else if (bodovi == 20)
		vrsta = VrstaAliena::Rozi;
	else
		vrsta = VrstaAliena::Zuti;
	smjer = Smjer::Desno;
	PostaviPozicijuTeksture();

	koordinataX = pocetnaKoordinataX;
	koordinataY = pocetnaKoordinataY;
	pogoden = false;
}

bool Alien::Pogoden()
{
	return pogoden;
}

void Alien::PostaviPogoden(bool b)
{
	pogoden = b;
}

void Alien::PostaviSmjer(Smjer s)
{
	smjer = s;
}

sf::Vector2i Alien::DohvatiKoordinate()
{
	return sf::Vector2i(koordinataX, koordinataY);
}

void Alien::PostaviPozicijuTeksture()
{
	if (vrsta == VrstaAliena::Zeleni)
		pozX = 0;
	else if (vrsta == VrstaAliena::Rozi)
		pozX = 3;
	else
		pozX = 6;

	if (smjer == Smjer::Lijevo)
		pozX += 1;
	else if (smjer == Smjer::Desno)
		pozX += 3;
}

void Alien::Pomakni(bool dotaknuoRub) 
{
	if (dotaknuoRub && smjer == Smjer::Desno) // ako je dotaknuo lijevi rub, mora se pomaknut dolje i nastaviti kretati desno
	{
		koordinataY += 1; // pomice se dolje za 1 blok
		++koordinataX; // jedan blok desno
	}
	else if (dotaknuoRub && smjer == Smjer::Lijevo)
	{
		koordinataY += 1; // pomice se dolje za 1 blok
		--koordinataX; // jedan blok lijevo
	}
	else if (!dotaknuoRub && smjer == Smjer::Desno)
	{
		++koordinataX; // jedan blok desno
	}
	else if (!dotaknuoRub && smjer == Smjer::Lijevo)
	{
		--koordinataX; // jedan blok lijevo
	}
	PostaviPozicijuTeksture();
}

void Alien::Renderiraj(Prozor* p) {
	sprite.setTexture(tekstura);
	sprite.setTextureRect(sf::IntRect(pozX*velicinaBloka, 0, velicinaBloka, velicinaBloka));
	sprite.setPosition(koordinataX * velicinaBloka, koordinataY * velicinaBloka);
	p->crtaj(sprite);
}

sf::IntRect Alien::DohvatiPravokutnik()
{
	sf::Vector2i pozicija(static_cast<int>(koordinataX*velicinaBloka), static_cast<int>(koordinataY * velicinaBloka));
	sf::Vector2i velicina(static_cast<int>(velicinaBloka), static_cast<int>(velicinaBloka));
	sf::IntRect alienArea(pozicija, velicina);
	return alienArea;
}

int Alien::DohvatiBodove()
{
	return bodovi;
}
Alien::~Alien() {}
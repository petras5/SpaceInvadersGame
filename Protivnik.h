#pragma once
#include "Smjer.h"
#include "Alien.h"
#include <vector>

class Protivnik
{
public:
	Protivnik() = default;
	Protivnik(float, int, int);
	~Protivnik();
	void Renderiraj(Prozor* p);
	void Pomakni();
	float DohvatiBrzinu();
	void ProvjeriDotaknuoRub();
	std::vector<Alien>& DohvatiAliens();
	void Reset(bool);
private:
	int maxKoordinataX;
	int maxKoordinataY;
	float velicinaBloka;
	float brzina;
	Smjer smjer;
	bool dotaknuoRub;
	int pomak;
	std::vector<Alien> aliens;

};

Protivnik::Protivnik(float v, int x, int y) :
	velicinaBloka(v),
	maxKoordinataX(x),
	maxKoordinataY(y)
{
	Reset(false);
}

void Protivnik::Reset(bool unisteniSvi)
{
	if (unisteniSvi)
	{
		pomak++;
		std::cout << "Unisteni svi alieni, stara brzina: " << brzina;
		brzina += 0.5f;
		std::cout << " nova brzina: " << brzina;
		std::cout << " pomak: " << pomak << std::endl;
		unisteniSvi = false;
	}
	else
	{
		pomak = 0;
		brzina = 1.0f;
	}
	smjer = Smjer::Desno;
	dotaknuoRub = false;
	size_t brojac = 0;
	for (auto y = 8; y >= 0; y-=2)
	{
		for (auto x = 20; x >= 0; x-=2)
		{
			if (brojac < 22)
			{
				Alien a(velicinaBloka, 10, x, y+2+pomak);
				aliens.push_back(a);
				brojac++;
			}
			else if (brojac < 44)
			{
				Alien a(velicinaBloka, 20, x, y+2+pomak);
				aliens.push_back(a);
				brojac++;
			}
			else
			{
				Alien a(velicinaBloka, 30, x, y+2+pomak);
				aliens.push_back(a);
				brojac++;
			}
		}
	}
}

void Protivnik::Renderiraj(Prozor* p)
{
	for (size_t i = 0; i < aliens.size(); i++) // s erase budem dok se uniste izbrisala pogodene (da njih ne gleda za rub) pa to ne treba dodatna provjera
		aliens[i].Renderiraj(p);
}

float Protivnik::DohvatiBrzinu() {
	return brzina;
}

void Protivnik::Pomakni()
{
	dotaknuoRub = false;
	for (size_t i = 0; i < aliens.size(); i++) // pomaknemo u trenutno postavljenom smjeru za 1 sve aliene
	{
		aliens[i].Pomakni(dotaknuoRub); 
	}
	ProvjeriDotaknuoRub(); // provjeri ako je nakon tog koraka doslo do sudara kojeg aliena s rubom
	if (dotaknuoRub) // ako je doslo do sudara pomakne ih desno (oni si promijene prikaz)
	{
		brzina += 0.1f;
		for (size_t i = 0; i < aliens.size(); i++)
		{
			aliens[i].PostaviSmjer(smjer); // mijenja se im smjer kretanja
			aliens[i].Pomakni(dotaknuoRub); // salje true
		}
	}
}

void Protivnik::ProvjeriDotaknuoRub()
{
	for (size_t i = 0; i < aliens.size(); i++)
	{
		if (aliens[i].DohvatiKoordinate().x < 0) // dotaknuo lijevi rub
		{
			smjer = Smjer::Desno;
			dotaknuoRub = true;
			break;
		}
		if (aliens[i].DohvatiKoordinate().x >= maxKoordinataX) // dotaknuo desni rub
		{
			smjer = Smjer::Lijevo;
			dotaknuoRub = true;
			break;
		}
	}
}

std::vector<Alien>& Protivnik::DohvatiAliens()
{
	return aliens;
}

Protivnik::~Protivnik() {}
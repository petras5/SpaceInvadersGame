#pragma once

#include <iostream>
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Prozor.h"
#include "Smjer.h"
#include "Alien.h"
#include "Protivnik.h"
#include "Igrac.h"
#include "Metak.h"
#include "Prepreka.h"

class Igra {
public:
	Igra();
	~Igra();
	void obradiUlaz();
	void update();
	void renderiraj();
	void Reset();
	Prozor* dohvatiProzor() {
		return &p;
	}
	sf::Time protekloVrijemeAliens();
	sf::Time protekloVrijemeIgrac();
	sf::Time protekloVrijemeMetci();
	void PomakniMetke();
	void restartSataMetci();
	void restartSataAliens();
	void restartSataIgrac();
	void ProvjeraSudaraPreprekaAlien();
	void ProvjeraSudaraMetakaPrepreka();
	void ProvjeraSudaraIgracAlien();
	void ProvjeraSudaraMetaka();
	void ProvjeraSudaraMetakAlien();
	void ProvjeraSudaraMetakIgrac();
	void IspucajMetkeAliena();
	int ProcitajHighscore();
	void ZapisiHighscore();
	void InicijalizirajPrepreke();
private:
	Prozor p;
	bool unisteniSvi;
	bool spacePressed = false;
	float brzinaMetka;
	float velicinaBloka;
	int highscore;
	int maxKoordinataX;
	int maxKoordinataY;
	Protivnik izvanzemaljci;
	Igrac igrac;
	std::vector<Metak> metciIgrac;
	std::vector<Metak> metciProtivnik;
	std::vector<Prepreka> prepreke;
	sf::Clock satAliens;
	sf::Clock satIgrac;
	sf::Clock satMetci;
	sf::Time vrijemeAliens;
	sf::Time vrijemeIgrac;
	sf::Time vrijemeMetci;
	sf::Texture teksturaMapa;
	sf::Sprite spriteMapa;
	sf::Text scoreText;
	sf::Font font;
	sf::Text highscoreText;
};

sf::Time Igra::protekloVrijemeAliens() {
	return vrijemeAliens;
}
sf::Time Igra::protekloVrijemeIgrac() {
	return vrijemeIgrac;
}
sf::Time Igra::protekloVrijemeMetci() {
	return vrijemeMetci;
}
void Igra::restartSataAliens() {
	vrijemeAliens += satAliens.restart();
}
void Igra::restartSataIgrac() {
	vrijemeIgrac += satIgrac.restart();
}
void Igra::restartSataMetci() {
	vrijemeMetci += satMetci.restart();
}

void Igra::renderiraj() {
	p.ocisti();
	p.crtaj(spriteMapa);
	p.crtaj(scoreText);
	p.crtaj(highscoreText);
	size_t i;
	for (i = 0; i < metciIgrac.size(); i++)
	{
		metciIgrac[i].Renderiraj(&p);
	}
	for (i = 0; i < metciProtivnik.size(); i++)
	{
		metciProtivnik[i].Renderiraj(&p);
	}
	izvanzemaljci.Renderiraj(&p);
	for (i = 0; i < prepreke.size(); i++)
	{
		prepreke[i].Renderiraj(&p);
	}
	igrac.Renderiraj(&p);
	p.prikazi();
}

void Igra::update() {
	p.update();
	scoreText.setString("Score: " + std::to_string(igrac.DohvatiBodove()));
	highscoreText.setString("Highscore: " + std::to_string(highscore));

	float vrijemeIteracijeAliens = 1.0f / izvanzemaljci.DohvatiBrzinu(); // koliko mora proci da bi mi izvrsili 1 korak u igri
	float vrijemeIteracijeIgrac = 1.0f / igrac.DohvatiBrzinu();
	float vrijemeIteracijeMetak = 1.0f / brzinaMetka;
	if (vrijemeAliens.asSeconds() >= vrijemeIteracijeAliens) {
		izvanzemaljci.Pomakni();
		IspucajMetkeAliena();
		vrijemeAliens -= sf::seconds(vrijemeIteracijeAliens);
	}
	if (vrijemeIgrac.asSeconds() >= vrijemeIteracijeIgrac) {
		igrac.Korak();
		vrijemeIgrac -= sf::seconds(vrijemeIteracijeIgrac);
	}
	if (vrijemeMetci.asSeconds() >= vrijemeIteracijeMetak) {
		PomakniMetke();
		vrijemeMetci -= sf::seconds(vrijemeIteracijeMetak);
	}
	ProvjeraSudaraPreprekaAlien();
	ProvjeraSudaraIgracAlien();
	ProvjeraSudaraMetakaPrepreka();
	ProvjeraSudaraMetaka();
	ProvjeraSudaraMetakAlien();
	ProvjeraSudaraMetakIgrac();
	if (!igrac.Izgubio() && izvanzemaljci.DohvatiAliens().size() == 0)
	{
		unisteniSvi = true;
		Reset();
	}
	else if (igrac.Izgubio())
	{
		ZapisiHighscore();
		Reset();
	}
}

void Igra::obradiUlaz() {
	igrac.PostaviSmjer(Smjer::Nema);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		igrac.PostaviSmjer(Smjer::Lijevo);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		igrac.PostaviSmjer(Smjer::Desno);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!spacePressed) {  // Check if space key was not pressed before
			spacePressed = true;  // Set the flag to indicate space key is pressed

			sf::Vector2i koordinateIgraca = igrac.DohvatiKoordinate();
			Metak m(true, velicinaBloka, koordinateIgraca.x, koordinateIgraca.y);
			metciIgrac.push_back(m);
		}
	}
	else {
		spacePressed = false;  // Reset the flag when space key is released
	}
}

void Igra::IspucajMetkeAliena()
{
	size_t i, index;
	for (i = 0; i < 2; i++)
	{
		index = rand() % izvanzemaljci.DohvatiAliens().size();
		Metak m(false, velicinaBloka, izvanzemaljci.DohvatiAliens()[index].DohvatiKoordinate().x, izvanzemaljci.DohvatiAliens()[index].DohvatiKoordinate().y);
		metciProtivnik.push_back(m);
	}
}

void Igra::PomakniMetke()
{
	size_t i;

	for (i = 0; i < metciIgrac.size(); i++) // svi imaju smjer gore
	{
		metciIgrac[i].Pomakni();
		if(metciIgrac[i].DohvatiKoordinatuY() < 0)
			metciIgrac.erase(metciIgrac.begin()+i);
	}

	for (i = 0; i < metciProtivnik.size(); i++) // svi imaju smjer prema dolje
	{
		metciProtivnik[i].Pomakni();
		if (metciProtivnik[i].DohvatiKoordinatuY() >= maxKoordinataY)
			metciProtivnik.erase(metciProtivnik.begin() + i);
	}
}

void Igra::ProvjeraSudaraIgracAlien()
{
	std::vector<Alien> aliens = izvanzemaljci.DohvatiAliens();
	sf::IntRect igracArea = igrac.DohvatiPravokutnik();
	for (size_t i = 0; i<aliens.size(); i++)
	{
		if (igracArea.intersects(aliens[i].DohvatiPravokutnik()))
		{
			igrac.PostaviIzgubio(true);
			break;
		}
	}
}

void Igra::ProvjeraSudaraPreprekaAlien() // ako se izvanzemaljci zalete u prepreku ona se unistava
{
	size_t i, j;
	for (i = 0; i < izvanzemaljci.DohvatiAliens().size(); i++)
	{
		for (j = 0; j < prepreke.size(); j++)
		{
			if (prepreke[j].DohvatiPravokutnik().intersects(izvanzemaljci.DohvatiAliens()[i].DohvatiPravokutnik()))
			{
				prepreke.erase(prepreke.begin() + j);
				j--;
				break;
			}
		}
	}
}


void Igra::ProvjeraSudaraMetakaPrepreka()
{
	size_t i = 0;
	while (i < metciIgrac.size())
	{
		size_t j = 0;
		bool metakIzbrisan = false;
		while (j < prepreke.size())
		{
			if (metciIgrac[i].DohvatiPravokutnik().intersects(prepreke[j].DohvatiPravokutnik()))
			{
				prepreke[j].PovecajBrojUdaraca();
				//std::cout << "Pogodena prepreka: " << j + 1 << " Broj udaraca sada: " << prepreke[j].DohvatiBrojUdaraca() << std::endl;
				metciIgrac.erase(metciIgrac.begin() + i);
				metakIzbrisan = true;
				if (prepreke[j].DohvatiBrojUdaraca() == 8)
				{
					prepreke.erase(prepreke.begin() + j);
				}
				else
				{
					j++;
				}
				break;
			}
			else
			{
				j++;
			}
		}
		if (!metakIzbrisan)
		{
			i++;
		}
	}

	i = 0;
	while (i < metciProtivnik.size())
	{
		size_t j = 0;
		bool metakIzbrisan = false;
		while (j < prepreke.size())
		{
			if (metciProtivnik[i].DohvatiPravokutnik().intersects(prepreke[j].DohvatiPravokutnik()))
			{
				prepreke[j].PovecajBrojUdaraca();
				//std::cout << "Pogodena prepreka: " << j + 1 << " Broj udaraca sada: " << prepreke[j].DohvatiBrojUdaraca() << std::endl;
				metciProtivnik.erase(metciProtivnik.begin() + i);
				metakIzbrisan = true;
				if (prepreke[j].DohvatiBrojUdaraca() == 8)
				{
					prepreke.erase(prepreke.begin() + j);
				}
				else
				{
					j++;
				}
				break;
			}
			else
			{
				j++;
			}
		}
		if (!metakIzbrisan)
		{
			i++;
		}
	}
}


void Igra::ProvjeraSudaraMetaka()
{
	size_t i, j;
	for (i = 0; i < metciIgrac.size(); i++)
	{
		for (j = 0; j < metciProtivnik.size(); j++)
		{
			if (metciIgrac[i].DohvatiPravokutnik().intersects(metciProtivnik[j].DohvatiPravokutnik()))
			{
				metciIgrac.erase(metciIgrac.begin() + i);
				metciProtivnik.erase(metciProtivnik.begin() + j);
				--i;
				--j;
				break;
			}
		}
	}
}

void Igra::ProvjeraSudaraMetakAlien()
{
	size_t i, j;
	for (i = 0; i < metciIgrac.size(); i++)
	{
		for (j = 0; j < izvanzemaljci.DohvatiAliens().size(); j++)
		{
			if (izvanzemaljci.DohvatiAliens()[j].DohvatiPravokutnik().intersects(metciIgrac[i].DohvatiPravokutnik()))
			{
				igrac.PovecajBodove(izvanzemaljci.DohvatiAliens()[j].DohvatiBodove());
				//std::cout << "Trenutni bodovi: " << igrac.DohvatiBodove() << std::endl;
				metciIgrac.erase(metciIgrac.begin() + i);
				izvanzemaljci.DohvatiAliens().erase(izvanzemaljci.DohvatiAliens().begin() + j);
				i--;
				j--;
				break;
			}
		}
	}
}

void Igra::ProvjeraSudaraMetakIgrac()
{
	size_t i;
	int brojZivota;
	for (i = 0; i < metciProtivnik.size(); i++)
	{
		if (igrac.DohvatiPravokutnik().intersects(metciProtivnik[i].DohvatiPravokutnik()))
		{
			igrac.SmanjiBrojZivota();
			brojZivota = igrac.DohvatiBrojZivota();
			if (brojZivota == 0)
			{
				std::cout << "Izgubio si." << std::endl;
				igrac.PostaviIzgubio(true);
				break;
			}
			//std::cout << "Broj zivota: " << igrac.DohvatiBrojZivota() << std::endl;
			metciProtivnik.erase(metciProtivnik.begin() + i);
			i--;
		}
	}
}

int Igra::ProcitajHighscore()
{
	const std::string filename = "highscore.txt";
	int h = 0;
	std::ifstream infile(filename);
	if (infile.is_open()) {
		infile >> h;
		infile.close();
	}
	else {
		std::cout << "Greska pri otvaranju datoteke za citanje." << std::endl;
	}
	return h;
}

void Igra::ZapisiHighscore()
{
	const std::string filename = "highscore.txt";

	int score = igrac.DohvatiBodove();
	if (score > highscore)
	{
		std::ofstream outfile(filename);
		if (outfile.is_open()) {
			outfile << score;
			outfile.close();
			std::cout << "Novi highscore napisan u file: " << score << std::endl;
		}
		else {
			std::cout << "Greska pri otvaranju datoteke za pisanje." << std::endl;
		}
	}
}

void Igra::InicijalizirajPrepreke()
{
	size_t i = 0;
	int razmak = maxKoordinataX / 6; // 40:6 = 6 kvadratica izmedu prepreka
	int sirina = 3; // sirina prepreke je 3*velicinaBloka
	for (i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			Prepreka prep(velicinaBloka, razmak - 1, maxKoordinataY-6);
			prepreke.push_back(prep);
		}
		else
		{
			Prepreka prep(velicinaBloka, i*sirina + (i+1)*razmak, maxKoordinataY-6);
			prepreke.push_back(prep);
		}
	}
}
void Igra::Reset()
{
	igrac.Reset();
	if (!unisteniSvi)
	{
		InicijalizirajPrepreke();
		highscore = ProcitajHighscore();
	}
	izvanzemaljci.DohvatiAliens().clear();
	izvanzemaljci.Reset(unisteniSvi);
	unisteniSvi = false;
}

Igra::Igra() : p("Space Invaders", sf::Vector2u(1280, 800)),
velicinaBloka(32.f),
maxKoordinataX(p.dohvatiVelicinu().x/velicinaBloka),
maxKoordinataY(p.dohvatiVelicinu().y/velicinaBloka),
izvanzemaljci(velicinaBloka, maxKoordinataX, maxKoordinataY),
igrac(velicinaBloka, maxKoordinataX, maxKoordinataY),
unisteniSvi(false),
brzinaMetka(20)
{
	teksturaMapa.loadFromFile("mapa.jpg");
	spriteMapa.setTexture(teksturaMapa);

	font.loadFromFile("arial.ttf");
	scoreText.setFont(font);
	highscoreText.setFont(font);
	scoreText.setCharacterSize(16); 
	highscoreText.setCharacterSize(16); 
	scoreText.setStyle(sf::Text::Bold);
	highscoreText.setStyle(sf::Text::Bold);
	scoreText.setFillColor(sf::Color::White);
	highscoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(maxKoordinataX/2*velicinaBloka, velicinaBloka/2);
	highscoreText.setPosition(velicinaBloka/2, velicinaBloka / 2);

	highscore = ProcitajHighscore();
	//std::cout << "Trenutni highscore: " << highscore << std::endl;
	highscoreText.setString("Highscore: " + std::to_string(highscore));
	scoreText.setString("Score: " + std::to_string(igrac.DohvatiBodove()));

	InicijalizirajPrepreke();
}

Igra::~Igra() {}
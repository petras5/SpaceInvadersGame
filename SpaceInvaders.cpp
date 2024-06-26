#include <iostream>
#include <SFML/Graphics.hpp>
#include "Igra.h"

using namespace std;

int main() {
	Igra igra;
	while (!igra.dohvatiProzor()->jelGotov()) {
		igra.obradiUlaz();
		igra.update();
		igra.renderiraj();
		igra.restartSataAliens();
		igra.restartSataIgrac();
		igra.restartSataMetci();
	}
	return 0;
}
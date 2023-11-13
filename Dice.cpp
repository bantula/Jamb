#include "Dice.h"
#include <cstdlib>
#include <ctime> // Ova dva zaglavlja koristim samo da vrednost kockice bude random
#include <iostream>
using namespace std;

Dice::Dice()
{
	value = 1;
	keep = false;
}

Dice::~Dice() {}

void Dice::throwDice()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	value = rand() % 6 + 1; // Generise broj između 1 i 6, dodaje se jedan jer je ostatak od 0 do 5
}

void Dice::printDice()
{;
	cout << "Kockica je pala na: " << value << endl;
}

int Dice::getValue()
{
	return value;
}

void Dice::setValue(int value)
{
	this->value = value;
}

void Dice::setKeep(bool keep)
{
	this->keep = keep;
}

bool Dice::getKeep()
{
	return this->keep;
}

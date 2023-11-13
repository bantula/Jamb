#include "Throw.h"
#include "Dice.h"
#include <iostream>
using namespace std;

Throw::Throw()
{
	for (int i = 0; i < DICE_COUNT; i++)
	{
		d[i].setValue(1); // Može bilo koja vrednost od 1 do 6
	}
	throwCount = 0;
}

Throw::~Throw(){}

void Throw::throwDice() // Baca kockice
{
	if (throwCount == 3)
	{
		cout << "You must write in the table first" << endl;
		return;
	}

	if (throwCount == 0)
	{
		for (int i = 0; i < DICE_COUNT; i++)
		{
			d[i].setKeep(false);
		}
	}

	for (int i = 0; i < DICE_COUNT; i++)
	{
		if (d[i].getKeep() == false)
		{
			d[i].throwDice();
		}
	}
	for (int i = 0; i < DICE_COUNT; i++)
	{
		d[i].setKeep(false);
	}

	printDice();
	addThrowCount();
}

void Throw::setDice(int dice[]) // Postavlja vrednosti kockica
{
	for (int i = 0; i < DICE_COUNT; i++)
	{
		d[i].setValue(dice[i]);
	}
	addThrowCount();
}

bool Throw::keepDice(bool dice[]) // Postavlja koje kockice treba da se zadrže
{
	for (int i = 0; i < DICE_COUNT; i++)
	{
		if (dice[i] != 1 && dice[i] != 0)
		{
			cout << "You must have 5 options" << endl;
			return false;
		}
	}
	if (dice[DICE_COUNT] == 1 || dice[DICE_COUNT] == 0)
	{
		cout << "You must have 5 options" << endl;
		return false;
	}

	for (int i = 0; i < 5; i++)
	{
		d[i].setKeep(dice[i]);
	}
	
	return true;
}

void Throw::printDice() // Ispisuje vrednosti kockica
{
	for (int i = 0; i < DICE_COUNT; i++)
	{
		d[i].printDice();
	}
}

void Throw::addThrowCount() // Povećava broj bacanja
{
	throwCount++;
}

void Throw::resetThrowCount() // Resetuje broj bacanja
{
	throwCount = 0;
}

int Throw::getThrowCount()
{
	return throwCount;
}

int Throw::getDiceValues(int dice)
{
	return d[dice].getValue();
}

#include "Game.h"
#include <iostream>
#define DICE_COUNT 5
using namespace std;

Game::Game()
{
	Table();
	Throw();
}

Game::~Game() {}

void Game::load(string table)
{
	table1.load(table);
}

string Game::save()
{
	return table1.save();
}

void Game::restart()
{
	table1.restart();
}

void Game::throwDice()
{
	throw1.throwDice();
}

void Game::setDice(int dice[])
{
	throw1.setDice(dice);
}

bool Game::keepDice(bool dice[])
{
	return throw1.keepDice(dice);
}

void Game::printChoices()
{
	if (throw1.getThrowCount() == 0) {
		cout << "You must throw the dice first!" << endl;
		return;
	}
	int dice[DICE_COUNT];
	for (int i = 0; i < DICE_COUNT; i++)
	{
		dice[i] = throw1.getDiceValues(i);
	}

	string bigString = table1.printChoises(dice, throw1.getThrowCount());

	table1.printBigString(bigString);
}

bool Game::writeResult(int choise)
{
	bool check = true;
	string temp = "";
	int dice[DICE_COUNT];
	for (int i = 0; i < 15; i++)
	{
		if (table1.getFieldValues(i) != 0) {
			check = false;
		}
	}
	if (check == true) {
		for (int i = 0; i < DICE_COUNT; i++)
		{
			dice[i] = throw1.getDiceValues(i);
		}
		temp = table1.printChoises(dice, throw1.getThrowCount());
	}
	bool b = table1.writeResult(choise);
	if (b) {
		throw1.resetThrowCount();
	}
	return b;
}

void Game::printResults()
{
	table1.printResults();
}

void Game::printDiceValues(int dice)
{
	cout << throw1.getDiceValues(dice) << endl;
}

int Game::getScore()
{	
	return table1.getScore();
}

bool Game::isGameOver()
{
	return table1.isGameOver();
}

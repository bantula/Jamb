#ifndef GAME_H
#define GAME_H
#include "Table.h"
#include "Throw.h"


class Game: public Table, public Throw
{
public:
	Game();
	~Game();

	void load(string table);
	string save();
	void restart();
	void throwDice();
	void setDice(int dice[]);
	bool keepDice(bool dice[]);
	void printChoices();
	bool writeResult(int choise);
	void printResults();
	void printDiceValues(int dice);

	int getScore();
	bool isGameOver();

private:

	Table table1;
	Throw throw1;
};

#endif // !GAME_H
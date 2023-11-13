#ifndef THROW_H
#define THROW_H
#include "Dice.h"
#define DICE_COUNT 5

class Throw
{
public:
	Throw();
	~Throw();

	void throwDice();
	void setDice(int dice[]);
	bool keepDice(bool dice[]);
	void printDice();

	void addThrowCount();
	void resetThrowCount();
	int getThrowCount();
	int getDiceValues(int dice);
private:
	Dice d[DICE_COUNT]; // Niz 5 kockica
	int throwCount;
};

#endif // !THROW_H


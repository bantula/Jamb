#ifndef DICE_H
#define DICE_H

class Dice
{
public:
	Dice();
	~Dice();

	void throwDice();
	void printDice();

	int getValue();
	void setValue(int value);
	void setKeep(bool keep);
	bool getKeep();

private:
	int value;
	bool keep;
};

#endif //DICE_H

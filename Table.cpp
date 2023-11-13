#include "Table.h"
#include "Throw.h"
#include <string>
using namespace std;
#include <iostream>

Table::Table() { // -1 mi je bila oznaka da u tom polju nije upisana vrednost, to vidim samo ja
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COLUMN_COUNT; j++)
		{
			matrix[i][j] = -1;
		}
	}

	for (int i = 0; i < ROW_COUNT + 2; i++)
	{
		fieldValues[i] = 0;
	}
}

Table::~Table() {}

void Table::load(string table) //Možda sam mogao jednostavnije (preko klase Polje) ali je bilo prekasno kad sam shvatio
{
	restart();
	if (!checkFormat(table)) {
		cout << "Format error" << endl;
		return;
	}
	int k = 0;
	int j = 0;
	for (int i = 0; i < ROW_COUNT; i++)
	{
		while (table[k] != '\n') {
			switch (table[k])
			{
			case ',':
				switch (j)
				{
				case 0:
					matrix[i][j] = -1;
					j++;
					break;
				case 1:
					if (table[k - 1] == ',') {
						matrix[i][j] = -1;
						j++;
					}
					break;
				case 2:
					if (table[k + 1] == '\n') {
						matrix[i][j] = -1;
						j++;
					}
					break;
				}
				break;

			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				if (matrix[i][j] == -1) {
					matrix[i][j] = table[k] - '0';
					if (table[k + 1] < '0' || table[k + 1] > '9') {
						j++;
					}
				}
				else
				{
					matrix[i][j] = matrix[i][j] * 10 + (table[k] - '0');
					j++;
				}
				
				if (table[k + 1] >= '0' && table[k + 1] <= '9' && table[k + 2] >= '0' && table[k + 2] <= '9') {
					cout << "Value error" << endl;
					return;
				}
				break;

			default:
				cout << "Format or Value error" << endl;
				return;
			}
			k++;
		}
		k++;
		j = 0;
	}
	checkValues();
	if (!checkColumn()) {
		cout << "Column error" << endl;
		return;
	}
}

string Table::save() // Ovde se vidi kako sam prelazio preko -1
{
	string s;
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COLUMN_COUNT; j++)
		{
			if (j == 0 || j == 1) {
				if (matrix[i][j] == -1) {
					s += ",";
				}
				else {
					s += to_string(matrix[i][j]) + ",";
				}
				
			}
			else {
				if (matrix[i][j] == -1) {
					s += "\n";
				}
				else {
					s += to_string(matrix[i][j]) + "\n";
				}
			}
		}
	}
	return s;
}

void Table::printResults() // ... kao i ovde
{
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COLUMN_COUNT; j++)
		{

			if (j == 0 || j == 1) {
				if (matrix[i][j] == -1) {
					cout << ",";
				}
				else {
					cout << matrix[i][j] << ",";
				}
			}
			else {
				if (matrix[i][j] == -1) {
					cout << '\n';
				}
				else {
					cout << matrix[i][j] << '\n';
				}
			}
		}
	}
}

void Table::restart()
{
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COLUMN_COUNT; j++)
		{
			matrix[i][j] = -1;
		}
	}
}

string Table::printChoises(int dice[], int throwCount) // Ovde mi vraca string zato sto mora ova funkcija da se pokrene,
{// a vi to niste uradili u Test 4 -_- pa sam morao da se snadjem
	int k = 0;
	string arrayOfStrings[15];
	for (int i = 0; i < ROW_COUNT; i++)
	{
		if (matrix[i][0] == -1) {
			arrayOfStrings[k] = "Down ";
			arrayOfStrings[k] += whichRowAndValue(i, k, dice, throwCount);
			k++;
			break;
		}
	}
	for (int i = 12; i >= 0; i--)
	{
		if (matrix[i][2] == -1) {
			arrayOfStrings[k] = "Up ";
			arrayOfStrings[k] += whichRowAndValue(i, k, dice, throwCount);
			k++;
			break;
		}
	}
	for (int i = 0; i < ROW_COUNT; i++)
	{
		if (matrix[i][1] == -1) {
			arrayOfStrings[k] = "Free ";
			arrayOfStrings[k] += whichRowAndValue(i, k, dice, throwCount);
			k++;
		}
	}
	string bigString = "";
	for (int i = 0; i < (sizeof(arrayOfStrings) / sizeof(arrayOfStrings[0])); i++)
	{
		bigString = bigString + to_string(i) + ":" + arrayOfStrings[i];
	}
	return bigString;
}

void Table::printBigString(string bigString) //Razlog što sam napravio ovu funkciju se vidi u Game.cpp
{
	cout << bigString << endl;
}

bool Table::writeResult(int choise)
{
	if (choise < 0) {
		cout << "Choise error" << endl;
		return false;
	}

	int k = 0;
	for (int i = 0; i < ROW_COUNT; i++)
	{
		if (matrix[i][0] == -1) {
			if (choise == k) {
				matrix[i][0] = getFieldValues(k);
				return true;
			}
			k++;
			break;
		}
	}
	for (int i = 12; i >= 0; i--)
	{
		if (matrix[i][2] == -1) {
			if (choise == k) {
				matrix[i][2] = getFieldValues(k);
				return true;
			}
			k++;
			break;
		}
	}
	for (int i = 0; i < ROW_COUNT; i++)
	{
		if (matrix[i][1] == -1) {
			if (choise == k) {
				matrix[i][1] = getFieldValues(k);
				return true;
			}
			k++;
		}
	}
	cout << "Choise error" << endl;
	return false;
}

bool Table::checkColumn()
{
	bool check = true;

	for (int i = 0; i < ROW_COUNT; i++)
	{
		if (matrix[i][0] < 0) {
			check = false;
		}
		if (matrix[i][0] >= 0 && check == false) {
			return false;
		}
	}
	check = true;
	for (int i = 12; i >= 0; i--)
	{
		if (matrix[i][2] < 0) {
			check = false;
		}
		if (matrix[i][2] >= 0 && check == false) {
			return false;
		}
	}
	return true;
}

bool Table::checkFormat(string table)
{
	int comma = 0;
	int newLine = 0;

	for (int i = 0; i < table.length(); i++)
	{
		if (table[i] == ',') {
			comma++;
		}
		if (table[i] == '\n') {
			newLine++;
			if (comma != 2) {
				return false;
			}
			comma = 0;
		}
	}
	if (newLine != ROW_COUNT) {
		return false;
	}
	return true;
}

bool Table::checkValues()
{
	bool check = false;
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COLUMN_COUNT; j++)
		{
			if (matrix[i][j] == -1) {
				continue;
			}
			switch (i)
			{
			case 0: case 1: case 2: case 3: case 4: case 5:
				if (matrix[i][j] % (i + 1) != 0 || matrix[i][j] > (i + 1) * 5) {
					cout << "Value error" << endl;
					return false;
				}
				break;
			case 6:
				if (matrix[i][j] > 30) {
					cout << "Value error" << endl;
					return false;
				}
				break;
			case 7:
				if (matrix[i][j] < 5) {
					cout << "Value error" << endl;
					return false;
				}
				break;
			case 8:
				if (matrix[i][j] != 66 && matrix[i][j] != 56 && matrix[i][j] != 46 && matrix[i][j] != 0) {
					cout << "Value error" << endl;
					return false;
				}
				break;
			case 9:
				if ((matrix[i][j] - 20) % 3 != 0 || matrix[i][j] > 38) {
					cout << "Value error" << endl;
					return false;
				}
				break;
			case 10:
				for (int k = 1; k <= 5; k++)
				{
					for (int l = k + 1; l <= 6; l++)
					{
						if ((matrix[i][j] - 30) == 2 * k + 3 * l || (matrix[i][j] - 30) == 2 * l + 3 * k) {
							check = true;
							break;
						}
					}
				}
				if (check == false) {
					cout << "Value error" << endl;
					return false;
				}
				break;
			case 11:
				if ((matrix[i][j] - 40) % 4 != 0 || matrix[i][j] > 64) {
					cout << "Value error" << endl;
					return false;
				}
				break;
			case 12:
				if ((matrix[i][j] - 50) % 5 != 0 || matrix[i][j] > 80) {
					cout << "Value error" << endl;
					return false;
				}
				break;
			}check = false;
		}
	};
	return true;
}

string Table::whichRowAndValue(int row, int k, int dice[], int throwCount) // Ispisuje ime polja i vrednost koja moze na njemu da se upise
{
	int howMany = 0;
	int value = 0;
	switch (row)
	{
	case 0:
		for (int i = 0; i < 5; i++)
		{
			if (dice[i] == 1) {
				value++;
			}
		}
		setFieldValues(value, k);
		return "Ones " + to_string(value) + "\n";
	case 1:
		for (int i = 0; i < 5; i++)
		{
			if (dice[i] == 2) {
				value += 2;
			}
		}
		setFieldValues(value, k);
		return "Twos " + to_string(value) + "\n";
	case 2:
		for (int i = 0; i < 5; i++)
		{
			if (dice[i] == 3) {
				value += 3;
			}
		}
		setFieldValues(value, k);
		return "Threes " + to_string(value) + "\n";
	case 3:
		for (int i = 0; i < 5; i++)
		{
			if (dice[i] == 4) {
				value += 4;
			}
		}
		setFieldValues(value, k);
		return "Fours " + to_string(value) + "\n";
	case 4:
		for (int i = 0; i < 5; i++)
		{
			if (dice[i] == 5) {
				value += 5;
			}
		}
		setFieldValues(value, k);
		return "Fives " + to_string(value) + "\n";
	case 5:
		for (int i = 0; i < 5; i++)
		{
			if (dice[i] == 6) {
				value += 6;
			}
		}
		setFieldValues(value, k);
		return "Sixes " + to_string(value) + "\n";

	case 6:
		for (int i = 0; i < 5; i++)
		{
			value += dice[i];
		}
		setFieldValues(value, k);
		return "Max " + to_string(value) + "\n";
	case 7:
		for (int i = 0; i < 5; i++)
		{
			value += dice[i];
		}
		setFieldValues(value, k);
		return "Min " + to_string(value) + "\n";

	case 8:
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5 - i - 1; j++) {
				if (dice[j] > dice[j + 1]) {
					int temp = dice[j];
					dice[j] = dice[j + 1];
					dice[j + 1] = temp;
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if ((i + 1) == dice[i]) {
				howMany++;
			}
		}
		if (howMany == 5) {
			switch (throwCount)
			{
			case 1:
				value = 66;
				break;
			case 2:
				value = 56;
				break;
			case 3:
				value = 46;
				break;
			}
		}
		setFieldValues(value, k);
		return "Straight " + to_string(value) + "\n";
	case 9:
		for (int i = 0; i < 4; i++)
		{
			for (int j = i + 1; j < 5; j++)
			{
				if (dice[i] == dice[j]) {
					howMany++;
				}
			}
			if (howMany >= 3) {
				value = 3 * dice[i] + 20;
			}
		}
		setFieldValues(value, k);
		return "Three of a kind " + to_string(value) + "\n";
	case 10:
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5 - i - 1; j++) {
				if (dice[j] > dice[j + 1]) {
					int temp = dice[j];
					dice[j] = dice[j + 1];
					dice[j + 1] = temp;
				}
			}
		}
		if (dice[0] == dice[1] && dice[2] == dice[3] && dice[2] == dice[4]) {
			if (dice[0] != dice[4]) {
				value = 2 * dice[0] + 3 * dice[2] + 30;
			}
		}
		if (dice[0] == dice[1] && dice[0] == dice[2] && dice[3] == dice[4]){
			if (dice[0] != dice[4]) {
				value = 2 * dice[3] + 3 * dice[0] + 30;
			}
		}
		setFieldValues(value, k);
		return "Full house " + to_string(value) + "\n";
	case 11:
		for (int i = 0; i < 4; i++)
		{
			for (int j = i + 1; j < 5; j++)
			{
				if (dice[i] == dice[j]) {
					howMany++;
				}
			}
			if (howMany >= 3) {
				value = 4 * dice[i] + 40;
			}
			else {
				howMany = 0;
			}
		}
		setFieldValues(value, k);
		return "Poker " + to_string(value) + "\n";
	case 12:
		for (int i = 1; i < 5; i++)
		{
			if (dice[0] == dice[i]) {
				howMany++;
			}
		}
		if (howMany == 4) {
			value = 5 * dice[0] + 50;
		}
		setFieldValues(value, k);
		return "Yamb " + to_string(value) + "\n";
	};
}

int Table::getScore()
{
	int score = 0;
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COLUMN_COUNT; j++)
		{
			if (matrix[i][j] != -1 && i != 6 && i != 7) {
				score += matrix[i][j];
			}
		}
	}
	for (int j = 0; j < COLUMN_COUNT; j++) {
		if (matrix[0][j] != -1 && matrix[6][j] != -1 && matrix[7][j] != -1){
			score += (matrix[6][j] - matrix[7][j]) * matrix[0][j];
		}
	}

	return score;
}

bool Table::isGameOver()
{
	for (int i = 0; i < ROW_COUNT; i++)
	{
		for (int j = 0; j < COLUMN_COUNT; j++)
		{
			if (matrix[i][j] == -1) {
				return false;
			}
		}
	}
	return true;
}

void Table::setFieldValues(int fieldValue, int k)
{
	fieldValues[k] = fieldValue;
}

int Table::getFieldValues(int k)
{
	return fieldValues[k];
}

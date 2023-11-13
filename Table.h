#ifndef TABLE_H
#define TABLE_H
#include <string>
#define ROW_COUNT 13
#define COLUMN_COUNT 3
using namespace std;

class Table
{
public:
	Table();
	~Table();

	void load(string table);
	string save();
	void printResults();
	void restart();
	string printChoises(int dice[], int throwCount);
	void printBigString(string bigString);
	bool writeResult(int choise);
	int getScore();
	bool isGameOver();
	void setFieldValues(int fieldValue, int k);
	int getFieldValues(int k);

private:
	bool checkColumn();
	bool checkFormat(string table);
	bool checkValues();
	string whichRowAndValue(int row, int k, int dice[], int throwCount);

	int fieldValues[ROW_COUNT + 2]; //Ovde sam pisao vrednosti koje mogu da se upisu za određeni choise
	int matrix[ROW_COUNT][COLUMN_COUNT];
};

#endif // !TABLE_H


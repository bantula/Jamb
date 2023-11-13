// Ovde ukljuciti Vase fajlove
#include "Game.h"
#include "tst.h"
#include "Table.h"
#include <iostream>
#include <string>
using namespace std;

// forward declare tested types
class Game;

int main(int argc, char const* argv[]) {
	using namespace std;
	int pts = 0;

	// This test simulates the game
	pts += Test0::tst<Game>();
	pts += Test1::tst<Game>();
	pts += Test2::tst<Game>();
	pts += Test3::tst<Game>();
	pts += Test4::tst<Game>();


	std::cout << "Points: " << pts << std::endl;

	/*Game g;
	string s = "5,3,\n8,,\n9,,\n20,16,\n,,\n,,\n,25,\n,7,\n,56,\n,,35\n,,48\n,,56\n,,70\n";
	g.load(s);
	string s1 = g.save();
	cout << s1;
	cout << "Hello World!" << endl;*/
	//g.printResults();

	/*Game game;
	int dice[] = { 1, 1, 2, 1, 5 };
	game.setDice(dice);
	bool rr[] = { true, false, false, true, false};
	game.keepDice(rr);
	game.throwDice();
	cout << game.save();*/


	return 0;
}

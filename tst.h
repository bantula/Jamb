#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
using namespace std;

// check if type is defined, forward declarations are not definitions
template <class, class = void>
struct is_defined : std::false_type {};
template <class T>
struct is_defined<
	T, std::enable_if_t<std::is_object<T>::value &&
	!std::is_pointer<T>::value && (sizeof(T) > 0)>>
	: std::true_type {};

namespace Test1 {

	template <class, class = void>
	struct is_defined_method : std::false_type {};

	template <class Game>
	struct is_defined_method<
		Game,
		std::enable_if_t<
		std::is_same<decltype(Game()), Game>::value&&
		std::is_same<decltype(std::declval<Game>().load(std::declval<string>())), void>::value&&
		std::is_same<decltype(std::declval<Game>().save()), string>::value
		>
	> : std::true_type {};

	template <class Game>
	int tst() {
		if constexpr (is_defined<Game>::value && is_defined_method<Game>::value) {
			std::stringstream in, out;

			in << "5,3,\n8,,\n9,,\n20,16,\n,,\n,,\n,25,\n,7,\n,56,\n,,35\n,,48\n,,56\n,,70\n";

			Game game;
			game.load(in.str());
			out << game.save();

			if (out.str() == "5,3,\n8,,\n9,,\n20,16,\n,,\n,,\n,25,\n,7,\n,56,\n,,35\n,,48\n,,56\n,,70\n") {
				std::cout << "Test passed" << std::endl;
				return 25;
			}
			else {
				std::cout << "Test failed" << std::endl;
			}
		}
		else {
			std::cout << "Interface failed" << std::endl;
		}
		return 0;
	}
}

namespace Test2 {

	template <class, class = void>
	struct is_defined_method : std::false_type {};

	template <class Game>
	struct is_defined_method<
		Game,
		std::enable_if_t<
		std::is_same<decltype(Game()), Game>::value&&
		std::is_same<decltype(std::declval<Game>().load(std::declval<string>())), void>::value&&
		std::is_same<decltype(std::declval<Game>().restart()), void>::value&&
		std::is_same<decltype(std::declval<Game>().save()), string>::value
		>
	> : std::true_type {};

	template <class Game>
	int tst() {
		if constexpr (is_defined<Game>::value && is_defined_method<Game>::value) {
			std::stringstream in, out;

			in << "5,3,\n8,,\n9,,\n20,16,\n,,\n,,\n,25,\n,7,\n,56,\n,,35\n,,48\n,,56\n,,70\n";

			Game game;
			game.load(in.str());
			game.restart();
			out << game.save();

			if (out.str() == ",,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n") {
				std::cout << "Test passed" << std::endl;
				return 25;
			}
			else {
				std::cout << "Test failed" << std::endl;
			}
		}
		else {
			std::cout << "Interface failed" << std::endl;
		}
		return 0;
	}
}

namespace Test3 {

	template <class, class = void>
	struct is_defined_method : std::false_type {};

	template <class Game>
	struct is_defined_method <
		Game,
		std::enable_if_t <
		std::is_same<decltype(Game()), Game>::value&&
		std::is_same<decltype(std::declval<Game>().load(std::declval<string>())), void>::value&&
		std::is_same<decltype(std::declval<Game>().getScore()), int> ::value
		>
	> : std::true_type {};

	template <class Game>
	int tst() {
		if constexpr (is_defined<Game>::value && is_defined_method<Game>::value) {
			std::stringstream in, out;

			in << "5,3,\n8,,\n9,,\n20,16,\n,,\n,,\n,25,\n,7,\n,56,\n,,35\n,,48\n,,56\n,,70\n";

			Game game;
			game.load(in.str());
			out << game.getScore();

			if (out.str() == "380") {
				std::cout << "Test passed" << std::endl;
				return 25;
			}
			else {
				std::cout << "Test failed" << std::endl;
			}
		}
		else {
			std::cout << "Interface failed" << std::endl;
		}
		return 0;
	}
}

namespace Test4 {

	template <class, class = void>
	struct is_defined_method : std::false_type {};

	template <class Game>
	struct is_defined_method <
		Game,
		std::enable_if_t <
		std::is_same<decltype(Game()), Game>::value&&
		std::is_same<decltype(std::declval<Game>().setDice(std::declval<int[]>())), void>::value&&
		std::is_same<decltype(std::declval<Game>().writeResult(std::declval<int>())), bool> ::value&&
		std::is_same<decltype(std::declval<Game>().save()), string>::value
		>
	> : std::true_type {};

	template <class Game>
	int tst() {
		if constexpr (is_defined<Game>::value && is_defined_method<Game>::value) {
			std::stringstream out;

			Game game;
			int dice[] = {1, 1, 2, 1, 5};
			game.setDice(dice);
			game.writeResult(0);
			out << game.save();

			if (out.str() == "3,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n,,\n") {
				std::cout << "Test passed" << std::endl;
				return 25;
			}
			else {
				std::cout << "Test failed" << std::endl;
			}
		}
		else {
			std::cout << "Interface failed" << std::endl;
		}
		return 0;
	}
}

namespace Test0 {

	template <class, class = void>
	struct is_defined_method : std::false_type {};

	template <class Game>
	struct is_defined_method <
		Game,
		std::enable_if_t <
		std::is_same<decltype(Game()), Game>::value&&
		std::is_same<decltype(std::declval<Game>().restart()), void>::value&&
		std::is_same<decltype(std::declval<Game>().throwDice()), void>::value&&
		std::is_same<decltype(std::declval<Game>().keepDice(std::declval<bool[]>())), bool>::value&&
		std::is_same<decltype(std::declval<Game>().printChoices()), void>::value&&
		std::is_same<decltype(std::declval<Game>().writeResult(std::declval<int>())), bool> ::value&&
		std::is_same<decltype(std::declval<Game>().printResults()), void>::value&&
		std::is_same<decltype(std::declval<Game>().getScore()), int> ::value&&
		std::is_same<decltype(std::declval<Game>().isGameOver()), bool> ::value
		>
	> : std::true_type{};

	template <class Game>
	int tst() {
		if constexpr (is_defined<Game>::value && is_defined_method<Game>::value) {

			Game game;
			bool exitGame = false; 
			int choice;
			cout << "Welcome!" << endl;
			while (!game.isGameOver() && !exitGame) {
				cout << "Write your choice and press ENTER." << endl;
				while(true) {
					cout << "1. Start new game" << endl
						<< "2. Exit game" << endl
						<< "3. Throw dice" << endl;
					cin >> choice;
					if (choice < 1 || choice > 3) {
						std::cout << "Invalid choice. Try again." << endl;
						continue;
					}
					break;
				}
				switch (choice) {
				case 1: 
					cout << "Blank table loaded..." << endl; game.restart(); break;
				case 2: 
					cout << "Goodbye!" << endl; exitGame = true; break;
				case 3: 
					cout << "Throwing dice..." << endl;
					cout << "Dice: " << endl; game.throwDice(); cout << endl;
					cout << "Choices: " << endl; game.printChoices(); cout << endl;
					for (int i = 1; i <= 2; i++) {
						cout << "Do you want to:" << endl;
						while (true) {
							cout << "1. Write result" << endl
								<< "2. Keep dice and throw again" << endl;
							cin >> choice;
							if (choice < 1 || choice > 2) {
								std::cout << "Invalid choice. Try again." << endl;
								continue;
							}
							break;
						}
						if (choice == 1) break;
						if (choice == 2) {
							bool diceToKeep[] = { false, false, false, false, false };
							cout << "Enter positions of dice you want to keep. Enter invalid position to continue." << endl;
							cin >> choice;
							while(choice >= 0 && choice <= 5) {
								diceToKeep[choice] = true;
								cin >> choice;
							}
							game.keepDice(diceToKeep);
							cout << "Throwing dice..." << endl;
							cout << "Dice: " << endl; game.throwDice(); cout << endl;
							cout << "Choices: " << endl; game.printChoices(); cout << endl;
						}
					}
					cout << "Where do you want to write the result?" << endl;
					cin >> choice;
					while (!game.writeResult(choice)) {
						std::cout << "Invalid position. Try again." << endl;
						cin >> choice;
					}
					cout << endl;
					game.printResults();
					cout << "Current score: " << game.getScore() << endl << endl;
					break;
				}
			}
			std::cout << "Test passed" << std::endl;
		}
		else {
			std::cout << "Interface failed" << std::endl;
		}
		return 0;
	}
}
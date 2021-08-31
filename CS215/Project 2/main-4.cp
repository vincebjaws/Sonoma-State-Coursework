/* Sample test file for Project 3
 */
#include <iostream>
#include "constants.hpp"
#include "player.hpp"
#include "game.hpp"
#include <string>

// You may modify this file to include other header files
using namespace std;

int main() {
	int num_rounds=0;	// number of rounds per game - chosen by user
	string tmp;		// to collect user input after "press any key"
	Game g;	// object for the game being played - will reset after each game

	// Ask the user how many rounds
	// If they give an invalid input or input is <= 0, exit
	cout << "How many rounds do you want to play?\n";
	cin >> num_rounds;
	cin.get();
	if (num_rounds <= 0) {
		return 0;
	}

	// Loop over all combinations of player strategies and print game report
	for (int p1_strategy=0; p1_strategy < NUM_STRATEGIES; p1_strategy++) {
		for (int p2_strategy=0; p2_strategy < NUM_STRATEGIES; 
			p2_strategy++) {
			cout << endl;
			g.Reset(possible_strategies[p1_strategy],
				possible_strategies[p2_strategy]);
			for (int i=1; i <= num_rounds; i++) {
				g.PlayTurn();
				//g.TurnReport(cout, i);
			}
			cout << g;
			cout << "Press ENTER to continue: ";
			getline(cin, tmp);			
		}
	
	}

	return 0;
}

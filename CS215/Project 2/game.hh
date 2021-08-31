//Vince Bjazevic
//Project 2
#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>
#include <string>
#include <vector>
#include "constants.hpp"
#include "player.hpp"

using namespace std;
/* Definition of Game class 
 * You may add to the private section
 */
class Game {
public:
	/* You MUST define the following functions */
	Game();
	// initialize player strategies
	Game(string p1_strategy, string p2_strategy);
	Game(const Game& p);
	~Game();	
	Game& operator = (const Game& p);

	// Play another round -- record each player's decision
	void PlayTurn();

	// Print the results of an individual turn (see sample output)
	void TurnReport(ostream& outs, int round_num) const;

	// Reinitialize list of turns
	void Reset();

	// Reinitialize game and player strategies
	void Reset(string p1_strategy, string p2_strategy);

	// Print game report (see sample output)
	// Need to print each player's strategy,
	// the turn report for every turn,
	// and the total sentences
	friend ostream& operator << (ostream& outs, const Game& g);

private:
	// Use these variables for the players
	// Do NOT change the data type
        Player* player1;
        Player* player2;
        vector<Turn> MoveHistory;
        void Sentence(Turn& newTurn, Decision player1_decision, Decision player2_decision);
        // You need a dynamic structure to store all of the previous decisions and outcomes this game            
        // You can use a linked list, a dynamic array, a vector...
};



#endif

//Vince Bjazevic
//Project 2
#include "constants.hpp"
#include "game.hpp"
#include <vector>
#include <string>
#include "player.hpp"


Game::Game()  {// Default Constructor
  player1 = new Player();
  player2 = new Player();
}



Game::Game(string p1_strategy, string p2_strategy)  { // Alt Constructor 
  player1 = new Player(p1_strategy);
  player2 = new Player(p2_strategy);
}


Game::Game(const Game& p)  { // Copy constructor
  player1 = new Player(p.player1->GetStrategy());
  player2 = new Player(p.player2->GetStrategy());
}


Game::~Game()  {//Deconstructor
  delete player1;
  delete player2;
  MoveHistory.clear();
}


Game& Game::operator = (const Game& p)  { //Assignment Operator
  player1 = p.player1;
  player2 = p.player2;
  return *this;
}


//Plays the turn and adds the turn to a vector of a MoveHistory
//Turn contains the values of score and player choice
void Game::PlayTurn()  {
  Turn NextTurn;
  if(MoveHistory.size() == 0) {
    NextTurn.p1_decision = player1->MakeNextDecision(UNKNOWN, MoveHistory.size());
    NextTurn.p2_decision = player2->MakeNextDecision(UNKNOWN, MoveHistory.size()); 
  }
  else {// Every other round
    NextTurn.p1_decision = player1->MakeNextDecision(MoveHistory[MoveHistory.size()-1].p2_decision, MoveHistory.size());
    NextTurn.p2_decision = player2->MakeNextDecision(MoveHistory[MoveHistory.size()-1].p1_decision, MoveHistory.size());
  }
  Sentence(NextTurn, NextTurn.p1_decision, NextTurn.p2_decision);
  MoveHistory.push_back(NextTurn);
}


//Turn report outs the turn as well as all information of each turn
void Game:: TurnReport(ostream& outs, int round_num) const  {

  outs << "*************** TURN " << round_num+1 << " *****************";
  if((MoveHistory[round_num]).p1_decision == SNITCH)
    outs << endl << "Player 1: snitch";
  else
    outs << endl << "Player 1: silent";
  if((MoveHistory[round_num]).p2_decision == SNITCH)
    outs << endl << "Player 2: snitch";
  else
    outs << endl << "Player 2: silent";
  outs << endl << endl;
  outs << "Player 1's total sentence: " << MoveHistory[round_num].p1_total << endl;
  outs << "Player 1's total sentence: " << MoveHistory[round_num].p2_total << endl;
}
  

void Game:: Reset()  {// Resets the Move history and set round to one
  MoveHistory.clear();
}



void Game::Reset(string p1_strategy, string p2_strategy)  { // sets new strategies
  delete player1;
  delete player2;
  player1 = new Player(p1_strategy);
  player2 = new Player(p2_strategy);
  Reset();
}

// Prints game reports and player strategies, as well as calculates the total
ostream& operator << (ostream& outs, const Game& g)  { 
  
  outs << "****************************************"  
       << endl << "GAME REPORT" << endl <<"Player 1 strategy:" 
       << g.player1->GetStrategy() << endl << "Player 2 strategy:"
       << g.player2->GetStrategy() << endl;
    
  float total_1 = 0;
  float total_2 = 0;
  for(int i = 0; i < g.MoveHistory.size(); i++) {
    g.TurnReport(outs, i);
    total_1 += (g.MoveHistory[i]).p1_total;
    total_2 += (g.MoveHistory[i]).p2_total;
  }
  outs << "****************************************" << endl //prints the totals
       << "Player 1's total sentence: " << total_1  << endl
       << "Player 2's total sentence: " << total_2  << endl;
					      
  return outs;
}

// Sentence gets the sentence of each turn based on player decision
void Game::Sentence(Turn& newTurn, Decision player1_decision, Decision player2_decision) {
  if(player1_decision == player2_decision) {
    if(player1_decision == SNITCH) {
      newTurn.p1_total = sentence_if_both_snitch;
      newTurn.p2_total = sentence_if_both_snitch;
    }
    else { // if player 1 is silent
      newTurn.p1_total = sentence_if_both_silent;
      newTurn.p2_total = sentence_if_both_silent;
    }
  }
  else if(player1_decision == SNITCH) {
    newTurn.p1_total = sentence_for_lone_snitch;
    newTurn.p2_total = sentence_for_lone_silent;
  }
  else { // if player 1 is silent
    newTurn.p2_total = sentence_for_lone_snitch;
    newTurn.p1_total = sentence_for_lone_silent;
  }
}




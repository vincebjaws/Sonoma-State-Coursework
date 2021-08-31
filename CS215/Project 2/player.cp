//Vince Bjazevic
//Project 2
#include "player.hpp"
#include "game.hpp"

using namespace std;

Player::Player() { //Default constructor
  strategy = "";
}

Player::Player(string desired_strategy)  { //Secondary Constructor
  strategy = desired_strategy;   
}

Player::Player(const Player& p)  { // Copy constructor
  strategy = p.strategy;
}

Player::~Player() { // Destructor
  strategy = "";
}


Player& Player::operator = (const Player& p)  { // Assignment Operator
  strategy = p.strategy;
  return *this;
}


//This function makes the next decision based on the strategy of the
//player.
Decision Player::MakeNextDecision(Decision choice, int turns)  {
  if(strategy == "ALWAYS_SNITCH") return SNITCH;
  if(strategy == "ALWAYS_SILENT") return SILENT;
  if(strategy == "TIT_FOR_TAT") { // Snitches if the opponent snitches previous turn
    if(choice == UNKNOWN) return SILENT; // Unknown as there is no previous turn
    if(choice == SNITCH) 
      return SNITCH;
    else 
      return SILENT;
  }
  
  if(strategy == "SPECIAL")  { // The special strategy returns snitch on even turns and silent on odd
      int remainder = turns % 2;
      if(remainder == 0)
	return SNITCH;//snitch
      if(remainder == 1)
	return SILENT;//silent
  }
}

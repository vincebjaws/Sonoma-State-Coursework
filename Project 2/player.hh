//Vince Bjazevic
//Project 2
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "constants.hpp"
#include <string>

class Player {

public:


        Player(); 
        Player(string desired_strategy); // initialize strategy
        Player(const Player& p);
        ~Player();
        Player& operator = (const Player& p);
        string GetStrategy() const {return strategy;}  // accessor function for strategy
        Decision MakeNextDecision(Decision choice, int turns);

private:
        string strategy; // should be one of the possible_strategies from constants.h	
};

#endif 

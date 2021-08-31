//Vince Bjazevic
//Project 2
#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <iostream>
using namespace std;

// Data type for a player's decision in each round
enum Decision { SILENT, SNITCH, UNKNOWN };

// Prison sentences for different combinations of choices
const float sentence_if_both_snitch = 5;
const float sentence_if_both_silent = 0.5;

// If the one snitches and the other doesn't...
const float sentence_for_lone_silent = 10; // this is the silent one's sentence
const float sentence_for_lone_snitch = 0;  // this is the snitch's sentence

// The possible strategies
const int NUM_STRATEGIES = 4;
const string possible_strategies[NUM_STRATEGIES] = {"ALWAYS_SNITCH", "ALWAYS_SILENT", "TIT_FOR_TAT", "SPECIAL"};

// Struct for players' decisions on a given turn - you don't have to use this
struct Turn {
       Decision p1_decision;
       Decision p2_decision;
       float p1_total;
       float p2_total;
};

#endif

#ifndef MISC_ENTITYINSTANCE_HPP
#define MISC_ENTITYINSTANCE_HPP

#include "JSONToken.hpp"
#include "Pair.hpp"
#include <string>

class EntityInstance {
public:
    void addAttribute(Pair &newPair);
    int numAttributes();
    std::vector<std::string> &attributeNames();
    void print();   // prints this object
    std::string getID();
    double getGrade();
    double getPrev();
    double getCurr();

private:
    std::vector<Pair> entityAttributes;
    std::vector<std::string> _attributeNames;
    int _numAttributes;

};


#endif //MISC_ENTITYINSTANCE_HPP
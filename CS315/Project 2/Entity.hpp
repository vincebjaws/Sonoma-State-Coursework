#ifndef MISC_ENTITY_HPP
#define MISC_ENTITY_HPP
#include "EntityInstance.hpp"
#include <vector>


class Entity {
public:
    void addObject(EntityInstance &);
    void print();
    Entity intersection(Entity & entity2);
    void createMatrix();
    int createCord(double gpa);
    void writeMatrix();
    double getPrev();
    double getCurr();
private:
    std::vector<EntityInstance> instances;
    int prevCord;
    int currCord;
};


#endif //MISC_ENTITY_HPP
#include "Entity.hpp"
#include <iostream>



void Entity::addObject(EntityInstance &newEntity) {
    instances.push_back(newEntity);
}

void Entity::print() {
    std::cout << '[' << std::endl;
    for (int i = 0; i < instances.size(); i++)
        instances[i].print();
    std::cout << ']' << std::endl;
}

void Entity::createMatrix() {
    std::ofstream outputStream ("result.json", std::ofstream::out);
    int matrix[8][8];
    outputStream <<'[' << std::endl;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            matrix[i][j] = 0;
    for(auto & instance : instances) {
        double currentGpa = instance.getCurr();
        double previousGpa = instance.getPrev();
        matrix[createCord(previousGpa)][createCord(currentGpa)]++;
    }
    for (int i = 0; i < 8; ++i) {
        outputStream <<'[';
        for (int j = 0; j < 8; ++j) {
            if(j == 7)
                outputStream << matrix[i][j];
            else
                outputStream << matrix[i][j] << "," << ' ';
        }
        if(i == 7)
            outputStream <<']' << std::endl;
        else
            outputStream <<']' << ',' << std::endl;
    }
    outputStream <<']' << std::endl;
}

int Entity::createCord(double GPA) {
    if(GPA <= 1.67)
        return 7;
    if(GPA <= 2.0)
        return 6;
    if(GPA <= 2.3)
        return 5;
    if(GPA <= 2.67)
        return 4;
    if(GPA <= 3.0)
        return 3;
    if(GPA <= 3.3)
        return 2;
    if (GPA <= 3.67)
        return 1;
    return 0;
}

double Entity::getPrev() { return prevCord; }
double Entity::getCurr() { return currCord;}

Entity Entity::intersection(Entity &otherEntity) {
    Entity intersection;
    for (auto &instance : instances) {
        std::string ID1 = instance.getID();
        for (auto &instances2 : otherEntity.instances) {
            if (ID1 != instances2.getID())
                continue;
            EntityInstance newInstance;
            Pair previousGpa = Pair("previousGpa", instance.getGrade());
            Pair currentGpa = Pair("currentGpa", instances2.getGrade());
            newInstance.addAttribute(currentGpa);
            newInstance.addAttribute(previousGpa);
            intersection.addObject(newInstance);
        }
    }
    return intersection;
}
#include "EntityInstance.hpp"
#include <iostream>

void EntityInstance::addAttribute(Pair &newPair) {
    entityAttributes.push_back(newPair);
    _attributeNames.push_back(newPair.attributeName());
}

int EntityInstance::numAttributes() {
    if(_attributeNames.size() == 0)
        _numAttributes = 0;
    _numAttributes = _attributeNames.size();
    return _numAttributes;
}

//std::vector<std::string> & EntityInstance::attributeNames() {}

void EntityInstance::print() {
    std::cout<<'{'<<std::endl;
    for(int i = 0; i<entityAttributes.size(); i++) {
        std::cout << entityAttributes[i].attributeName() << " : ";
        if (entityAttributes[i].isDouble())
            std::cout << entityAttributes[i].numberValue() << "," << std::endl;
        else
            std::cout << entityAttributes[i].stringValue() << "," << std::endl;
    }
    std::cout<<'}'<<std::endl;
}

std::string EntityInstance::getID() {
    for(int i=0; entityAttributes.size()!=i; i++){
        if(entityAttributes[i].attributeName()=="id")
            return entityAttributes[i].stringValue();
    }
    return "";
}


double EntityInstance::getGrade(){
    for(int i=0; entityAttributes.size()!=i; i++){
        if(entityAttributes[i].attributeName()=="gpa")
            return entityAttributes[i].numberValue();
    }
    return -1;
}


double EntityInstance::getPrev() {
    return entityAttributes[1].numberValue();
}

double EntityInstance::getCurr(){
    return entityAttributes[0].numberValue();
}

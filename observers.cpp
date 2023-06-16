//
// Created by Gabi on 25.05.2023.
//
#include "observers.h"

#include <algorithm>
#include "observers.h"

void Observable::addInteresat(Observer *el) {
    //std::cout<<"ADAUGAT\n";
    this->interesati.push_back(el);
}

void Observable::removeInteresat(Observer *el) {
    //std::cout<<"STERS\n";
    auto it = std::find_if(interesati.begin(), interesati.end(), [el](Observer* other){
       return el == other;
    });
    interesati.erase(it);
}


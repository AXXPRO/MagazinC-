//
// Created by Gabi on 08.04.2023.
//

#ifndef MAGAZINC___VALIDATOR_H
#define MAGAZINC___VALIDATOR_H
#include "../Domain/domain.h"


class ValidatorProdus{

    ///Throws exception if produs isn't valid
public:
   static void isValid(const Produs&);

};



#endif //MAGAZINC___VALIDATOR_H

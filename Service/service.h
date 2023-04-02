//
// Created by Gabi on 02.04.2023.
//

#ifndef MAGAZINC___SERVICE_H
#define MAGAZINC___SERVICE_H
#include "../Repository/repo.h"
#include <iostream>

class Service{



private:

    Repo REPO;
public:
    Service(Repo& REPO):REPO{REPO} {};
    void adaugare_produs_service(std::string nume, std::string tip, std::string producator, float pret);

    ///Returneaza un vector cu produsele
    std::vector<Produs> afisare_produse_service();

};

#endif //MAGAZINC___SERVICE_H

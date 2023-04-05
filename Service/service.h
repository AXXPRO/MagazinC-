//
// Created by Gabi on 02.04.2023.
//

#ifndef MAGAZINC___SERVICE_H
#define MAGAZINC___SERVICE_H
#include "../Repository/repo.h"
#include <iostream>

using std::string;
class Service{



private:

    Repo<Produs>& REPO;
public:
    Service(Repo<Produs>& REPO):REPO{REPO}{};
    void adaugare_produs_service(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret);

    ///Returneaza un vector cu produsele
    std::vector<Produs> afisare_produse_service () const;

    ///Functia sterge produsul cu numele dat prin parametru, sau arunca exceptie
    void delete_service(const string&);
    ///Functia cauta produsul cu numele dat prin parametru, returneaza referinta la el, sau arunca exceptie
     Produs cauta_service(const string&);
     ///Functia modifica produsul dat prin nume, sau arunca exceptie
     void modifica_service(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret);
};




#endif //MAGAZINC___SERVICE_H

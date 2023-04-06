//
// Created by Gabi on 02.04.2023.
//

#include "service.h"
#include <iostream>
#include "../Lista/lista.h"
void Service::adaugare_produs_service(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret) {

    Produs produs = Produs(nume, tip,producator,pret);

    ///VALDIARE

    REPO.append(produs);

}

Iterator<Produs> Service::afisare_produse_service() const
{

    return REPO.get_all();
}

void Service::modifica_service(const string &nume,const std::string& tip, const std::string& producator, const float& pret) {

    Produs produs = Produs(nume, tip,producator,pret);
    REPO.modify(nume, produs);
}

void Service::delete_service(const string& nume) {

REPO.erase(nume);

}

 const Produs& Service::cauta_service(const string &nume) {

    return REPO.search(nume);

}
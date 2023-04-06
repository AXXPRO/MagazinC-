//
// Created by Gabi on 02.04.2023.
//

#include "service.h"
#include <iostream>
void Service::adaugare_produs_service(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret) {

    Produs produs = Produs(nume, tip,producator,pret);

    ///VALDIARE

    REPO.adaugare_produs(produs);

}

const std::vector<Produs>& Service::afisare_produse_service() const
{

    return REPO.get_all();
}

void Service::modifica_service(const string &nume,const std::string& tip, const std::string& producator, const float& pret) {

    Produs produs = Produs(nume, tip,producator,pret);
    REPO.modifica_element(nume, produs);
}

void Service::delete_service(const string& nume) {

REPO.delete_element(nume);

}

 const Produs& Service::cauta_service(const string &nume) {

    return REPO.cauta_element(nume);

}
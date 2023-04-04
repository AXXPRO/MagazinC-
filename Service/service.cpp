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

std::vector<Produs> Service::afisare_produse_service() const
{
    std::vector<Produs> lista_returnat = REPO.get_all();
    return lista_returnat;
}

void Service::delete_service(const string& nume) {

REPO.delete_element(nume);

}

 Produs Service::cauta_service(const string &nume) {

    return REPO.cauta_element(nume);

}
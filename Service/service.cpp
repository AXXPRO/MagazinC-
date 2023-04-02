//
// Created by Gabi on 02.04.2023.
//

#include "service.h"
#include <iostream>
void Service::adaugare_produs_service(std::string nume, std::string tip, std::string producator, float pret) {

    Produs produs = Produs(nume, tip,producator,pret);

    ///VALDIARE

    REPO.adaugare_produs(produs);

}

std::vector<Produs> Service::afisare_produse_service()
{
    std::vector<Produs> lista_returnat = REPO.get_all();
    return lista_returnat;
}
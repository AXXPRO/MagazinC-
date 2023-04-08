//
// Created by Gabi on 02.04.2023.
//
#include "../Domain/domain.h"
#include "service.h"
#include <iostream>
#include "../Lista/lista.h"
#include "../Validator/validator.h"
void Service::adaugare_produs_service(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret) {

    Produs produs = Produs(nume, tip,producator,pret);


    ///VALDIARE
    ValidatorProdus::isValid(produs);
    REPO.append(produs);

}

Iterator<Produs> Service::afisare_produse_service() const
{

    return REPO.get_all();
}

void Service::modifica_service(const string &nume,const std::string& tip, const std::string& producator, const float& pret) {

    Produs produs = Produs(nume, tip,producator,pret);
    ValidatorProdus::isValid(produs);
    REPO.modify(nume, produs);
}


string Service::getValue(const Produs& prod, int camp_sortare){

    switch (camp_sortare) {
        case 1:
            return prod.getNume();

        case 2:
            return std::to_string(prod.getPret());
            case 3:
            return prod.getNume() + prod.getTip();}}

Iterator<Produs>Service::sortare_service(ListaRepo<Produs>& lista_returnat, int camp_sortare)
{


    Iterator<Produs> it = REPO.get_all();

    string smallest_possible = "";
    string current_element;
    bool sorting = true;
    while(sorting)
    { it.prim();
        sorting = false;

        while(it.valid())
        {
            if(getValue(it.element(), camp_sortare) > smallest_possible)
            {
                sorting = true;
                current_element = getValue(it.element(), camp_sortare);
                break;
            }
            it.urmator();
        }
        if(!sorting)
            break;
        it.prim();

        while(it.valid())
        {

            if( getValue(it.element(), camp_sortare) < current_element  &&  getValue(it.element(), camp_sortare) > smallest_possible)
            {
                current_element = getValue(it.element(), camp_sortare);
            }

            it.urmator();
        }

        it.prim();
        while(it.valid())
        {

            if( getValue(it.element(), camp_sortare) == current_element)
            {
               lista_returnat.append(it.element());
            }

            it.urmator();
        }
        smallest_possible = current_element;
    }

    return lista_returnat.get_all();





}

Iterator<Produs>Service::filtrare_service(ListaRepo<Produs>& lista_returnat,int camp_filtrat, string filtru)
{

    Iterator<Produs> it = REPO.get_all();
    string value;
    float value_float;

    while(it.valid())
    {
        switch (camp_filtrat) {
            case 1:
                value_float = it.element().getPret();
                if(value_float == std::stof(filtru))
                {lista_returnat.append(it.element());}
                break;

            case 2:
                value = it.element().getNume();
                if(value == filtru)
                {lista_returnat.append(it.element());}
                break;

            case 3:
                value = it.element().getProducator();
                if(value == filtru)
                {lista_returnat.append(it.element());}
                break;
            default:
                throw ValidatorError("Parametrii incorecti!\n");

        }




        it.urmator();
    }


    return lista_returnat.get_all();
}


void Service::delete_service(const string& nume) {

REPO.erase(nume);

}

 const Produs& Service::cauta_service(const string &nume) {

    return REPO.search(nume);

}
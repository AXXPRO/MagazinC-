//
// Created by Gabi on 02.04.2023.
//

#include "repo.h"
void Repo::adaugare_produs(const Produs &element) {

    lista.push_back(element);
}
int Repo::numar_elemente() const
{
    return lista.size();
}

Produs Repo::cauta_element(const std::string nume)const{


    for(auto el:lista)
    {
        if(el.getNume() == nume)
            return el;

    }
    throw std::exception();

}

void Repo::modifica_element(const std::string nume, const Produs& other)
{

    for(int i=0; i<lista.size(); i++)
    {
        if(lista[i].getNume() == nume)
        {
            lista[i].setProducator(other.getProducator());
            lista[i].setTip(other.getTip());
            lista[i].setPret(other.getPret());

            return;
        }

    }
    throw std::exception();

}
std::vector<Produs> Repo::get_all() {
    std::vector<Produs> lista_returnat;
    for (auto el: lista) {
        lista_returnat.push_back(el);
    }
    return lista_returnat;
}
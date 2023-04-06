//
// Created by Gabi on 02.04.2023.
//

#include "repo.h"
using std::string;
using std::vector;


void Repo::adaugare_produs(const Produs& element) {

    lista.push_back(element);
}
int Repo::numar_elemente() const
{
    return (int)lista.size();
}

const Produs& Repo::cauta_element(const string& nume)const{


    for(const auto& el:lista)
    {
        if(el.getNume() == nume)
            return el;

    }
    throw std::exception();

}
void Repo::delete_element(const string &nume){

    for(int i=0; i<lista.size(); i++)
    {
        if(lista[i].getNume() == nume)
        {
           lista.erase(lista.begin()+i);
            return;
        }

    }
    throw std::exception();
}


void Repo::modifica_element(const string& nume, const Produs& other)
{
    for (auto& el: lista)
    //for(int i=0; i<lista.size(); i++)
    {
        if(el.getNume() == nume)
        {
            el.setProducator(other.getProducator());
            el.setTip(other.getTip());
            el.setPret(other.getPret());

            return;
        }

    }
    throw std::exception();

}
const vector<Produs>& Repo::get_all()  const{

    return lista;

    /* std::vector<Produs> lista_returnat;
    for (const auto& el: lista) {
        lista_returnat.push_back(el);
    }
    return lista_returnat;
*/}
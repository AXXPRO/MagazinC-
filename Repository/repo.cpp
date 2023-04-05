//
// Created by Gabi on 02.04.2023.
//

#include "repo.h"
using std::string;
using std::vector;

template <typename T>
void Repo<T>::adaugare_produs(const T &element) {

    lista.push_back(element);
}

template <typename T>
int Repo<T>:: numar_elemente() const
{
    return (int)lista.size();
}
template <typename T>
 T Repo<T>::cauta_element(const string& nume)const{


    for(const auto& el:lista)
    {
        if(el.getNume() == nume)
            return el;

    }
    throw std::exception();

}

template <typename T>
void Repo<T>::delete_element(const string &nume){

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

template <typename T>
void Repo<T>::modifica_element(const string& nume, const T& other)
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

template <typename T>
vector<T> Repo<T>::get_all()  const{
    std::vector<Produs> lista_returnat;
    for (const auto& el: lista) {
        lista_returnat.push_back(el);
    }
    return lista_returnat;
}
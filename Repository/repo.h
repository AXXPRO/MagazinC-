//
// Created by Gabi on 02.04.2023.
//

#ifndef MAGAZINC___REPO_H
#define MAGAZINC___REPO_H

#include <iostream>
#include <vector>
#include "../Domain/domain.h"

using std::string;
using std::vector;

template <typename T>
class Repo{

private:
    std::vector<T> lista;

public:
    ///
    /// \return the number of elements currently in the Repo
    int numar_elemente() const;
    ///Adds an ellement
    void adaugare_produs(const T& element);
    ///Returns an object with the given name, or trows exception if none found

   const  T& cauta_element(const string& nume)const;

    /// Modifies the object's attributes(identified by its name) to the ones of the "other" parameter
    ///Trows exception if no object with said name
    void modifica_element(const string& nume, const T& other);

    ///Functia returneaza un vector cu toate elementele din aplicatie
    const vector<T>& get_all() const;

    ///Functia va sterge elementul cu numele dat sau va arunca exceptie
    void delete_element(const string& nume);

};


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
const T& Repo<T>::cauta_element(const string& nume)const{


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
const vector<T>& Repo<T>::get_all()  const{

    return lista;
}

#endif //MAGAZINC___REPO_H

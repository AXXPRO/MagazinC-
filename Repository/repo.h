//
// Created by Gabi on 02.04.2023.
//

#ifndef MAGAZINC___REPO_H
#define MAGAZINC___REPO_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "../Domain/domain.h"
#include "../Erori/errors.h"

using std::string;
using std::vector;

template <typename T>
class Repo{

protected:
    vector<T> lista;

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
     vector<T>&  get_all();


    ///Functia va sterge elementul cu numele dat sau va arunca exceptie
    void delete_element(const string& nume);

};


template <typename T>
void Repo<T>::adaugare_produs(const T &element) {

    auto iter = std::find_if(lista.begin(), lista.end(), [&](T &p){
       return p.getNume() == element.getNume();
    });

    if (iter != lista.end())
    {
        throw RepoError("Element deja existent!\n");
    }
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
    throw RepoError("Element inexistent!\n");

}

template <typename T>
void Repo<T>::delete_element(const string &nume){


    auto iter = std::find_if(lista.begin(), lista.end(), [&](T& p){
        return (p.getNume() == nume);
    });
    if(numar_elemente() ==0 )
    {
        throw RepoError("Lista goala!\n");
    }
    if (iter == lista.end())
    {     throw RepoError("Element inexistent!\n");

    }
    lista.erase(iter);
//    for(int i=0; i<lista.size(); i++)
//    {
//        if(lista[i].getNume() == nume)
//        {
//            lista.erase(lista.begin()+i);
//            return;
//        }
//
//    }
//    throw std::exception();
}

template <typename T>
void Repo<T>::modifica_element(const string& nume, const T& other)
{

    if(numar_elemente() ==0 )
    {
        throw RepoError("Lista goala!\n");
    }

    auto iter = std::find_if(lista.begin(), lista.end(), [&](T& p){
        return (p.getNume() == nume);
    });

    if (iter == lista.end())
    {   throw RepoError("Element inexistent!\n");

    }
    (*iter).setProducator(other.getProducator());
    (*iter).setTip(other.getTip());
    (*iter).setPret(other.getPret());
//    for(int i=0; i<lista.size(); i++)
//    {
//        if(lista[i].getNume() == nume)
//        {
//            lista[i].setProducator(other.getProducator());
//            lista[i].setTip(other.getTip());
//            lista[i].setPret(other.getPret());
//
//            return;
//        }
//
//    }
//  throw std::exception();

}

template <typename T>
vector<T>& Repo<T>::get_all(){

    return lista;
}


template <typename T>
class RepoCos:public Repo<T>{
public:
    void adaugare_produs(const T& element);
};

template <typename T>
void RepoCos<T>::adaugare_produs(const T &element) {

//    int nr_elemente = std::count_if(Repo<T>::lista.begin(),Repo<T>::lista.end(), [&](T& el){
//        return el.getNume()==element.getNume();
//    });
//    if(nr_elemente == 2)
//    {
//        throw RepoError("Maxim 2 elemente cu acelasi nume!");
//    }
    Repo<T>::lista.push_back(element);
}



#endif //MAGAZINC___REPO_H

//
// Created by Gabi on 02.04.2023.
//

#ifndef MAGAZINC___REPO_H
#define MAGAZINC___REPO_H
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "../Domain/domain.h"
#include "../Erori/errors.h"

using std::string;
using std::vector;

template <typename T>
class RepoAbstract
{
public:
    virtual int numar_elemente() const=0;
    ///Adds an ellement
    virtual void adaugare_produs(const T& element)=0;
    ///Returns an object with the given name, or trows exception if none found

    virtual const T& cauta_element(const string& nume)=0;

    /// Modifies the object's attributes(identified by its name) to the ones of the "other" parameter
    ///Trows exception if no object with said name
    virtual void modifica_element(const string& nume, const T& other)=0;

    ///Functia returneaza un vector cu toate elementele din aplicatie
    virtual vector<T>&  get_all()=0;


    ///Functia va sterge elementul cu numele dat sau va arunca exceptie
    virtual void delete_element(const string& nume)=0;
};

template <typename T>
class Repo: public RepoAbstract<T> {

protected:
    vector<T> lista;

public:
    ///
    /// \return the number of elements currently in the Repo
   int numar_elemente() const override;
    ///Adds an ellement
 void adaugare_produs(const T& element) override;
    ///Returns an object with the given name, or trows exception if none found

  const  T& cauta_element(const string& nume) override;

    /// Modifies the object's attributes(identified by its name) to the ones of the "other" parameter
    ///Trows exception if no object with said name
  void modifica_element(const string& nume, const T& other)override;

    ///Functia returneaza un vector cu toate elementele din aplicatie
   vector<T>&  get_all() override;


    ///Functia va sterge elementul cu numele dat sau va arunca exceptie
   void delete_element(const string& nume) override;

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
const T& Repo<T>::cauta_element(const string& nume){


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
    void adaugare_produs(const T& element) override;
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


template <typename T>
class RepoFisier:public Repo<T>{


    private:
        string calea;
    void store();
    void load();


    public:
   RepoFisier(string cale) {
       this->calea = cale;
        load();
    };

    ~RepoFisier(){
        store();
    }

    void adaugare_produs(const T& element) override;
    const T& cauta_element(const string& nume) override;

    void modifica_element(const string& nume, const T& other) override;


    vector<T>& get_all() override;

    void delete_element(const string& nume) override;


    };

template <typename T>
void RepoFisier<T>::adaugare_produs(const T &element)  {

    load();
    Repo<T>::adaugare_produs(element);
    store();

}
template <typename T>
void RepoFisier<T>::modifica_element(const string& nume, const T& other)  {

    load();
    Repo<T>::modifica_element(nume, other);
    store();

}
template <typename T>
const T& RepoFisier<T>:: cauta_element(const string& nume)  {

    load();
   return Repo<T>::cauta_element(nume);


}
template <typename T>
vector<T>& RepoFisier<T>::get_all()  {

    load();
   return Repo<T>::get_all();

}
template <typename T>
void RepoFisier<T>::delete_element(const string& nume)  {

    load();
    Repo<T>::delete_element(nume);
    store();

}
template <typename T>
void RepoFisier<T>::load()
{
    Repo<T>::lista.clear();
    std::ifstream f("../"+calea);
    if (!f.is_open())
    {
        throw RepoError("Fisier inexistent!\n");
    }

    string linie, cuvant;
    vector<string> cuvinte;


    while(!f.eof())
    { cuvinte.clear();
        std::getline(f, linie);


        if(linie != "")
        {
            std::stringstream X(linie);

            while(getline(X, cuvant, ','))
            {
                cuvinte.push_back(cuvant);
            }

            ///nume, tip, producator, pret
            Produs p(cuvinte[0],cuvinte[1],cuvinte[2] , stof(cuvinte[3]));
            Repo<T>::adaugare_produs(p);
        }


    }
    f.close();

}
template <typename T>
void RepoFisier<T>::store()
{
std::ofstream f("../"+calea);
///    if (!f.is_open()) {
   ///     throw RepoError("Fisier inexistent!\n");

    ///}
    for (auto& p:Repo<T>::get_all()) {
       f<<p.to_string()<<std::endl;
    }

    f.close();
}

#endif //MAGAZINC___REPO_H

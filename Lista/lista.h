//
// Created by Gabi on 06.04.2023.
//

#ifndef MAGAZINC___LISTA_H
#define MAGAZINC___LISTA_H
#include "../Erori/errors.h"
#include <iostream>
#include "iterator.h"
using std::string;

template <typename T>
 struct celula{

    celula* urmator;
    T valoarea;
    celula(T val):urmator(NULL) , valoarea(val){};
};


template <typename T> class ListaRepo;

template <typename U>
class Iterator{
    friend class ListaRepo<U>;
private:

    celula<U>* curent;

    const ListaRepo<U>& lista;

public:
    Iterator(const ListaRepo<U>& lis);
   ~Iterator() = default;
    bool valid() const;
    void urmator();
    const U& element();



};

template <typename T>
Iterator<T>::Iterator(const ListaRepo<T>& lis): lista(lis){

    curent = lista.cap;

}
template <typename T>
bool Iterator<T>::valid()const {
    return curent!=NULL;

}

template <typename T>
void Iterator<T>::urmator() {
    if(valid())
    {
        curent = curent->urmator;
    }

}

template <typename T>
const T& Iterator<T>::element() {

    return curent->valoarea;
}


template <typename T>
class ListaRepo{
private:
     friend class Iterator<T>;

    celula<T>* cap;
    int numar_elemente;

public:

    ListaRepo();

    ///copy constructor

    ListaRepo(ListaRepo<T>& o);
    ~ListaRepo();

    //Iterator<T> iterator();
    Iterator<T> get_all() const;

    int len() const;
    const T& search(const string& nume)const;
    void append(const T& element);
    void erase(const string& nume);
    void modify(const string& nume, const T& other);



};
template <typename T>
Iterator<T> ListaRepo<T>::get_all() const{
    return Iterator(*this);
}



template <typename T>
ListaRepo<T>::ListaRepo()
{   cap =NULL;
    numar_elemente = 0;
}



template <typename T>
void ListaRepo<T>::modify(const string &nume, const T &other) {
    if(cap == NULL)
    {
        throw RepoError("Lista goala!\n");
    }
    celula<T>* curent;
    curent = cap;
    if(cap->valoarea.getNume()== nume)
    {
            cap->valoarea.setProducator(other.getProducator());
            cap->valoarea.setTip(other.getTip());
            cap->valoarea.setPret(other.getPret());
        return;

    }

    while(curent!=NULL)
    { if(curent->valoarea.getNume() == nume) {

            curent->valoarea.setProducator(other.getProducator());
            curent->valoarea.setTip(other.getTip());
            curent->valoarea.setPret(other.getPret());
            return;
        }
        curent = curent->urmator;

    }

    throw RepoError("Valoarea nu a fost gasita!\n");

}



template <typename T>
const T& ListaRepo<T>::search(const string& nume)const{
    if(cap == NULL)
    {
        throw RepoError("Lista goala!\n");
    }
    celula<T>* curent;
    curent = cap;
    if(cap->valoarea.getNume()== nume)
    {
        return cap->valoarea;
    }

    while(curent!=NULL)
    { if(curent->valoarea.getNume() == nume) {

            return curent->valoarea;
        }
        curent = curent->urmator;

    }

    throw RepoError("Valaorea nu a fost gasita!\n");

}

template <typename T>
void ListaRepo<T> ::erase(const string &nume) {

    if(cap == NULL)
    {
        throw RepoError("Lista goala!\n");
    }
    celula<T>* curent;
    curent = cap;
    if(cap->valoarea.getNume()== nume)
    {
        cap = cap->urmator;
        delete curent;
        numar_elemente--;
        return;
    }

    celula<T>* predecesor;
    while(curent!=NULL)
    { if(curent->valoarea.getNume() == nume) {
        predecesor->urmator = curent->urmator;
        delete curent;
        numar_elemente--;
            return;

        }
        predecesor = curent;
        curent = curent->urmator;

    }

    throw RepoError("Valaorea nu a fost gasita!\n");

}


template <typename T>
void ListaRepo<T>::append(const T &element) {
    celula<T>* nou = new celula(element);
    nou->urmator = NULL;
    nou->valoarea = element;

    celula<T>* curent;
    curent = cap;
    if(cap == NULL)
    {
        cap = nou;
        numar_elemente++;
        return;
    }
    while(curent->urmator!=NULL)
    { if(curent->valoarea == element) {
            throw RepoError("Produs deja existent!\n");
        }
        curent = curent->urmator;

    }

    if(curent->valoarea.getNume() == element.getNume()) {
        throw RepoError("Produs deja existent!\n");
    }

    curent->urmator = nou;
    numar_elemente++;

    return;


}

template <typename T>
int ListaRepo<T>::len() const{
    return this->numar_elemente;
}


template <typename T>
ListaRepo<T>:: ~ListaRepo(){
    celula<T>* aux1, *aux2;
    if(cap != NULL){
        aux1 = cap;
        aux2 = aux1->urmator;
        while(aux2!=NULL)
        {

            delete aux1;
            aux1 = aux2;
            aux2 = aux1->urmator;
        }

    }


}






#endif //MAGAZINC___LISTA_H

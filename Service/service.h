//
// Created by Gabi on 02.04.2023.
//

#ifndef MAGAZINC___SERVICE_H
#define MAGAZINC___SERVICE_H
#include "../Repository/repo.h"
#include "../Lista/lista.h"
#include <iostream>

using std::string;
class Service{



private:
    ///Return true if a product respects a set of rules


    bool boolSortare(const Produs& p1 ,const Produs& p2, int& camp_sortat);
    bool boolFilter(const Produs&,const int&, const string&) const;
    Repo<Produs>& REPO;
    RepoCos<Produs> REPOCos;
public:
    Service(Repo<Produs>& REPO):REPO{REPO}/* , RepoCos{Repo<Produs>()} */{};
    void adaugare_produs_service(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret);

    ///Returneaza un vector cu produsele
    vector<Produs>& afisare_produse_service () const;

    void export_service (const string&);
    void filtrare_service(vector<Produs>& ,int camp_filtrat, string filtru);

    void sortare_service(vector<Produs>& , int camp_sortare);

    ///Functia sterge produsul cu numele dat prin parametru, sau arunca exceptie
    void delete_service(const string&);
    ///Functia cauta produsul cu numele dat prin parametru, returneaza referinta la el, sau arunca exceptie
    const Produs& cauta_service(const string&);
     ///Functia modifica produsul dat prin nume, sau arunca exceptie
     void modifica_service(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret);


    ///Functions for the the creation of a COS
    void adaugare_cos_service(const string& nume);
    ///Functie ce va golii cosul
    void goleste_cos_servcie();
    ///Functie ce va genera nr_elemente in cos
    void genereaza_cos_service(int);
    ///Functia va returna pretul actual al elementelor din cos
    float pret_cos_service();


};




#endif //MAGAZINC___SERVICE_H

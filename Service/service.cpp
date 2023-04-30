//
// Created by Gabi on 02.04.2023.
//
#include "../Domain/domain.h"
#include "service.h"
#include <iostream>
#include <algorithm>
#include <fstream>

#include <random>

#include <iterator>
#include "../Validator/validator.h"
using std::pair;
using std::map;
void Service::adaugare_produs_service(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret) {

    Produs produs = Produs(nume, tip,producator,pret);

    ///VALDIARE
    ValidatorProdus::isValid(produs);
    REPO.adaugare_produs(produs);

}

vector<Produs>&  Service::afisare_produse_service() const
{

    return REPO.get_all();
}

void Service::modifica_service(const string &nume,const std::string& tip, const std::string& producator, const float& pret) {

    Produs produs = Produs(nume, tip,producator,pret);
    ValidatorProdus::isValid(produs);
    REPO.modifica_element(nume, produs);
}
bool Service::boolSortare(const Produs& p1 ,const Produs& p2, int& camp_sortat)
{ string st1, st2;
    switch (camp_sortat) {
        case 1:
            if(p1.getNume() <=p2.getNume())
                return true;
            return false;

        case 2:
            if(p1.getPret() -p2.getPret() <= 0.00001)
                return true;
            return false;
        case 3:

            st1+=p1.getNume();
            st1+=p1.getTip();
            st2+=p2.getNume();
            st2+=p2.getTip();
            if(st1<=st2)
                return true;
            return false;
        default:
            throw ValidatorError("Parametrii invalizi!\n");

    }

}


void Service::sortare_service(vector<Produs>& filtrat,int camp_sortare)
{
   // 1.Nume
   // 2.Pret
   // 3.Nume + Tip


    vector<Produs> originale = REPO.get_all();
    filtrat = originale;
  std::sort(filtrat.begin(), filtrat.end(),[&](Produs& p1, Produs& p2){
      return boolSortare(p1, p2, camp_sortare);
  });
}


bool Service::boolFilter(const Produs& el ,const int& camp_filtrat,const string& filtru) const
{
    switch (camp_filtrat) {
        case 1:
            if(el.getPret() - stof(filtru) < 0.0001)
                return true;
            return false;

        case 2:
            if(el.getNume() == filtru)
                return true;
            return false;
        case 3:
            if(el.getProducator() == filtru)
                return true;
            return false;
        default:
            throw ValidatorError("Parametrii invalizi!\n");

    }

}
void Service::filtrare_service(vector<Produs>& filtrat,int camp_filtrat, string filtru)
{
   // 1.Pret
   // 2.Nume
   //3.Producator

   vector<Produs> originale = REPO.get_all();

    std::copy_if(originale.begin(), originale.end(), std::back_inserter(filtrat), [&](Produs& el){
        return boolFilter(el ,camp_filtrat, filtru);
    });


}


void Service::delete_service(const string& nume) {

REPO.delete_element(nume);

}

 const Produs& Service::cauta_service(const string &nume) {

    return REPO.cauta_element(nume);

}
void Service::export_service(const string &nume_fisier)
{
    vector<Produs> temp = REPOCos.get_all();

    string true_name;
    true_name+="../";
    true_name+=nume_fisier;
    std::ofstream f(true_name);
    for(const auto& el : temp)
    {
        f<<el<<std::endl;
    }

    f.close();
}

void Service::adaugare_cos_service(const string &nume) {

    Produs P =REPO.cauta_element(nume);
    REPOCos.adaugare_produs(P);
}
void Service::goleste_cos_servcie() {

    vector<Produs> temp = REPOCos.get_all();
    vector<string> temp_string;
    for(auto const& el : temp)
    {   temp_string.push_back(el.getNume());
    }
    for(auto const& el : temp_string)
    {
        REPOCos.delete_element(el);
    }

}

void Service::genereaza_cos_service(int nr_elemente)
{

    this->goleste_cos_servcie();

    vector<Produs> elemente = REPO.get_all();
    vector<string> disponibile;
    for(auto const& el: elemente)
    {
        disponibile.push_back(el.getNume());
        disponibile.push_back(el.getNume());
    }

    while(nr_elemente && disponibile.size())
    {    std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<> dist(0, disponibile.size()-1);
        int rndNr = dist(mt);
        Produs aux = REPO.cauta_element(disponibile[rndNr]);
        REPOCos.adaugare_produs(aux);

        disponibile.erase(disponibile.begin() + rndNr);
        nr_elemente--;
    }


}

float Service::pret_cos_service(){
    float pret = 0;

    for( auto const& el : REPOCos.get_all())
    {
        pret+=el.getPret();
    }
    return pret;
}

void Service::raport_service(map<string, vector<Produs>>& dictionar)
{
    vector<Produs> v = REPO.get_all();
    for(auto const& el : v)
    {
        dictionar[el.getTip()].push_back(el);
    }
}
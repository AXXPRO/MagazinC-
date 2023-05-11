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
    REPO->adaugare_produs(produs);

    ActiuneUndo* act = new UndoAdaugare(REPO, produs);
    lista_undouri.push_back(act);

}

Service::~Service() {

    for(auto el : lista_undouri)
    {
        delete el;
    }
    delete REPO;

    delete REPOCos;
}

void Service::undo_service()
{
    if(lista_undouri.empty())
    {
        throw ValidatorError("Lista de undo goala!\n");
    }

    ActiuneUndo* act = lista_undouri.back();
    act->undo();
    lista_undouri.pop_back();
    delete act;
}


vector<Produs>&  Service::afisare_produse_service() const
{

    return REPO->get_all();
}

void Service::modifica_service(const string &nume,const std::string& tip, const std::string& producator, const float& pret) {

    Produs produs = Produs(nume, tip,producator,pret);
    ValidatorProdus::isValid(produs);

    const Produs p = REPO->cauta_element(nume);
    REPO->modifica_element(nume, produs);


    ActiuneUndo* act = new UndoModificare(REPO, p);
    lista_undouri.push_back(act);
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


    vector<Produs> originale = REPO->get_all();
    filtrat = originale;
  std::sort(filtrat.begin(), filtrat.end(),[&](Produs& p1, Produs& p2){
      return boolSortare(p1, p2, camp_sortare);
  });
}


bool Service::boolFilter(const Produs& el ,const int& camp_filtrat,const string& filtru) const
{
    switch (camp_filtrat) {
        case 1:
            if(abs(el.getPret() - stof(filtru) ) < 0.0001) {
                return true;
            }
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

   vector<Produs> originale = REPO->get_all();

    std::copy_if(originale.begin(), originale.end(), std::back_inserter(filtrat), [&](Produs& el){
        return boolFilter(el ,camp_filtrat, filtru);
    });


}
vector<Produs> Service::sortare_service_GUI(vector<Produs>& inputVector , int camp_sortare)
{
    vector<Produs> originale = inputVector;
    vector<Produs> returnat;

    returnat = originale;
    std::sort(returnat.begin(), returnat.end(),[&](Produs& p1, Produs& p2){
        return boolSortare(p1, p2, camp_sortare);
    });

    return returnat;

}
vector<Produs> Service::filtrare_service_GUI(vector<Produs>& inputVector,int camp_filtrat, string filtru)
{
    // 1.Pret
    // 2.Nume
    //3.Producator
   // std::cout<<camp_filtrat<<filtru<<std::endl;
    vector<Produs> originale = inputVector;
    vector<Produs> returnat;
    std::copy_if(originale.begin(), originale.end(), std::back_inserter(returnat), [&](Produs& el){
        return boolFilter(el ,camp_filtrat, filtru);
    });

  //  for(auto el : returnat)
   // {
    //    std::cout<<el<<" ";
   // }
  //  std::cout<<std::endl;
    return returnat;

}



void Service::delete_service(const string& nume) {


    const Produs p = REPO->cauta_element(nume);
    REPO->delete_element(nume);
    ActiuneUndo* act = new UndoStergere(REPO, p);
    lista_undouri.push_back(act);
}

 const Produs& Service::cauta_service(const string &nume) {

    return REPO->cauta_element(nume);

}
void Service::export_service(const string &nume_fisier)
{
    vector<Produs> temp = REPOCos->get_all();

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

    Produs P =REPO->cauta_element(nume);
    REPOCos->adaugare_produs(P);
}
void Service::goleste_cos_servcie() {

    vector<Produs> temp = REPOCos->get_all();
    vector<string> temp_string;
    for(auto const& el : temp)
    {   temp_string.push_back(el.getNume());
    }
    for(auto const& el : temp_string)
    {
        REPOCos->delete_element(el);
    }

}

void Service::genereaza_cos_service(int nr_elemente)
{

    this->goleste_cos_servcie();

    vector<Produs> elemente = REPO->get_all();
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
        Produs aux = REPO->cauta_element(disponibile[rndNr]);
        REPOCos->adaugare_produs(aux);

        disponibile.erase(disponibile.begin() + rndNr);
        nr_elemente--;
    }


}

float Service::pret_cos_service(){
    float pret = 0;

    for( auto const& el : REPOCos->get_all())
    {
        pret+=el.getPret();
    }
    return pret;
}

void Service::raport_service(map<string, vector<Produs>>& dictionar)
{
    vector<Produs> v = REPO->get_all();
    for(auto const& el : v)
    {
        dictionar[el.getTip()].push_back(el);
    }
}

void Service::raport_service_GUI(map<string, vector<Produs>>& dictionar, vector<Produs> initial)
{
    vector<Produs> v =initial;
    for(auto const& el : v)
    {
        dictionar[el.getTip()].push_back(el);
    }
}
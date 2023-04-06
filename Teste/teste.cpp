//
// Created by Gabi on 30.03.2023.
//
#include "../Domain/domain.h"
#include "teste.h"
#include "../Repository/repo.h"
#include "../Service/service.h"
#include <iostream>
#include <cassert>

///For testing operator<<
#include <sstream>
#include <cstring>

#define epsilon 0.00001

using std::cout;
using std::endl;
void run_all_tests()
{
    teste_domain();
    std::cout<<"Teste domain trecute!\n";
    teste_repo();
    std::cout<<"Teste repo trecute!\n";
    teste_service();
    std::cout<<"Teste service trecute!\n";

}

void teste_service()
{
    Repo<Produs> REPO;
    Service SERVICE(REPO);

    assert(REPO.numar_elemente() == 0);
    SERVICE.adaugare_produs_service("a", "a", "a", 7);
    assert(REPO.numar_elemente() == 1);
     const Produs& produs_cautat = SERVICE.cauta_service("a");
    assert(produs_cautat ==  Produs("a", "a", "a", 7));
  cout<<"!\n";
    std::vector<Produs> list = SERVICE.afisare_produse_service();
    cout<<"!\n";
    assert(list[0] == Produs("a","a","a",7));

    SERVICE.modifica_service("a", "b", "b", 0);
   const Produs& produs_cautat2 = SERVICE.cauta_service("a");
    assert(produs_cautat2 == Produs("a","b","b",0));
    SERVICE.delete_service("a");
    assert(REPO.numar_elemente() == 0);

    std::cout<<std::endl;
}

void teste_repo(){

    Repo<Produs> REPO;
    assert(REPO.numar_elemente() ==0);
    Produs produs1("a","b","b",12.5);


    cout<<"!\n";
    REPO.adaugare_produs(produs1);
    cout<<"!\n";
    assert(REPO.numar_elemente()==1);
    Produs produs2("b","c","d",30);
    REPO.adaugare_produs(produs2);
    Produs produs_cautat = REPO.cauta_element("b");
    assert(produs_cautat == produs2);
    cout<<"!\n";
    try{

       REPO.cauta_element("c");
        assert(false);
    }
    catch (std::exception&){}
    cout<<"!\n";

    Produs produs_modifica("a","modificat","modificat",20);
    try{
        REPO.modifica_element("z", produs_modifica);
        assert(false);
    }
    catch (std::exception&){}

    REPO.modifica_element("a", produs_modifica);
    produs_cautat = REPO.cauta_element("a");
    assert(produs_cautat == produs_modifica);


   const std::vector<Produs>& lista_copie = REPO.get_all();

    assert(lista_copie[0]== Produs("a","modificat","modificat",20));


    REPO.delete_element("a");
    assert(REPO.numar_elemente() ==1);

    try{
         REPO.delete_element("q");
        assert(false);
    }
    catch (std::exception&){}



    std::cout<<std::endl;
}

void teste_domain()
{ Produs produs_test{"Carte", "Copii", "ABC", 50.5};

    std::ostringstream out;
    out<<produs_test;
    std::string nume_string = out.str();
    const char * nume_test = nume_string.c_str();


    assert(strcmp(nume_test, "Nume: Carte Producator: ABC Tip: Copii Pret: 50.5")==0);
    assert(produs_test.getTip()== "Copii");
    assert(produs_test.getNume()== "Carte");
    assert(produs_test.getProducator()== "ABC");
    assert(abs(produs_test.getPret() - 50.5) < epsilon);

    produs_test.setNume("Jucarie");
    produs_test.setPret(99.9);
    produs_test.setProducator("Noriel");
    produs_test.setTip("Adulti");

    assert(produs_test.getTip()== "Adulti");
    assert(produs_test.getNume()== "Jucarie");
    assert(produs_test.getProducator()== "Noriel");
    assert(abs(produs_test.getPret() - 99.9) < epsilon);

    Produs produs_test_diferit("a","a", "aa",-23);
    assert((produs_test == produs_test_diferit)==false);

    const Produs produs_constant("z","z","z", 0);
    assert((produs_constant == produs_test_diferit)==false);


    std::cout<<std::endl;

}
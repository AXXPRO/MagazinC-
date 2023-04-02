//
// Created by Gabi on 30.03.2023.
//
#include "../Domain/domain.h"
#include "teste.h"
#include "../Repository/repo.h"
#include <iostream>
#include <assert.h>

///For testing operator<<
#include <sstream>
#include <cstring>

#define epsilon 0.00001

void run_all_tests()
{
    teste_domain();
    std::cout<<"Teste domain trecute!\n";
    teste_repo();
    std::cout<<"Teste repo trecute!\n";

}

void teste_repo(){

    Repo REPO;
    assert(REPO.numar_elemente() ==0);
    Produs produs1("a","b","b",12.5);
    REPO.adaugare_produs(produs1);
    assert(REPO.numar_elemente()==1);
    Produs produs2("b","c","d",30);
    REPO.adaugare_produs(produs2);
    Produs produs_cautat = REPO.cauta_element("b");
    assert(produs_cautat == produs2);

    try{
        produs_cautat = REPO.cauta_element("c");
        assert(false);
    }
    catch (std::exception){}

    Produs produs_modifica("a","modificat","modificat",20);
    try{
        REPO.modifica_element("z", produs_modifica);
        assert(false);
    }
    catch (std::exception){}

    REPO.modifica_element("a", produs_modifica);
    produs_cautat = REPO.cauta_element("a");
    assert(produs_cautat == produs_modifica);


    std::vector<Produs> lista_copie;
    lista_copie = REPO.get_all();

    assert(lista_copie[0]== Produs("a","modificat","modificat",20));

    lista_copie[0] = Produs("q","modificat","modificat",20);

    try{
        produs_cautat = REPO.cauta_element("q");
        assert(false);
    }
    catch (std::exception){}




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

}
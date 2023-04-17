//
// Created by Gabi on 30.03.2023.
//
#include "../Domain/domain.h"
#include "teste.h"
#include "../Repository/repo.h"
#include "../Service/service.h"
#include "../Lista/lista.h"
#include "../Validator/validator.h"
#include <iostream>
#include <string>
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
    teste_validator();
    std::cout<<"Teste valdiator trecute!\n";

}
void teste_validator()
{
    Produs valid = Produs("a","b","c",2);
    ValidatorProdus validare;
    validare.isValid(valid);
    Produs invalid = Produs("","","",-22);
    std::ostringstream out;
    try{
        validare.isValid(invalid);
        assert(false);
    }catch (ValidatorError& c){ out<<c;
        std::string nume_string = out.str();
        const char * nume_test = nume_string.c_str();

        assert(strcmp(nume_test, "Nume invalid!\nTip invalid!\nProducator invalid!\nPret invalid!\n")==0);}

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
//
//  Iterator<Produs> itr = SERVICE.afisare_produse_service();
//
//  assert(itr.element() ==Produs("a","a","a",7) );



    SERVICE.modifica_service("a", "b", "b", 1);
   const Produs& produs_cautat2 = SERVICE.cauta_service("a");
    assert(produs_cautat2 == Produs("a","b","b",1));
    SERVICE.delete_service("a");
    assert(REPO.numar_elemente() == 0);

    SERVICE.adaugare_produs_service("a", "b", "c", 7);
    SERVICE.adaugare_produs_service("b", "z", "e", 1);
    SERVICE.adaugare_produs_service("c", "z", "c", 9);


//    ListaRepo<Produs> lista_filtrare;
//    SERVICE.filtrare_service(lista_filtrare, 1, "7");
//    Iterator<Produs>itr_filtrare_pret = lista_filtrare.get_all();
//    assert(itr_filtrare_pret.element() == Produs("a", "b", "c", 7));
//
//
//    ListaRepo<Produs> lista_filtrare2;
//    SERVICE.filtrare_service(lista_filtrare2, 2, "a");
//    Iterator<Produs>itr_filtrare_nume = lista_filtrare2.get_all();
//    assert(itr_filtrare_nume.element() == Produs("a", "b", "c", 7));
//
//    ListaRepo<Produs> lista_filtrare3;
//    SERVICE.filtrare_service(lista_filtrare3, 3, "c");
//    Iterator<Produs>itr_filtrare_producator= lista_filtrare3.get_all();
//    assert(itr_filtrare_producator.element() == Produs("a", "b", "c", 7));
//    itr_filtrare_producator.urmator();
//    assert(itr_filtrare_producator.element() == Produs("c", "z", "c", 9));
//
//    try {
//        SERVICE.filtrare_service(lista_filtrare3, 6, "c");
//    }
//    catch (ValidatorError& ) {};
//
//    ListaRepo<Produs> lista_sortata_nume;
//    SERVICE.sortare_service(lista_sortata_nume,1);
//    Iterator<Produs> iterator_sortat_nume = lista_sortata_nume.get_all();
//    assert(iterator_sortat_nume.element() == Produs("a", "b", "c", 7));
//    iterator_sortat_nume.urmator();
//    assert(iterator_sortat_nume.element() == Produs("b", "z", "e", 1));
//    iterator_sortat_nume.urmator();
//    assert(iterator_sortat_nume.element() == Produs("c", "z", "c", 9));
//
//    ListaRepo<Produs> lista_sortata_pret;
//    SERVICE.sortare_service(lista_sortata_pret,2);
//    Iterator<Produs> iterator_sortat_pret = lista_sortata_pret.get_all();
//    assert(iterator_sortat_pret.element() == Produs("b", "z", "e", 1));
//    iterator_sortat_pret.urmator();
//    assert(iterator_sortat_pret.element() == Produs("a", "b", "c", 7));
//    iterator_sortat_pret.urmator();
//    assert(iterator_sortat_pret.element() == Produs("c", "z", "c", 9));
//
//    ListaRepo<Produs> lista_sortata_nume_tip;
//    SERVICE.sortare_service(lista_sortata_nume_tip,3);
//    Iterator<Produs> iterator_sortat_nume_tip = lista_sortata_nume_tip.get_all();
//    assert(iterator_sortat_nume_tip.element() == Produs("a", "b", "c", 7));
//    iterator_sortat_nume_tip.urmator();
//    assert(iterator_sortat_nume_tip.element() == Produs("b", "z", "e", 1));
//    iterator_sortat_nume_tip.urmator();
//    assert(iterator_sortat_nume_tip.element() == Produs("c", "z", "c", 9));
//

}

void teste_repo(){
    Produs Produs1("a","a","a",20);
    Produs Produs2("b","b","b",90);
    Produs Produs3("c","c","c",0);
    Produs Produs4("d","d","d",231);

    ListaRepo<Produs> lista;
    std::ostringstream out;
    assert(lista.len()==0);
    try{
        lista.modify("sa", Produs("a","a","c",23));
        assert(false);
    }catch (RepoError& c) {
        out<<c;
        std::string nume_string = out.str();
        const char * nume_test = nume_string.c_str();

        assert(strcmp(nume_test, "Lista goala!\n")==0);

    }

    try{
        lista.search("dsa");
        assert(false);
    }catch (RepoError& c) {
    }
    try{
        lista.erase("DAS");
        assert(false);
    }catch (RepoError& c) {
    }
    lista.append(Produs1);
    Produs Produs_Cautat1 = lista.search("a");
    assert(Produs_Cautat1 == Produs1);
    assert(lista.len()==1);

    try{
        lista.modify("sa", Produs("a","a","c",23));
        assert(false);
    }catch (RepoError& c) {
    }

    try{
        lista.search("dsa");
        assert(false);
    }catch (RepoError& c) {
    }
    try{
        lista.erase("DAS");
        assert(false);
    }catch (RepoError& c) {
    }
    try{
        lista.append(Produs("a","b","c",2));
        assert(false);
    }catch (RepoError& c) {
    }



    Produs ProdusModifica1("a","a","a",60);
    Produs ProdusModifica2("b","b","b",0);

    lista.modify("a", ProdusModifica1);
    Produs Produs_Cautat_Modificat1 = lista.search("a");
    assert(Produs_Cautat_Modificat1 == ProdusModifica1);


    lista.append(Produs2);
    assert(lista.len()==2);

    try{
        lista.append(Produs("a","b","c",2));
        assert(false);
    }catch (RepoError& c) {
    }


    Produs Produs_Cautat2 = lista.search("b");
    assert(Produs_Cautat2 == Produs2);

    lista.modify("b", ProdusModifica2);
    Produs Produs_Cautat_Modificat2 = lista.search("b");
    assert(Produs_Cautat_Modificat2 == ProdusModifica2);



    lista.append(Produs3);
    assert(lista.len()==3);
    Iterator<Produs> itr = lista.get_all();

    assert(itr.valid() == true);
    assert(itr.element() == ProdusModifica1);
    itr.urmator();
    assert(itr.element() == ProdusModifica2);
    itr.urmator();
    assert(itr.element() == Produs3);
    itr.urmator();
    assert(itr.valid() == false);

    lista.erase("a");
    assert(lista.len()==2);

    lista.erase("c");
    assert(lista.len()==1);
    lista.append(Produs4);
    assert(lista.len()==2);







    /*
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
    */
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
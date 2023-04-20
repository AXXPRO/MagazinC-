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
    teste_cos_service();
    std::cout<<"Teste cos trecute!\n";

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

vector<Produs> itr = SERVICE.afisare_produse_service();
    assert(itr[0]==Produs("a","a","a",7) );




    SERVICE.modifica_service("a", "b", "b", 1);
   const Produs& produs_cautat2 = SERVICE.cauta_service("a");
    assert(produs_cautat2 == Produs("a","b","b",1));
    SERVICE.delete_service("a");
    assert(REPO.numar_elemente() == 0);

    SERVICE.adaugare_produs_service("a", "b", "c", 7);
    SERVICE.adaugare_produs_service("b", "z", "e", 1);
    SERVICE.adaugare_produs_service("c", "z", "c", 9);


   vector<Produs> lista_filtrare;
   SERVICE.filtrare_service(lista_filtrare, 1, "7");

   assert(lista_filtrare[0] == Produs("a", "b", "c", 7));

    vector<Produs> lista_filtrare2;
    SERVICE.filtrare_service(lista_filtrare2, 2, "a");

    assert(lista_filtrare2[0] == Produs("a", "b", "c", 7));

   vector<Produs> lista_filtrare3;
    SERVICE.filtrare_service(lista_filtrare3, 3, "c");

   assert(lista_filtrare3[0] == Produs("a", "b", "c", 7));
    assert(lista_filtrare3[1] == Produs("c", "z", "c", 9));


    try {
        SERVICE.filtrare_service(lista_filtrare3, 6, "c");
    }
    catch (ValidatorError& ) {};

   vector<Produs> lista_sortata_nume;
    SERVICE.sortare_service(lista_sortata_nume,1);

    assert( lista_sortata_nume[0] == Produs("a", "b", "c", 7));

    assert( lista_sortata_nume[1] == Produs("b", "z", "e", 1));

    assert( lista_sortata_nume[2] == Produs("c", "z", "c", 9));

    vector<Produs> lista_sortata_pret;
    SERVICE.sortare_service(lista_sortata_pret,2);

    assert(lista_sortata_pret[0] == Produs("b", "z", "e", 1));

    assert(lista_sortata_pret[1] == Produs("a", "b", "c", 7));

    assert(lista_sortata_pret[2] == Produs("c", "z", "c", 9));

    vector<Produs> lista_sortata_nume_tip;
    SERVICE.sortare_service(lista_sortata_nume_tip,3);

    assert(lista_sortata_nume_tip[0] == Produs("a", "b", "c", 7));

    assert(lista_sortata_nume_tip[1] == Produs("b", "z", "e", 1));

    assert(lista_sortata_nume_tip[2] == Produs("c", "z", "c", 9));

    try{
        SERVICE.sortare_service(lista_sortata_nume_tip,4);
        assert(false);
    }
    catch (ValidatorError& e){};

    SERVICE.adaugare_produs_service("A", "z", "c", 9);
    vector<Produs> lista_sortata_nume2;
    SERVICE.sortare_service(lista_sortata_nume2,1);

    assert( lista_sortata_nume2[0] == Produs("A", "z", "c", 9));
    assert( lista_sortata_nume2[1] == Produs("a", "b", "c", 7));

    vector<Produs> lista_sortata_nume_tip2;
    SERVICE.sortare_service(lista_sortata_nume_tip2,3);

    assert( lista_sortata_nume_tip2[0] == Produs("A", "z", "c", 9));
    assert( lista_sortata_nume_tip2[1] == Produs("a", "b", "c", 7));


}

void teste_cos_service()
{    Repo<Produs> REPO;
    Service SERVICE(REPO);
    Produs Produs1("a","a","a",20);
    Produs Produs2("b","b","b",90);
    Produs Produs3("c","c","c",1);
    REPO.adaugare_produs(Produs1);
    REPO.adaugare_produs(Produs2);
    REPO.adaugare_produs(Produs3);

    SERVICE.adaugare_cos_service("a");
    assert(SERVICE.pret_cos_service() - 20 <= 0.00001);
    SERVICE.adaugare_cos_service("a");
    SERVICE.goleste_cos_servcie();
    assert(SERVICE.pret_cos_service() - 0 <= 0.00001);

    SERVICE.genereaza_cos_service(1);
    assert(SERVICE.pret_cos_service() > 0);

    SERVICE.genereaza_cos_service(6);
    assert(SERVICE.pret_cos_service() - 222 <= 0.00001);

}
void teste_repo(){
    Produs Produs1("a","a","a",20);
    Produs Produs2("b","b","b",90);
    Produs Produs3("c","c","c",0);
    Produs Produs4("d","d","d",231);

   Repo<Produs> lista;
    std::ostringstream out;
    assert(lista.numar_elemente()==0);



    try{
        lista.modifica_element("sa", Produs("a","a","c",23));
        assert(false);
    }catch (RepoError& c) {
        out<<c;
        std::string nume_string = out.str();
        const char * nume_test = nume_string.c_str();

        assert(strcmp(nume_test, "Lista goala!\n")==0);

    }

    try{
        lista.cauta_element("dsa");
        assert(false);
    }catch (RepoError& c) {
    }
    try{
        lista.delete_element("DAS");
        assert(false);
    }catch (RepoError& c) {
    }
    lista.adaugare_produs(Produs1);
    Produs Produs_Cautat1 = lista.cauta_element("a");
    assert(Produs_Cautat1 == Produs1);
    assert(lista.numar_elemente()==1);

    try{
        lista.modifica_element("sa", Produs("a","a","c",23));
        assert(false);
    }catch (RepoError& c) {
    }

    try{
        lista.cauta_element("dsa");
        assert(false);
    }catch (RepoError& c) {
    }
    try{
        lista.delete_element("DAS");
        assert(false);
    }catch (RepoError& c) {
    }
    try{
        lista.adaugare_produs(Produs("a","b","c",2));
        assert(false);
    }catch (RepoError& c) {
    }



    Produs ProdusModifica1("a","a","a",60);
    Produs ProdusModifica2("b","b","b",0);

    lista.modifica_element("a", ProdusModifica1);
    Produs Produs_Cautat_Modificat1 = lista.cauta_element("a");
    assert(Produs_Cautat_Modificat1 == ProdusModifica1);


    lista.adaugare_produs(Produs2);
    assert(lista.numar_elemente()==2);

    try{
        lista.adaugare_produs(Produs("a","b","c",2));
        assert(false);
    }catch (RepoError& c) {
    }


    Produs Produs_Cautat2 = lista.cauta_element("b");
    assert(Produs_Cautat2 == Produs2);

    lista.modifica_element("b", ProdusModifica2);
    Produs Produs_Cautat_Modificat2 = lista.cauta_element("b");
    assert(Produs_Cautat_Modificat2 == ProdusModifica2);



    lista.adaugare_produs(Produs3);
    assert(lista.numar_elemente()==3);
    vector<Produs> temp = lista.get_all();
    assert(temp[2] == Produs3);

//
//    assert(itr.valid() == true);
//    assert(itr.element() == ProdusModifica1);
//    itr.urmator();
//    assert(itr.element() == ProdusModifica2);
//    itr.urmator();
//    assert(itr.element() == Produs3);
//    itr.urmator();
//    assert(itr.valid() == false);

    lista.delete_element("a");
    assert(lista.numar_elemente()==2);

    lista.delete_element("c");
    assert(lista.numar_elemente()==1);
    lista.adaugare_produs(Produs4);
    assert(lista.numar_elemente()==2);

    RepoCos<Produs> REPOCOS;
    assert(REPOCOS.numar_elemente() == 0);
    REPOCOS.adaugare_produs(Produs3);
    assert(REPOCOS.numar_elemente() == 1);






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
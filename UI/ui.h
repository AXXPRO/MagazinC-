//
// Created by Gabi on 02.04.2023.
//

#ifndef MAGAZINC___UI_H
#define MAGAZINC___UI_H
#include "../Service/service.h"


class UI{
private:

    Service& SERVICE;
    //Prints a UI interface
    static void show_ui() ;
    ///Function for adding a Produs to the aplication
    void add_produs_ui();

    ///Functie ui pentru a adauga in cos un element dupa nume
   void adaugare_cos_ui();
    ///Functie ui pentru a golii cosu
   void goleste_cos_ui();
   ///Functia de ui pentru a genera cosu
   void genereaza_cos_ui();

    void pret_cos_ui();

public:
    UI(Service& SERVICE): SERVICE{SERVICE}{};
    ///Function that runs the aplication
    void run_ui();
    ///Va afisa anumite elemente dupa un criteriu
    void filtrare_ui();
    ///Va afisa elementele sortate dupa un criteriu
    void sortare_ui();

    ///Va afisa elementele
    void print_all_ui(vector<Produs> v) const;

    ///Va sterge un element
    void delete_ui();

    ///Va cauta si afisa elementul daca exista
    void cauta_ui();
    ///Va cauta si modifica elementul daca exista
    void modifica_ui();


};

#endif //MAGAZINC___UI_H

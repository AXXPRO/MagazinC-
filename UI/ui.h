//
// Created by Gabi on 02.04.2023.
//

#ifndef MAGAZINC___UI_H
#define MAGAZINC___UI_H
#include "../Service/service.h"


class UI{
private:

    Service SERVICE;
    //Prints a UI interface
    void show_ui() const;
    ///Function for adding a Produs to the aplication
    void add_produs_ui();



public:
    UI(Service SERVICE): SERVICE{SERVICE}{};
    ///Function that runs the aplication
    void run_ui();

    ///Va afisa elementele
    void print_all_ui() const;

    ///Va sterge un element
    void delete_ui();

    ///Va cauta si afisa elementul daca exista
    void cauta_ui();


};

#endif //MAGAZINC___UI_H

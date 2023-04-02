//
// Created by Gabi on 02.04.2023.
//
#include <iostream>
#include "ui.h"

void UI::show_ui() const{

    std::cout<<"Alegeti optiunea dumeavoastra:\n";
    std::cout<<"1.Adaugare de produs\n";
    std::cout<<"4.Afisare de produse\n";
}

void UI::run_ui(){
    std::string input;
    int choice;
    bool running = true;
    while(running)
    {   show_ui();
        choice = -1;
        try{
            std::getline(std::cin, input);
            choice = std::stoi(input);
        }
        catch(std::invalid_argument &o)
        {
            //std::cout<<"Valoare non-numerica!\n";
        }


        ///Try
        switch (choice) {
            case 1:
                add_produs_ui();
                break;
            case 4:
                print_all_ui();
                break;
            default:
                std::cout<<"Varianta inexsitetna!\n";
                getchar();

        }
    }


}

void UI::print_all_ui()
{
  std::vector<Produs> l = SERVICE.afisare_produse_service();
  for(auto el:l)
  {
      std::cout<<el<<std::endl;
  }

}
void UI::add_produs_ui() {
    std::string nume;
    std::cout<<" Dati numele: ";
    std::getline(std::cin, nume);

    std::string tip;
    std::cout<<"Dati tipul: ";
    std::getline(std::cin, tip);

    std::string producator;
    std::cout<<"Dati producatorul: ";
    std::getline(std::cin, producator);

    std::string pret_string;
    float pret;
    std::cout<<"Dati pretrul: ";
    std::getline(std::cin, pret_string);
    pret = std::stof(pret_string);

    SERVICE.adaugare_produs_service(nume,tip,producator,pret);



}
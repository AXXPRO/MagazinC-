//
// Created by Gabi on 02.04.2023.
//
#include <iostream>
#include "ui.h"
using std::cout;
using std::endl;

void UI::show_ui() const{

    cout<<"Alegeti optiunea dumeavoastra:\n";
    cout<<"1.Adaugare de produs\n";
    cout<<"2.Sterge produs dupa nume\n";
    cout<<"3.Cauta produs dupa nume\n";
    cout<<"4.Afisare de produse\n";
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
        try {
            switch (choice) {
                case 1:
                    add_produs_ui();
                    break;
                case 2:
                    delete_ui();
                    break;
                case 3:
                    cauta_ui();
                    break;
                case 4:
                    print_all_ui();
                    break;
                default:
                    std::cout<<"Varianta inexsitetna!\n";
                    getchar();

            }
        }
        catch (...){cout<<"Eroare!\n";}

    }


}

void UI::cauta_ui()
{
    string  nume_de_cautat;
    cout<<" Dati numele: ";
    std::getline(std::cin, nume_de_cautat);

    Produs cautat = SERVICE.cauta_service(nume_de_cautat);

    cout<<cautat<<endl;

}
void UI::delete_ui() {

    string  nume_de_sters;
    cout<<" Dati numele: ";
    std::getline(std::cin, nume_de_sters);
    SERVICE.delete_service(nume_de_sters);
}

void UI::print_all_ui() const
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
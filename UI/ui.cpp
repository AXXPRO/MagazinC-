//
// Created by Gabi on 02.04.2023.
//
#include <iostream>
#include "ui.h"
using std::cout;
using std::cin;
using std::endl;

void UI::show_ui() {

    cout<<"Alegeti optiunea dumeavoastra:\n";
    cout<<"1.Adaugare de produs\n";
    cout<<"2.Sterge produs dupa nume\n";
    cout<<"3.Cauta produs dupa nume\n";
    cout<<"4.Modifica produs dupa nume\n";
    cout<<"5.Afisare de produse\n";
    cout<<"6.Filtrare dupa un criteriu\n";
    cout<<"7.Sortare dupa un criteriu\n";
    cout<<"0.Inchidere\n";
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
                case 0:
                    running = false;
                    break;
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
                    modifica_ui();
                    break;

                case 5:
                    print_all_ui(SERVICE.afisare_produse_service());
                    break;
                case 6:
                    filtrare_ui();
                    break;
                case 7:
                    sortare_ui();
                    break;
                default:
                    std::cout<<"Varianta inexsitetna!\n";
                    getchar();

            }
        }
        catch (RepoError& err){cout<<err;}
        catch (std::invalid_argument&) {cout<<"Date de intrare invalide!\n";}

    }


}
void UI::modifica_ui() {

    string  nume_de_modificat;
    cout<<" Dati numele: ";
    std::getline(std::cin, nume_de_modificat);

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

    SERVICE.modifica_service(nume_de_modificat,tip,producator,pret);


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

void UI::print_all_ui(vector<Produs> v) const
{
  //  vector<Produs> v{SERVICE.afisare_produse_service()};

    for(auto const& el : v)
        cout<<el<<endl;
 // for(const auto& el:l)
  //{
    //  std::cout<<el<<std::endl;
 // }

}

void UI::filtrare_ui()
{
    string camp_filtrat_string;
    int camp_filtrat;
    string filtru;
    cout<<"Dupa ce criteriu doriti sa filtrati?\n1.Pret\n2.Nume\n3.Producator\n";

    std::getline(std::cin, camp_filtrat_string);
    camp_filtrat = std::stof(camp_filtrat_string);

    cout<<"Dati criteriul pe care trebuie sa il indeplineasca(cu ce valoare sa fie egal campul ales)\n";
    std::getline(std::cin, filtru);

    vector<Produs> filtrat;
    SERVICE.filtrare_service(filtrat, camp_filtrat, filtru);
    print_all_ui(filtrat);





}

void UI::sortare_ui()
{


    string camp_sortare_string;
    int camp_sortat;

    cout<<"Dupa ce criteriu doriti sa sortati?\n1.Nume\n2.Pret\n3.Nume + Tip\n";

    std::getline(std::cin, camp_sortare_string);
    camp_sortat = std::stof(camp_sortare_string);

    vector<Produs> sortat;
    SERVICE.sortare_service(sortat, camp_sortat);

    print_all_ui(sortat);



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
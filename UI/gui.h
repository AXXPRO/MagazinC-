//
// Created by Gabi on 07.05.2023.
//

#ifndef MAGAZINC___GUI_H
#define MAGAZINC___GUI_H
#include "../Service/service.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QFormLayout>
#include <QCheckBox>

class GUI: public QWidget{
private:
Q_OBJECT
    Service& SERVICE;
    //Prints a UI interface

    Produs curretProdus = Produs("","","",-1);
    QVBoxLayout* layoutMain;
    QHBoxLayout* layoutHorizonalList;
    QFormLayout* formLauyout;
    QFormLayout* searchLayout;
    QLineEdit* searchBar;
    QLineEdit* numeEdit;
    QLineEdit* tipEdit;
    QLineEdit* producatorEdit;
    QLineEdit* pretEdit;
    QCheckBox* sortedCheckBox;
    QCheckBox* filteredCheckBox;
    QPushButton* filtersButton;
    QPushButton* sortersButton;
    std::string filteredField;
    int sortType;
    int filterType;
    std::string currentTextSearched;

    QListWidget* lista;
    ///Needed to check if an item disappeared
    int lastRow;
    QPushButton* AddButton;
    QPushButton* DeleteButton;
    QPushButton* ModifyButton;
    QPushButton* UndoButton;
    QFont font;
    QVBoxLayout* LayoutMenuButtons;
    QWidget* MenuButtons;
    void LoadElements(QListWidget* ,vector<Produs>);

    void connect();

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

    void export_ui();
    void raport_ui();
    void undo_ui();

public:
    GUI(Service& SERVICE);

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

#endif //MAGAZINC___GUI_H
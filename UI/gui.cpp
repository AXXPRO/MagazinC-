#include "../Service/service.h"
#include "gui.h"
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>

GUI::GUI(Service& SERVICE):SERVICE(SERVICE){

    layoutMain = new QVBoxLayout;
    layoutHorizonalList  = new QHBoxLayout;
    ///adaugam un widget, meniul si 2 butoane
    ///meniu si 2 butone orizonatl

    menu_and_buttons = new QWidget;
    menu_and_buttons->setLayout(layoutHorizonalList);
    lista = new QListWidget;
    layoutHorizonalList->addWidget(lista);

    AddButton = new QPushButton("Adauga");
    DeleteButton = new QPushButton("Sterge");
    font = QFont("Times new Roman", 16);
    DeleteButton->setFont(font);
    AddButton->setFont(font);
    LayoutMenuButtons =  new QVBoxLayout;
    MenuButtons = new QWidget;
    MenuButtons->setLayout(LayoutMenuButtons);
    LayoutMenuButtons->addWidget(AddButton);
    LayoutMenuButtons->addWidget(DeleteButton);
    layoutHorizonalList->addWidget(MenuButtons);

    layoutMain->addWidget(menu_and_buttons);



    //QPushButton* AddButton = new QPushButton("Adauga");
    //QPushButton* DeleteButton = new QPushButton("Sterge");
  //  auto font = QFont("Times new Roman", 16);

  //  DeleteButton->setFont(font);
   // AddButton->setFont(font);

    this->setLayout(layoutMain);

    LoadElements(SERVICE.afisare_produse_service());

}

void GUI::LoadElements(vector<Produs> vector) {

    this->lista->clear();
   for(auto const el : vector)
    {
        new QListWidgetItem( QString::fromStdString( el.to_string()) , this->lista);
    }




}
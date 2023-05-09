#include "../Service/service.h"
#include "../Validator/validator.h"
#include "gui.h"
#include <string>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

GUI::GUI(Service& SERVICE):SERVICE(SERVICE){

    layoutMain = new QVBoxLayout;
    layoutHorizonalList  = new QHBoxLayout;
    ///adaugam un widget, meniul si 2 butoane
    ///meniu si 2 butone orizonatl

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

    layoutMain->addLayout(layoutHorizonalList);


    formLauyout = new QFormLayout;

    numeEdit = new QLineEdit;
    numeEdit->setFont(this->font);
    tipEdit= new QLineEdit;
    tipEdit->setFont(this->font);
    producatorEdit= new QLineEdit;
    producatorEdit->setFont(this->font);
    pretEdit= new QLineEdit;
    pretEdit->setFont(this->font);

    this->numeEdit->setFixedHeight(36);
    this->tipEdit->setFixedHeight(36);
    this->producatorEdit->setFixedHeight(36);
    this->pretEdit->setFixedHeight(36);

    this->numeEdit->setFixedWidth(200);
    this->tipEdit->setFixedWidth(200);
    this->producatorEdit->setFixedWidth(200);
    this->pretEdit->setFixedWidth(200);


    QLabel *numeString = new QLabel("Nume: ");
    numeString->setFont(this->font);

    QLabel *tipString = new QLabel("Tip: ");
    tipString->setFont(this->font);

    QLabel *producatorString = new QLabel("Producator: ");
    producatorString->setFont(this->font);

    QLabel *pretString = new QLabel("Pret: ");
    pretString->setFont(this->font);

    formLauyout->addRow(numeString, this->numeEdit);
    formLauyout->addRow(tipString, this->tipEdit);
    formLauyout->addRow(producatorString, this->producatorEdit);
    formLauyout->addRow(pretString, this->pretEdit);

    layoutMain->addLayout(formLauyout);

    searchLayout = new QFormLayout;
    searchBar = new QLineEdit;
    searchBar->setFont(this->font);
    this->searchBar->setFixedHeight(36);

    this->searchBar->setFixedWidth(300);

    QLabel *searchString = new QLabel("Cauta: ");
    searchString->setFont(this->font);
    searchLayout->addRow( searchString, this->searchBar);


    layoutMain->addLayout(searchLayout);

    this->setLayout(layoutMain);



    LoadElements(this->lista, SERVICE.afisare_produse_service());
    connect();
}


void GUI::connect() {

    QObject::connect(this->AddButton, &QPushButton::clicked,[this](){

        std::string nume = numeEdit->text().toStdString();
        std::string tip = tipEdit->text().toStdString();
        std::string producator = producatorEdit->text().toStdString();
        std::string pret_string =pretEdit->text().toStdString();
        float pret;
        try
        {
            pret = std::stof(pret_string);
        }
        catch (std::invalid_argument&) {pret = -1;} ///Invalid price

        try {
            SERVICE.adaugare_produs_service(nume,tip,producator,pret);
            LoadElements(this->lista, SERVICE.afisare_produse_service());
        }
        catch (RepoError& err){QMessageBox::warning(this,"Something went wrong!",QString::fromStdString(err.mesaj) );}
       catch (ValidatorError& err){QMessageBox::warning(this,"Something went wrong!",QString::fromStdString(err.mesaj) );}


    } );
    QObject::connect(this->DeleteButton, &QPushButton::clicked,[this](){



        try {
            ValidatorProdus::isValid(this->curretProdus);
        }
        catch (ValidatorError& err) {
            QMessageBox::warning(this,"Please select!","Click the item from the list you want to delete." );
            return;
        }
       string numeDeSters = this->curretProdus.getNume();
        this->SERVICE.delete_service(numeDeSters);
        LoadElements(this->lista, SERVICE.afisare_produse_service());

    } );
    QObject::connect(this->lista, &QListWidget::itemSelectionChanged, [this](){
    if(this->lista->selectionModel()->currentIndex().row() == this->lastRow)
    {   ///Invalidate it
        this->curretProdus = Produs("","","",-1);
        return;
    }
    this->lastRow = this->lista->selectionModel()->currentIndex().row();
      auto textWidgetItem = this->lista->item(this->lista->selectionModel()->currentIndex().row());


     auto textItem = textWidgetItem->text().toStdString();


     std::stringstream X(textItem);
        string cuvant;
        vector<string> cuvinte;
        while(getline(X, cuvant, ','))
        {
            cuvinte.push_back(cuvant);
        }

        ///nume, tip, producator, pret
       /// Produs p(cuvinte[0],cuvinte[1],cuvinte[2] , stof(cuvinte[3]));
       this->numeEdit->setText(QString::fromStdString(cuvinte[0]));
        this->tipEdit->setText(QString::fromStdString(cuvinte[1]));
        this->producatorEdit->setText(QString::fromStdString(cuvinte[2]));
        this->pretEdit->setText(QString::fromStdString(cuvinte[3]));
        this->curretProdus = Produs(cuvinte[0],cuvinte[1],cuvinte[2] , stof(cuvinte[3]));


    });
    QObject::connect(this->searchBar, &QLineEdit::textChanged, [this](const QString& text){


        std::string currentText = text.toStdString();

        vector<Produs> vectorService = SERVICE.afisare_produse_service();
        vector<Produs> vectorSearch;

        for(const auto& el : vectorService)
        {
        auto pos = el.getNume().find(currentText);
        if (pos == 0)
        {
            vectorSearch.push_back(el);
        }
     //

        }

        LoadElements(this->lista, vectorSearch);

    });


}


void GUI::LoadElements(QListWidget* listToPopulate, vector<Produs> vector) {

    listToPopulate->clear();
   for(auto const el : vector)
    {
     auto Item = new QListWidgetItem( QString::fromStdString( el.to_string()));
     Item->setFont(this->font);
     listToPopulate->addItem(Item);

    }




}
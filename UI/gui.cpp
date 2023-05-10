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
    ModifyButton = new QPushButton("Modifica");
    UndoButton = new QPushButton("Undo");
    font = QFont("Times new Roman", 16);
    DeleteButton->setFont(font);
    AddButton->setFont(font);
    ModifyButton->setFont(font);
    UndoButton->setFont(font);
    LayoutMenuButtons =  new QVBoxLayout;
    MenuButtons = new QWidget;
    MenuButtons->setLayout(LayoutMenuButtons);
    LayoutMenuButtons->addWidget(AddButton);
    LayoutMenuButtons->addWidget(DeleteButton);
    LayoutMenuButtons->addWidget(ModifyButton);
    LayoutMenuButtons->addWidget(UndoButton);
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
    this->currentTextSearched="";

    layoutMain->addLayout(searchLayout);

    filteredCheckBox = new QCheckBox("Filtrate");
    filteredCheckBox->setFont(this->font);
    sortedCheckBox =  new QCheckBox("Sortate");
    sortedCheckBox->setFont(this->font);
    auto layoutCheckBox = new QHBoxLayout;
    layoutCheckBox->addWidget(filteredCheckBox);
    layoutCheckBox->addWidget(sortedCheckBox);

    filtersButton = new QPushButton("Filtre");
    filtersButton->setFont(font);
    sortersButton = new QPushButton("Sortari");
    sortersButton->setFont(font);
    layoutCheckBox->addWidget(filtersButton);
    layoutCheckBox->addWidget(sortersButton);


    sortedCheckBox->setCheckState(Qt::Unchecked);
    filteredCheckBox->setCheckState(Qt::Unchecked);

    filterType=2;
    filteredField="";
    sortType=1;

    layoutMain->addLayout(layoutCheckBox);
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

    QObject::connect(this->searchBar, &QLineEdit::textChanged, [this](const QString& text){


       this->currentTextSearched = text.toStdString();

        LoadElements(this->lista, SERVICE.afisare_produse_service());

    });
    QObject::connect(this->ModifyButton, &QPushButton::clicked,[this](){


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
            SERVICE.modifica_service(nume,tip,producator,pret);
            LoadElements(this->lista, SERVICE.afisare_produse_service());
        }
        catch (RepoError& err){QMessageBox::warning(this,"Something went wrong!",QString::fromStdString(err.mesaj) );}
        catch (ValidatorError& err){QMessageBox::warning(this,"Something went wrong!",QString::fromStdString(err.mesaj) );}


    } );
    QObject::connect(this->UndoButton, &QPushButton::clicked,[this](){



    try {
        SERVICE.undo_service();
    }
    catch(ValidatorError &err) {
        QMessageBox::warning(this,"Something went wrong!",QString::fromStdString(err.mesaj) );
        return;
    }
    catch(RepoError&err)
    { QMessageBox::warning(this,"Something went wrong!",QString::fromStdString(err.mesaj) );
        return;

    }
        LoadElements(this->lista, SERVICE.afisare_produse_service());

    });

    QObject::connect(this->lista, &QListWidget::itemSelectionChanged, [this](){


    //    std::cout<<this->lista->selectionModel()->currentIndex().row()<<std::endl;


        if(this->lista->selectedItems().size() == 0)
        {   ///Invalidate it
            this->curretProdus = Produs("","","",-1);
            return;
        }


       // this->lastRow = this->lista->selectionModel()->currentIndex().row();
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

      //  std::cout<<this->curretProdus<<std::endl;
    });

    QObject::connect(this->filteredCheckBox, &QCheckBox::stateChanged, [this](const int state){

        LoadElements(this->lista, SERVICE.afisare_produse_service());
    });

    QObject::connect(this->sortedCheckBox, &QCheckBox::stateChanged, [this](const int state){

        LoadElements(this->lista, SERVICE.afisare_produse_service());
    });

    QObject::connect(this->filtersButton, &QPushButton::clicked, [this](){
        QWidget* filtersScreen = new QWidget;

        auto layout = new QVBoxLayout;
        auto label = new QLabel("Introduceti filrtrul, si apoi apasati butonul specific campului dupa care filtrati");
        label->setFont(this->font);
        layout->addWidget(label);
        auto inputFilter = new QLineEdit;
        inputFilter->setFixedHeight(40);
        //inputFilter->setFixedWidth(200);
        inputFilter->setFont(this->font);
        layout->addWidget(inputFilter);


        auto pret_button = new QPushButton("Pret");
        pret_button->setFont(this->font);
        auto name_button = new QPushButton("Nume");
        name_button->setFont(this->font);
        auto producator_button = new QPushButton("Producator");
        producator_button->setFont(this->font);


        // 1.Pret
        // 2.Nume
        //3.Producator



        auto buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(name_button);
        buttonLayout->addWidget(pret_button);
        buttonLayout->addWidget(producator_button);

        layout->addLayout(buttonLayout);
        filtersScreen->setLayout(layout);

        QObject::connect(name_button, &QPushButton::clicked, [filtersScreen,inputFilter,this](){
            this->filterType = 2;
            this->filteredField = inputFilter->text().toStdString();

            std::cout<<this->filteredField<<std::endl;
            filtersScreen->hide();
            LoadElements(this->lista, SERVICE.afisare_produse_service());
        });

        QObject::connect(pret_button, &QPushButton::clicked, [filtersScreen,inputFilter,this](){
            this->filterType = 1;
            this->filteredField = inputFilter->text().toStdString();
            std::cout<<this->filteredField<<std::endl;
            filtersScreen->hide();
            LoadElements(this->lista, SERVICE.afisare_produse_service());
        });

        QObject::connect(producator_button, &QPushButton::clicked, [filtersScreen,inputFilter,this](){
            this->filterType = 3;
            this->filteredField = inputFilter->text().toStdString();
            std::cout<<this->filteredField<<std::endl;
            filtersScreen->hide();
            LoadElements(this->lista, SERVICE.afisare_produse_service());
        });


        filtersScreen->show();
/*


        QObject::connect(pret_button, &QPushButton::clicked, [sortersScreen,this](){
            this->sortType = 2;
            sortersScreen->hide();
        });
        QObject::connect(tip_button, &QPushButton::clicked, [sortersScreen,this](){
            this->sortType = 3;
            sortersScreen->hide();
        });
        sortersScreen->show();


        */
    });

    QObject::connect(this->sortersButton, &QPushButton::clicked, [this]() {
        auto sortersScreen = new QWidget;
        auto layout = new QVBoxLayout;
        auto label = new QLabel("Selectati dupa ce doriti sa sortam elementele");
        label->setFont(this->font);

        layout->addWidget(label);

        auto name_button = new QPushButton("Nume");
        name_button->setFont(this->font);

        auto pret_button = new QPushButton("Pret");
        pret_button->setFont(this->font);

        auto tip_button = new QPushButton("Nume + Tip");
        tip_button->setFont(this->font);

        auto buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(name_button);
        buttonLayout->addWidget(pret_button);
        buttonLayout->addWidget(tip_button);

        layout->addLayout(buttonLayout);
        // 1.Nume
        // 2.Pret
        // 3.Nume + Tip
        sortersScreen->setLayout(layout);

        QObject::connect(name_button, &QPushButton::clicked, [sortersScreen,this](){
         this->sortType = 1;
            sortersScreen->hide();
            LoadElements(this->lista, SERVICE.afisare_produse_service());
        });

        QObject::connect(pret_button, &QPushButton::clicked, [sortersScreen,this](){
            this->sortType = 2;
            sortersScreen->hide();
            LoadElements(this->lista, SERVICE.afisare_produse_service());
        });
        QObject::connect(tip_button, &QPushButton::clicked, [sortersScreen,this](){
            this->sortType = 3;
            sortersScreen->hide();
            LoadElements(this->lista, SERVICE.afisare_produse_service());
        });
        sortersScreen->show();

    });
}


void GUI::LoadElements(QListWidget* listToPopulate, vector<Produs> vectorInitial) {


    ///2 is on, 0 is off
    ///if filtrate

    vector<Produs> vector;
    listToPopulate->clear();

    std::copy_if(vectorInitial.begin(), vectorInitial.end(), std::back_inserter(vector), [this](const Produs& p){

        auto pos = p.getNume().find(this->currentTextSearched);
        return  pos == 0;
    });

    if(this->sortedCheckBox->checkState() == Qt::Checked)
    {
        vector =  SERVICE.sortare_service_GUI(vector, this->sortType);
    }

    if(this->filteredCheckBox->checkState() == Qt::Checked)
    {

       vector = SERVICE.filtrare_service_GUI(vector,this->filterType, this->filteredField);
    }


    ///if sortate

   for(auto const el : vector)
    {
     auto Item = new QListWidgetItem( QString::fromStdString( el.to_string()));
     Item->setFont(this->font);
     listToPopulate->addItem(Item);

    }




}
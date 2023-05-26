#include "../Service/service.h"
#include "../Validator/validator.h"
#include "gui.h"
#include <string>
#include <stdlib.h>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QTabBar>
#include <QTabWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QMouseEvent>
#include <unistd.h>

GUI::GUI(Service &SERVICE) : SERVICE(SERVICE) {
    layoutMain = new QVBoxLayout;

    this->mainTab = new QWidget;
    this->mainTab->setLayout(layoutMain);

    layoutHorizonalList = new QHBoxLayout;
    ///adaugam un widget, meniul si 2 butoane
    ///meniu si 2 butone orizonatl

    lista = new QListWidget;

    layoutHorizonalList->addWidget(lista);

    AddButton = new QPushButton("Adauga");
    DeleteButton = new QPushButton("Sterge");
    ModifyButton = new QPushButton("Modifica");
    UndoButton = new QPushButton("Undo");
    AdaugaCosButton = new QPushButton("Adauga in Cos");
    font = QFont("Times new Roman", 16);
    DeleteButton->setFont(font);
    AddButton->setFont(font);
    ModifyButton->setFont(font);
    UndoButton->setFont(font);
    AdaugaCosButton->setFont(font);
    LayoutMenuButtons = new QVBoxLayout;
    MenuButtons = new QWidget;
    MenuButtons->setLayout(LayoutMenuButtons);
    LayoutMenuButtons->addWidget(AddButton);
    LayoutMenuButtons->addWidget(DeleteButton);
    LayoutMenuButtons->addWidget(ModifyButton);
    LayoutMenuButtons->addWidget(UndoButton);
    LayoutMenuButtons->addWidget(AdaugaCosButton);
    layoutHorizonalList->addWidget(MenuButtons);

    layoutMain->addLayout(layoutHorizonalList);


    formLauyout = new QFormLayout;

    numeEdit = new QLineEdit;
    numeEdit->setFont(this->font);
    tipEdit = new QLineEdit;
    tipEdit->setFont(this->font);
    producatorEdit = new QLineEdit;
    producatorEdit->setFont(this->font);
    pretEdit = new QLineEdit;
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
    searchLayout->addRow(searchString, this->searchBar);
    this->currentTextSearched = "";

    layoutMain->addLayout(searchLayout);

    filteredCheckBox = new QCheckBox("Filtrate");
    filteredCheckBox->setFont(this->font);
    sortedCheckBox = new QCheckBox("Sortate");
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

    filterType = 2;
    filteredField = "";
    sortType = 1;

    layoutMain->addLayout(layoutCheckBox);
    layoutRaportButtons = new QHBoxLayout;
    layoutMain->addLayout(layoutRaportButtons);

//     slider = new QSlider(Qt::Horizontal);
//
//
//    slider->setRange(0,2);
//    slider->setValue(0);
//    slider->setFixedWidth(200);
//  //  slider->setFixedHeight(100);
//
//    layoutMain->addWidget(slider);

    this->currentShownVector=SERVICE.afisare_produse_service();
    loadButoane(layoutRaportButtons);


    //this->setLayout(layoutMain);
   // auto tabs = new QTabWidget();
    this->addTab(this->mainTab, "main");
    this->cosTab = new QWidget;
    this->addTab(this->cosTab, "Cos");

  //  this->tableCos = new QTableWidget;
  //  this->tableCos->setFont(this->font);
   // this->tableCos->setColumnCount(4);

   // QStringList headers;
    //headers<<"Nume"<<"Producator"<<"Tip"<<"Pret";
    //this->tableCos->setHorizontalHeaderLabels(headers);
    cosVLayout = new QVBoxLayout;
    CosCRUDGUIButton = new QPushButton("CosCRUDGUI");
    CosCRUDGUIButton->setFont(font);
     CosReadOnlyGUIButton = new QPushButton("CosReadOnlyGUI");
     CosReadOnlyGUIButton->setFont(font);
    cosVLayout->addWidget(CosCRUDGUIButton);
   cosVLayout->addWidget(CosReadOnlyGUIButton);




   // cosVLayout->addWidget(this->tableCos);


    EmptyCosButton = new QPushButton("Empty Cos");
    EmptyCosButton->setFont(font);

    QLabel* textGenerare = new QLabel("Cate elemente aleatorii generam: ");
    textGenerare->setFont(font);
    QLabel* textExport = new QLabel("Cu ce nume dam export la cos: ");
    textExport->setFont(font);


    GenerateCosButton = new QPushButton("Genereaza elemente aleator");
    GenerateCosButton->setFont(font);
    ExportCosButton = new QPushButton("Export");
    ExportCosButton->setFont(font);

    exportTextEdit = new QLineEdit;
    exportTextEdit->setFont(font);
    numarGenerateTextEdit = new QLineEdit;
    numarGenerateTextEdit->setFont(font);

    ///Adaugam 2 layouturi orizontale, unu pentru export, altu pentru generare de elemente

    auto generateLayout = new QHBoxLayout;
    auto exportLayout = new QHBoxLayout;

    generateLayout->addWidget(textGenerare);
    generateLayout->addWidget(numarGenerateTextEdit);
    generateLayout->addWidget(GenerateCosButton);

    exportLayout->addWidget(textExport);
    exportLayout->addWidget(exportTextEdit);
    exportLayout->addWidget(ExportCosButton);

    cosVLayout->addLayout(generateLayout);


    cosVLayout->addLayout(exportLayout);

    cosVLayout->addWidget(EmptyCosButton);

    cosTab->setLayout(cosVLayout);

    //tabs->show();


    update();
    connect();
}

void GUI::loadButoane(QHBoxLayout *layout) {


    std::map<string, vector<Produs>> dictionar;
    SERVICE.raport_service_GUI(dictionar, this->currentShownVector);

    for (auto &el: vectorButoaneDinamice) {
        delete el;
    }
    this->vectorButoaneDinamice.clear();
    this->numarInstante.clear();
    QPushButton *buttonNou;
    int i = 0;

    for (auto const &el: dictionar) {
        numarInstante.push_back(0);
        buttonNou = new QPushButton(QString::fromStdString(el.first));
        buttonNou->setFont(this->font);
        ///pozitia lui e i

        // cout<<"Elementele de tipul "<<el.first<<" sunt:\n";
        for (auto const &prod: el.second) {
            numarInstante[i]++;
        }
        //  std::cout<<numarInstante[i]<<std::endl;

        this->vectorButoaneDinamice.push_back(buttonNou);
        layout->addWidget(buttonNou);
        QObject::connect(buttonNou, &QPushButton::clicked, [this, i]() {

            QMessageBox::warning(this, "Number of ", QString::fromStdString(std::to_string(numarInstante[i])));
        });
        i++;


    }

}

void GUI::connect() {
   // for(auto const taburiCos: this->elementeObserver)

    QObject::connect(this->CosCRUDGUIButton, &QPushButton::clicked, [this](){

        Observer* tabNou = new CosCRUDGUI(this->SERVICE);

        this->elementeObserver.push_back(tabNou);
        SERVICE.addInteresat(tabNou);
        tabNou->idInVector = elementeObserver.size() - 1;
        QObject::connect(tabNou,&Observer::removeObserverIndexed , [this,tabNou](){

           SERVICE.removeInteresat(tabNou);
        });

     //   sleep(2);
       // delete elementeObserver[0];
    });

    QObject::connect(this->ExportCosButton, &QPushButton::clicked, [this]() {

        auto text = this->exportTextEdit->text();


        if(text.isEmpty())
        {
            QMessageBox::warning(this, "Something went wrong!", "Dati un nume de export!");
            return;
        }
    SERVICE.export_service(text.toStdString());

    });


    QObject::connect(this->GenerateCosButton, &QPushButton::clicked, [this]() {

        auto text = this->numarGenerateTextEdit->text();

        try {
            int numar = stoi(text.toStdString());
            SERVICE.genereaza_cos_service(numar);
            update();

        }
        catch (std::invalid_argument) {
            QMessageBox::warning(this, "Something went wrong!", "Numar de elemente invalid!");
            return;
        }

    });

    QObject::connect(this->EmptyCosButton, &QPushButton::clicked, [this]() {

        SERVICE.goleste_cos_servcie();
        update();

    });
    QObject::connect(this->AddButton, &QPushButton::clicked, [this]() {

        std::string nume = numeEdit->text().toStdString();
        std::string tip = tipEdit->text().toStdString();
        std::string producator = producatorEdit->text().toStdString();
        std::string pret_string = pretEdit->text().toStdString();
        float pret;
        try {
            pret = std::stof(pret_string);
        }
        catch (std::invalid_argument &) { pret = -1; } ///Invalid price

        try {
            SERVICE.adaugare_produs_service(nume, tip, producator, pret);

        }
        catch (RepoError &err) {
            QMessageBox::warning(this, "Something went wrong!", QString::fromStdString(err.mesaj));
        }
        catch (ValidatorError &err) {
            QMessageBox::warning(this, "Something went wrong!", QString::fromStdString(err.mesaj));
        }

        update();

    });
    QObject::connect(this->DeleteButton, &QPushButton::clicked, [this]() {


        try {
            ValidatorProdus::isValid(this->curretProdus);
        }
        catch (ValidatorError &err) {
            QMessageBox::warning(this, "Please select!", "Click the item from the list you want to delete.");
            return;
        }
        string numeDeSters = this->curretProdus.getNume();
        this->SERVICE.delete_service(numeDeSters);
        update();
    });

    QObject::connect(this->AdaugaCosButton, &QPushButton::clicked, [this]() {


        try {
            ValidatorProdus::isValid(this->curretProdus);
        }
        catch (ValidatorError &err) {
            QMessageBox::warning(this, "Please select!", "Click the item from the list you want to add to the Cos.");
            return;
        }
        string numeProdus = this->curretProdus.getNume();
        this->SERVICE.adaugare_cos_service(numeProdus);
        update();
    });

    QObject::connect(this->searchBar, &QLineEdit::textChanged, [this](const QString &text) {


        this->currentTextSearched = text.toStdString();

        update();

    });
    QObject::connect(this->ModifyButton, &QPushButton::clicked, [this]() {


        std::string nume = numeEdit->text().toStdString();
        std::string tip = tipEdit->text().toStdString();
        std::string producator = producatorEdit->text().toStdString();
        std::string pret_string = pretEdit->text().toStdString();
        float pret;
        try {
            pret = std::stof(pret_string);
        }
        catch (std::invalid_argument &) { pret = -1; } ///Invalid price

        try {
            SERVICE.modifica_service(nume, tip, producator, pret);

        }
        catch (RepoError &err) {
            QMessageBox::warning(this, "Something went wrong!", QString::fromStdString(err.mesaj));
        }
        catch (ValidatorError &err) {
            QMessageBox::warning(this, "Something went wrong!", QString::fromStdString(err.mesaj));
        }

        update();

    });
    QObject::connect(this->UndoButton, &QPushButton::clicked, [this]() {


        try {
            SERVICE.undo_service();
        }
        catch (ValidatorError &err) {
            QMessageBox::warning(this, "Something went wrong!", QString::fromStdString(err.mesaj));
            return;
        }
        catch (RepoError &err) {
            QMessageBox::warning(this, "Something went wrong!", QString::fromStdString(err.mesaj));
            return;

        }
        update();

    });

    QObject::connect(this->lista, &QListWidget::itemSelectionChanged, [this]() {


        //    std::cout<<this->lista->selectionModel()->currentIndex().row()<<std::endl;


        if (this->lista->selectedItems().size() == 0) {   ///Invalidate it
            this->curretProdus = Produs("", "", "", -1);
            return;
        }


        // this->lastRow = this->lista->selectionModel()->currentIndex().row();
        auto textWidgetItem = this->lista->item(this->lista->selectionModel()->currentIndex().row());


        auto textItem = textWidgetItem->text().toStdString();


        std::stringstream X(textItem);
        string cuvant;
        vector<string> cuvinte;
        while (getline(X, cuvant, ',')) {
            cuvinte.push_back(cuvant);
        }

        ///nume, tip, producator, pret
        /// Produs p(cuvinte[0],cuvinte[1],cuvinte[2] , stof(cuvinte[3]));
        this->numeEdit->setText(QString::fromStdString(cuvinte[0]));
        this->tipEdit->setText(QString::fromStdString(cuvinte[1]));
        this->producatorEdit->setText(QString::fromStdString(cuvinte[2]));
        this->pretEdit->setText(QString::fromStdString(cuvinte[3]));
        this->curretProdus = Produs(cuvinte[0], cuvinte[1], cuvinte[2], stof(cuvinte[3]));

        //  std::cout<<this->curretProdus<<std::endl;
    });

    QObject::connect(this->filteredCheckBox, &QCheckBox::stateChanged, [this](const int state) {

        update();
    });

    QObject::connect(this->sortedCheckBox, &QCheckBox::stateChanged, [this](const int state) {

        update();
    });

    QObject::connect(this->filtersButton, &QPushButton::clicked, [this]() {
        QWidget *filtersScreen = new QWidget;

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

        QObject::connect(name_button, &QPushButton::clicked, [filtersScreen, inputFilter, this]() {
            this->filterType = 2;
            this->filteredField = inputFilter->text().toStdString();

            //std::cout << this->filteredField << std::endl;
            filtersScreen->hide();
            update();
        });

        QObject::connect(pret_button, &QPushButton::clicked, [filtersScreen, inputFilter, this]() {
            this->filterType = 1;
            this->filteredField = inputFilter->text().toStdString();
           // std::cout << this->filteredField << std::endl;
            filtersScreen->hide();
            update();
        });

        QObject::connect(producator_button, &QPushButton::clicked, [filtersScreen, inputFilter, this]() {
            this->filterType = 3;
            this->filteredField = inputFilter->text().toStdString();
            std::cout << this->filteredField << std::endl;
            filtersScreen->hide();
            update();
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

        QObject::connect(name_button, &QPushButton::clicked, [sortersScreen, this]() {
            this->sortType = 1;
            sortersScreen->hide();
            update();
        });

        QObject::connect(pret_button, &QPushButton::clicked, [sortersScreen, this]() {
            this->sortType = 2;
            sortersScreen->hide();
       update();
        });
        QObject::connect(tip_button, &QPushButton::clicked, [sortersScreen, this]() {
            this->sortType = 3;
            sortersScreen->hide();
        update();
        });
        sortersScreen->show();

    });
}


void GUI::update() {
    LoadElements(this->lista, SERVICE.afisare_produse_service());
    this->loadButoane(this->layoutRaportButtons);
   // this->changeCosPrice();
   // LoadCosElements();
   // std::cout<<slider->value()<<std::endl;

}
/*
void GUI::LoadCosElements()
{
   // this->tableCos->clear();
   // this->tableCos->setRowCount(0);
    this->tableCos->clearContents();
    this->tableCos->setRowCount(0);
    vector<Produs> vect = SERVICE.get_all_cos();

    for(const auto& el: vect)
    {
        auto  nume = new QTableWidgetItem;
        auto  producator = new QTableWidgetItem;
        auto  tip = new QTableWidgetItem;
        auto  pret = new QTableWidgetItem;
        this->tableCos->setRowCount(tableCos->rowCount() + 1);

        nume->setText(QString::fromStdString( el.getNume()));
        producator->setText(QString::fromStdString( el.getProducator()));
        tip->setText(QString::fromStdString( el.getTip()));

        ///float to std
        std::stringstream pretStringStream;
        pretStringStream<<el.getPret();
        std::string pretString = pretStringStream.str();

        pret->setText(QString::fromStdString( pretString));


        this->tableCos->setItem(tableCos->rowCount() -1, 0, nume);
        this->tableCos->setItem(tableCos->rowCount() -1, 1, producator);
        this->tableCos->setItem(tableCos->rowCount() -1, 2, tip);
        this->tableCos->setItem(tableCos->rowCount() -1, 3, pret);
    }


}
 */

void GUI::LoadElements(QListWidget *listToPopulate, vector<Produs> vectorInitial) {


    ///2 is on, 0 is off
    ///if filtrate

    currentShownVector.clear();
    // vector<Produs> vector;


    std::copy_if(vectorInitial.begin(), vectorInitial.end(), std::back_inserter(currentShownVector),
                 [this](const Produs &p) {

                     auto pos = p.getNume().find(this->currentTextSearched);
                     return pos == 0;
                 });

    if (this->sortedCheckBox->checkState() == Qt::Checked) {
        currentShownVector = SERVICE.sortare_service_GUI(currentShownVector, this->sortType);
    }

    if (this->filteredCheckBox->checkState() == Qt::Checked) {

        currentShownVector = SERVICE.filtrare_service_GUI(currentShownVector, this->filterType, this->filteredField);
    }


    ///if sortate
    listToPopulate->clear();
    for (auto const el: currentShownVector) {
        auto Item = new QListWidgetItem(QString::fromStdString(el.to_string()));
        Item->setFont(this->font);
        listToPopulate->addItem(Item);

    }


}

CosCRUDGUI::CosCRUDGUI(Service& S):SERVICE(S){
    this->setFont(QFont("Arial",15));
      tableCos = new QTableWidget;
     this->tableCos->setColumnCount(4);
     QStringList headers;
    headers<<"Nume"<<"Producator"<<"Tip"<<"Pret";
    tableCos->setHorizontalHeaderLabels(headers);

    auto cosCrudLayout = new QVBoxLayout;
    this->setLayout(cosCrudLayout);
    cosCrudLayout->addWidget(tableCos);

    auto formLayout = new QFormLayout;
    cosCrudLayout->addLayout(formLayout);
    this->GenerateCosButton = new QPushButton("Generare");
    cosCrudLineEdit = new QLineEdit;
    formLayout->addRow(this->GenerateCosButton, cosCrudLineEdit);

    this->EmptyCosButton = new QPushButton("Empty");
    cosCrudLayout->addWidget(EmptyCosButton);
    pretLabel = new QLabel;
    setPretLabel();

    cosCrudLayout->addWidget(pretLabel);
    connect();
   populate();



    this->show();
}
void CosCRUDGUI::setPretLabel() {
    auto pretCos = SERVICE.pret_cos_service();
    QLabel("Pretul elementelor din Cos este 0!");
    QString text("Pretul elementelor din Cos este ");

    std::stringstream pretStringStream;
    pretStringStream<<pretCos;
    std::string pretString = pretStringStream.str();


    text.push_back( QString::fromStdString(pretString));
    text.push_back("!");
    pretLabel->setText(text);
}
void CosCRUDGUI::connect() {
    QObject::connect(this->EmptyCosButton, &QPushButton::clicked,[this](){
        SERVICE.goleste_cos_servcie();

    });
    QObject::connect(this->GenerateCosButton, &QPushButton::clicked, [this]() {

        auto text = this->cosCrudLineEdit->text();

        try {
            int numar = stoi(text.toStdString());
            SERVICE.genereaza_cos_service(numar);


        }
        catch (std::invalid_argument) {
            QMessageBox::warning(this, "Something went wrong!", "Numar de elemente invalid!");
            return;
        }

    });
}
void CosCRUDGUI::populate() {


    // this->tableCos->setRowCount(0);
    this->tableCos->clearContents();
    this->tableCos->setRowCount(0);
    vector<Produs> vect = SERVICE.get_all_cos();

    for(const auto& el: vect)
    {
        auto  nume = new QTableWidgetItem;
        auto  producator = new QTableWidgetItem;
        auto  tip = new QTableWidgetItem;
        auto  pret = new QTableWidgetItem;
        this->tableCos->setRowCount(tableCos->rowCount() + 1);

        nume->setText(QString::fromStdString( el.getNume()));
        producator->setText(QString::fromStdString( el.getProducator()));
        tip->setText(QString::fromStdString( el.getTip()));

        ///float to std
        std::stringstream pretStringStream;
        pretStringStream<<el.getPret();
        std::string pretString = pretStringStream.str();

        pret->setText(QString::fromStdString( pretString));


        this->tableCos->setItem(tableCos->rowCount() -1, 0, nume);
        this->tableCos->setItem(tableCos->rowCount() -1, 1, producator);
        this->tableCos->setItem(tableCos->rowCount() -1, 2, tip);
        this->tableCos->setItem(tableCos->rowCount() -1, 3, pret);
    }
}
void CosCRUDGUI::update() {
    this->setPretLabel();
   this->populate();
}
CosCRUDGUI::~CosCRUDGUI() {

 //   std::cout<<"Destructor\n";
    this->destroy();
}


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
#include <QTableWidget>
#include "../observers.h"

class GUI: public QTabWidget{
private:
Q_OBJECT
    Service& SERVICE;
    //Prints a UI interface
    QSlider* slider;
    QWidget* mainTab;
    QWidget* cosTab;
    QLabel* elementeCosLabel;
    QVBoxLayout* cosVLayout;
    vector<Produs> currentShownVector;
    Produs curretProdus = Produs("","","",-1);
    QVBoxLayout* layoutMain;
    QHBoxLayout* layoutHorizonalList;
    QHBoxLayout* layoutRaportButtons;
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
    QTableWidget* tableCos;
    ///Needed to check if an item disappeared
    int lastRow;
    QPushButton* AddButton;
    QPushButton* DeleteButton;
    QPushButton* ModifyButton;
    QPushButton* UndoButton;
    QPushButton* AdaugaCosButton;
    QPushButton* EmptyCosButton;
    QPushButton* GenerateCosButton;
    QPushButton* ExportCosButton;
    QLineEdit* numarGenerateTextEdit;
    QLineEdit* exportTextEdit;
    QFont font;
    QVBoxLayout* LayoutMenuButtons;
    QWidget* MenuButtons;
    vector<Observer*> elementeObserver;

    QPushButton* CosCRUDGUIButton;
    QPushButton* CosReadOnlyGUIButton;

    void LoadCosElements();
    void LoadElements(QListWidget* ,vector<Produs>);

    void connect();

    vector<QPushButton* > vectorButoaneDinamice;
    vector<int> numarInstante;
    void loadButoane(QHBoxLayout* );
    void changeCosPrice();
    void update();


public:
    GUI(Service& SERVICE);

};

class CosCRUDGUI:public Observer{
    void update() override;
Q_OBJECT

protected:
   inline void closeEvent(QCloseEvent* event) override{

        emit removeObserverIndexed(idInVector);
    }
public:
    CosCRUDGUI();
    ~CosCRUDGUI() override;



};



class CosReadOnlyGUI:public Observer{

};
#endif //MAGAZINC___GUI_H

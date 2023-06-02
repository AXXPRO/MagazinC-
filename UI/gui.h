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
#include <QPainter>
#include <QImage>
#include <QPaintEvent>
#include <QGraphicsView>
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
    //void LoadCosElements();
    void LoadElements(QListWidget* ,vector<Produs>);

    void connect();

    vector<QPushButton* > vectorButoaneDinamice;
    vector<int> numarInstante;
    void loadButoane(QHBoxLayout* );

    void update();


public:
    GUI(Service& SERVICE);
protected:
    inline void closeEvent(QCloseEvent* event) override{
        for(const auto& el:elementeObserver)
        {
            delete el;
        }
    }
};

class CosCRUDGUI:public Observer{
    Service& SERVICE;
    QTableWidget* tableCos;
    QPushButton* EmptyCosButton;
    QPushButton* GenerateCosButton;
    QLineEdit* cosCrudLineEdit;
    QLabel* pretLabel;
    void update() override;
    void populate();
    void connect();
    void setPretLabel();
Q_OBJECT

protected:
   inline void closeEvent(QCloseEvent* event) override{

        emit removeObserverIndexed(idInVector);

    }
public:
    CosCRUDGUI(Service& S);


    ~CosCRUDGUI() override;



};



class CosReadOnlyGUI:public Observer{
    Service& SERVICE;
    vector<std::pair<int,int>> coordonates;
    int nrElements;
    int knownNrElements=-1;
    const int WidgetWidth = 500;
    const int WidgetHeight = 500;
    void update() override;
    void populate();
    void connect();
    void paintEvent(QPaintEvent* ev) override{
        QPainter p{ this };
        if(knownNrElements !=nrElements) {
            coordonates.clear();
            for (int i = 0; i < nrElements; i++) {
                int XCord, YCord;
                const int Width = 10;
                const int Height = 10;
                XCord = rand() % WidgetHeight;
                YCord = rand() % WidgetWidth;
                coordonates.emplace_back(XCord, YCord);
            }
        }
        for(int i =0; i<coordonates.size(); i++)
        {
            p.drawEllipse(coordonates[i].first,coordonates[i].second,20, 20);
        }

        knownNrElements = nrElements;
        //QImage imagine;
       //auto e = imagine.load("C:/Users/Gabi/Desktop/MagazinC-/download.jpg");

      // p.drawImage(30,0,imagine);
    }
public:
    CosReadOnlyGUI(Service& S);
protected:
    inline void closeEvent(QCloseEvent* event) override{

        emit removeObserverIndexed(idInVector);

    }

};
#endif //MAGAZINC___GUI_H

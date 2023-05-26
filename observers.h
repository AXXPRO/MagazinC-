//
// Created by Gabi on 25.05.2023.
//

#ifndef MAGAZINC___OBSERVERS_H
#define MAGAZINC___OBSERVERS_H

#include <vector>
#include <iostream>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>

using std::vector;
class Observer:public QWidget{
    Q_OBJECT
protected:


public:
    virtual void update() = 0;
  // explicit Observer(Service* S):SERVICE(S){};
    virtual ~Observer() = default;
    int idInVector;

 signals:
    void removeObserverIndexed(int index);
};



class Observable{
private:
    vector<Observer*> interesati;

public:
    void addInteresat(Observer* el);
    void removeInteresat(Observer* el);
protected:
        void notify(){
            //std::cout<<"SCIMBARE\n";
            for(auto el : interesati)
            {
                el->update();
            }
        }
};



#endif //MAGAZINC___OBSERVERS_H

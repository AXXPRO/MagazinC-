//
// Created by Gabi on 30.03.2023.
//

#include "domain.h"

Produs::Produs(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret) {
    this->nume = nume;
    this->tip = tip;
    this->producator = producator;
    this->pret = pret;
    //std::cout<<"Produs creat prin valori\n";
}

Produs::Produs(const Produs& o){

    this->nume = o.nume;
    this->tip = o.tip;
    this->producator = o.producator;
    this->pret = o.pret;
   // std::cout<<"Produs creat prin alt produs\n";
}

Produs::~Produs() {

   // std::cout<<"Produs distrus!\n";

}
std::string Produs::to_string() const {
    std::string result;

    result+=this->nume;
    result+=",";
    result+=this->tip;
    result+=",";
    result+=this->producator;
    result+=",";
    result+= std::to_string(this->pret);

    return result;

}

std::string Produs::getNume() const{
    return this->nume;
}
std::string Produs::getProducator() const{
    return this->producator;
}
std::string Produs::getTip() const{
    return this->tip;
}
float Produs::getPret() const{
    return this->pret;
}

void Produs::setNume(const std::string& nume_nou) {
    this->nume = nume_nou;
}
void Produs::setProducator(const std::string& producator_nou) {
    this->producator = producator_nou;

}
void Produs::setTip(const std::string& tip_nou) {
    this->tip = tip_nou;
}

void Produs::setPret(const float& pret_nou) {
    this->pret = pret_nou;
}

bool Produs::operator ==(const Produs& o)
{
    bool ok = true;
    if(this->nume != o.nume)
        ok = false;
    if(this->producator != o.producator)
        ok = false;
    if(this->pret != o.pret)
        ok = false;
    if(this->tip != o.tip)
        ok = false;
    return ok;
}

std:: ostream& operator<<(std::ostream& os, const Produs& produs)
{
    os <<"Nume: "<<produs.nume <<" Producator: "<<produs.producator<<" Tip: "<<produs.tip<<" Pret: "<<produs.pret;
    return os;
}

bool operator ==(const Produs&o, const Produs&t)
{
    bool ok = true;
    if(t.nume != o.nume)
        ok = false;
    if(t.producator != o.producator)
        ok = false;
    if(t.pret != o.pret)
        ok = false;
    if(t.tip != o.tip)
        ok = false;
    return ok;
}
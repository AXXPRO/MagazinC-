//
// Created by Gabi on 30.03.2023.
//

#include "domain.h"

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

void Produs::setNume(std::string nume_nou) {
    this->nume = nume_nou;
}
void Produs::setProducator(std::string producator_nou) {
    this->producator = producator_nou;

}
void Produs::setTip(std::string tip_nou) {
    this->tip = tip_nou;
}

void Produs::setPret(float pret_nou) {
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
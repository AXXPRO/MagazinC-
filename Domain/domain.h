//
// Created by Gabi on 30.03.2023.
//
#include <iostream>
#ifndef MAGAZINC___DOMAIN_H
#define MAGAZINC___DOMAIN_H

class Produs{
public:
    Produs(std::string nume, std::string tip, std::string producator, float pret): nume{nume}, tip{tip}, producator{producator}, pret{pret}
    {

    }
    ///
    /// \return the name of the product
    std::string getNume() const;
    ///
    /// \return  the producer of the product
    std::string getProducator() const;
    ///
    /// \return the type of the product
    std::string getTip() const;
    ///
    /// \return the price of the product
    float getPret() const;

    ///sets the name of the produs
    void setNume(std::string);
    ///sets the producator of the produs
    void setProducator(std::string);
    ///sets the type of the produs
    void setTip(std::string);
    ///sets the price of the produs
    void setPret(float);

    bool operator ==(const Produs& o);

private:
    std::string nume;
    std::string tip;
    std::string producator;
    float pret;


};




#endif //MAGAZINC___DOMAIN_H

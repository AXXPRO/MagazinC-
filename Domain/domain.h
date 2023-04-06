//
// Created by Gabi on 30.03.2023.
//
#include <iostream>
#ifndef MAGAZINC___DOMAIN_H
#define MAGAZINC___DOMAIN_H

class Produs{
public:
    Produs(const std::string& nume, const std::string& tip, const std::string& producator, const float& pret);

    Produs(const Produs& o);
    ~Produs();
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
    void setNume(const std::string&);
    ///sets the producator of the produs
    void setProducator(const std::string&);
    ///sets the type of the produs
    void setTip(const std::string&);
    ///sets the price of the produs
    void setPret(const float&);

    bool operator ==(const Produs& o);

    friend std:: ostream& operator<<(std::ostream& os, const Produs& produs);
    friend bool operator ==(const Produs&o, const Produs&t);
private:
    std::string nume;
    std::string tip;
    std::string producator;
    float pret;


};




#endif //MAGAZINC___DOMAIN_H

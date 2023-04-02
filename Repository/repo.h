//
// Created by Gabi on 02.04.2023.
//

#ifndef MAGAZINC___REPO_H
#define MAGAZINC___REPO_H

#include <iostream>
#include <vector>
#include "../Domain/domain.h"


class Repo{

private:
    std::vector<Produs> lista;

public:
    ///
    /// \return the number of elements currently in the Repo
    int numar_elemente() const;
    ///Adds an ellement
    void adaugare_produs(const Produs& element);
    ///Returns an object with the given name, or trows exception if none found
    Produs cauta_element(const std::string nume)const;

    /// Modifies the object's attributes(identified by its name) to the ones of the "other" parameter
    ///Trows exception if no object with said name
    void modifica_element(const std::string nume, const Produs& other);
};

#endif //MAGAZINC___REPO_H

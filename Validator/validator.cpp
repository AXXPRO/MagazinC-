//
// Created by Gabi on 08.04.2023.
//
#include "validator.h"
#include "string.h"
#include "../Erori/errors.h"
void ValidatorProdus::isValid(const Produs& prod)
{

  std::string mesaj_err= "";

    if(prod.getNume() == "")
        mesaj_err += "Nume invalid!\n";
    if(prod.getTip() == "")
        mesaj_err += "Tip invalid!\n";
    if(prod.getProducator() == "")
        mesaj_err += "Producator invalid!\n";
    if(prod.getPret() <= 0)
        mesaj_err += "Pret invalid!\n";

    if(mesaj_err != "")
    {
        throw ValidatorError(mesaj_err);
    }

}
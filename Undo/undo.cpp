//
// Created by Gabi on 30.04.2023.
//

#include "undo.h"
void UndoAdaugare::undo() {

    REPO->delete_element(produs_adaugat.getNume());
}

void UndoModificare::undo() {
    REPO->modifica_element(produs_modificat.getNume(), produs_modificat);
}

void UndoStergere::undo() {

    REPO->adaugare_produs(produs_sters);
}
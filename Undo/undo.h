//
// Created by Gabi on 30.04.2023.
//

#ifndef MAGAZINC___UNDO_H
#define MAGAZINC___UNDO_H

#include "../Domain/domain.h"
#include "../Repository/repo.h"

class ActiuneUndo{

public:
    ActiuneUndo()=default;
    virtual void undo()=0;
    virtual ~ActiuneUndo(){};

};


class UndoAdaugare:public ActiuneUndo{

    Produs produs_adaugat;
    Repo<Produs>& REPO;
public:
    UndoAdaugare(Repo<Produs>& R, const Produs& p):REPO(R), produs_adaugat(p) {};
    void undo() override;
    ~UndoAdaugare() override{};
};


class UndoModificare:public ActiuneUndo{

    Produs produs_modificat;
    Repo<Produs>& REPO;
public:
    UndoModificare(Repo<Produs>& R, const Produs& p):REPO(R), produs_modificat(p) {};
    void undo() override;
    ~UndoModificare() override{};
};


class UndoStergere:public ActiuneUndo{

    Produs produs_sters;
    Repo<Produs>& REPO;
public:
    UndoStergere(Repo<Produs>& R, const Produs& p):REPO(R), produs_sters(p) {};
    void undo() override;
    ~UndoStergere() override{};
};



#endif //MAGAZINC___UNDO_H

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
    RepoAbstract<Produs>* REPO;
public:
    UndoAdaugare(RepoAbstract<Produs>* R, const Produs& p): produs_adaugat(p) {REPO = R;};
    void undo() override;
    ~UndoAdaugare() override{};
};


class UndoModificare:public ActiuneUndo{

    Produs produs_modificat;
    RepoAbstract<Produs>* REPO;
public:
    UndoModificare(RepoAbstract<Produs>* R, const Produs& p):REPO(R), produs_modificat(p) {};
    void undo() override;
    ~UndoModificare() override{};
};


class UndoStergere:public ActiuneUndo{

    Produs produs_sters;
    RepoAbstract<Produs>* REPO;
public:
    UndoStergere(RepoAbstract<Produs>* R, const Produs& p):REPO(R), produs_sters(p) {};
    void undo() override;
    ~UndoStergere() override{};
};



#endif //MAGAZINC___UNDO_H

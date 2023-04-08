//
// Created by Gabi on 06.04.2023.
//

#ifndef MAGAZINC___ERRORS_H
#define MAGAZINC___ERRORS_H

#include <iostream>
using std::string;
using std::ostream;
class RepoError{
    string mesaj;
public:
    RepoError(string err):mesaj{err} {}
friend ostream& operator<<(ostream& out, const RepoError& msj);
};
inline ostream& operator<<(ostream& out, const RepoError& error)
{
    out << error.mesaj;
    return out;
}

class ValidatorError{
    string mesaj;
public:
    ValidatorError(string err):mesaj{err} {}
    friend ostream& operator<<(ostream& out, const ValidatorError& msj);
};

inline ostream& operator<<(ostream& out, const ValidatorError& error)
{
    out << error.mesaj;
    return out;
}


#endif //MAGAZINC___ERRORS_H

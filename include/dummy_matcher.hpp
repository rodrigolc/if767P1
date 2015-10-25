// Rodrigo Lopes - rlc2
// (2015)

/*
    classe com algoritmo "burro".
    usa força bruta para fazer a busca.
*/
#ifndef DUMMY_MATCHER_H
#define DUMMY_MATCHER_H

#include "matcher.hpp"
#include <vector>

class dummy_matcher: public matcher{
private:
    std::vector<char*> patterns;

public:
    dummy_matcher(std::vector<char*> patterns); //construtor
    virtual ~dummy_matcher(); //destrutor
    virtual bool match(const char* string); //procura a string usando o padrão
};

#endif //DUMMY_MATCHER_H

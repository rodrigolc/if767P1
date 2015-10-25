// Rodrigo Lopes - rlc2
// (2015)

#ifndef FUZZY_MATCHER_H
#define FUZZY_MATCHER_H

#include <vector>
#include "matcher.hpp"

class fuzzy_matcher : public matcher {
public:
    fuzzy_matcher(std::vector<char*> patterns,int distance); //construtor
    virtual bool match(const char* string) = 0; //procura a string usando o padrão
};

#endif //FUZZY_MATCHER_H

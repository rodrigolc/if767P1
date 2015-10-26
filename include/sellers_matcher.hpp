// Rodrigo Lopes - rlc2
// (2015)

/*
    classe que implemente o algoritmo aproximado de Peter H Sellers.
*/
#ifndef SELLERS_MATCHER_H
#define SELLERS_MATCHER_H

#include "fuzzy_matcher.hpp"

class sellers_matcher: public matcher{
private:
    std::vector<char*> patterns;
    std::vector<int> sizes;
    int distance;
    int max_size;
public:
    sellers_matcher(std::vector<char*> patterns,int distance=0); //construtor
    virtual ~sellers_matcher(); //destrutor
    virtual bool match(const char* string); //procura a string usando o padrão
};

#endif //SELLERS_MATCHER_H

// Rodrigo Lopes - rlc2
// (2015)

/*
    classe que implemente o algoritmo KMP.
*/
#ifndef KMP_MATCHER_H
#define KMP_MATCHER_H

#include "matcher.hpp"
#include <vector>


class kmp_matcher: public matcher{
private:
    std::vector<int*> tables;
    std::vector<char*> patterns;

public:
    kmp_matcher(std::vector<char*> patterns); //construtor
    virtual ~kmp_matcher(); //destrutor
    virtual bool match(int size, const char* string); //procura a string usando o padrão
};

#endif //KMP_MATCHER_H

// Rodrigo Lopes - rlc2
// (2015)

/*
    classe que implemente o algoritmo aproximado de Peter H Sellers.
*/
#ifndef WU_MANBER_MATCHER_H
#define WU_MANBER_MATCHER_H

#include "fuzzy_matcher.hpp"
#include <map>

class wu_manber_matcher: public matcher{
private:
    std::vector<char*> patterns;
    std::vector<int> sizes;
    std::vector<std::map<char,unsigned long>> maps;
    int distance;
    int max_size;
    // int word_size = sizeof(unsigned long) * 8;
    unsigned long shift_r_correct = (~0) & ((~0)>>1);
public:
    wu_manber_matcher(std::vector<char*> patterns,int distance=0); //construtor
    virtual ~wu_manber_matcher(); //destrutor
    virtual bool match(const char* string); //procura a string usando o padrão
};

#endif //WU_MANBER_MATCHER_H

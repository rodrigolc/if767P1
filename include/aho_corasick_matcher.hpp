// Rodrigo Lopes - rlc2
// (2015)

/*
    classe que implemente o algoritmo KMP.
*/
#ifndef AHO_CORASICK_MATCHER_H
#define AHO_CORASICK_MATCHER_H

#include "matcher.hpp"
#include <map>


struct node {
    //char* label;// TODO check if used
    std::map<char,node*> transitions;
    bool match;
    node* fallback;
    node(/*char* label,*/bool match): /*label(label),*/transitions(),match(match),fallback(nullptr){};
    bool has(const char a){ return transitions.count(a); }
};


class aho_corasick_matcher: public matcher{
private:
    node* root = nullptr;

public:
    aho_corasick_matcher(std::vector<char*> patterns); //construtor
    virtual ~aho_corasick_matcher(); //destrutor
    virtual bool match(const char* string); //procura a string usando o padrão
};

#endif //AHO_CORASICK_MATCHER_H

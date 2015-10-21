// Rodrigo Lopes - rlc2
// (2015)

/*
    classe que implemente o algoritmo KMP.
*/
#ifndef AHO_CORASICK_MATCHER_H
#define AHO_CORASICK_MATCHER_H

#include "matcher.hpp"
#include <vector>

struct node_t;
struct transition{
    char c;
    node_t* _node;
};

struct node_t {
    char* label;
    std::vector<transition> transitions;
};


class aho_corasick_matcher: public matcher{
private:
    node_t* root;

public:
    aho_corasick_matcher(std::vector<char*> patterns); //construtor
    virtual ~aho_corasick_matcher(); //destrutor
    virtual bool match(const char* string); //procura a string usando o padrão
};

#endif //AHO_CORASICK_MATCHER_H

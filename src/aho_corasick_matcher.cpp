// Rodrigo Lopes - rlc2
// (2015)
#include "aho_corasick_matcher.hpp"
#include "util.hpp"
#include "cstring"

node_t* add_pattern(node_t* root, char* string);
node_t* find_failure_functions(node_t* root);
int ac_match(node_t* pattern, const char* string);

aho_corasick_matcher::aho_corasick_matcher(std::vector<char*> patterns){
    // Montar trie
    for(char* pattern : patterns){
        this->root = add_pattern(this->root,pattern);
    }
    // achar funções de falha (transições)
    this->root = find_failure_functions(this->root);
}

aho_corasick_matcher::~aho_corasick_matcher(){

}

bool aho_corasick_matcher::match(int size,const char* string){
    int str_len = size;
    
    return false;
}

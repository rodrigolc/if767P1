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

bool aho_corasick_matcher::match(const char* string){
    int str_len = strlen(string);
    for(size_t i = 0; i < this->patterns.size();i++){
        if(ac_match(this->patterns[i],this->tables[i],string) < str_len) return true;
    }
    return false;
}

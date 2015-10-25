// Rodrigo Lopes - rlc2
// (2015)
#include "aho_corasick_matcher.hpp"
#include "util.hpp"
#include "cstring"
#include <queue>

node* add_pattern(node* root, char* string);
void find_failure_functions(node* root);
void destroy_trie(node* root);

aho_corasick_matcher::aho_corasick_matcher(std::vector<char*> patterns){
    // Montar trie
    for(char* pattern : patterns){
        this->root = add_pattern(this->root,pattern);
    }
    // achar funções de falha (transições)
    find_failure_functions(this->root);
}

aho_corasick_matcher::~aho_corasick_matcher(){
    std::queue<node*> E;
    for( auto p : root->transitions){
        E.push(p.second);
    }
}

bool aho_corasick_matcher::match(const char* string){
    node* current = this->root;
    int size = strlen(string);
    for(int i = 0; i < size ; i++){
        // printf("c: %c\n",string[i]);
        //se não há transição com o caractere, acha o fallback(ou a raiz)
        while((! current->has(string[i])) && current != root) {current = current->fallback;};
        //se ainda não há, é raiz. avança pro proximo caractere
        if(! current->has(string[i])) continue;
        //segue a transição
        current = current->transitions[string[i]];
        //checa se é estado de aprovação
        auto aux = current;
        do {if (aux->match) return true;} while( (aux = aux->fallback) != root);
    }

    //se não achou nenhum estado de aprovação com nenhum caractere,
    //não houve match
    return false;
}


node* add_pattern_helper(node*,char*);
node* add_pattern(node* root, char* string){
    if(root == nullptr) root = new node(false);
    root = add_pattern_helper(root,string);
    return root;
}

void find_failure_functions(node* root){
    std::queue<node*> E;
    for( auto p : root->transitions){
        p.second->fallback = root;
        E.push(p.second);
    }
    while(!E.empty()){
        node* current = E.front();
        E.pop();
        for(auto p : current->transitions){
            if(p.second == nullptr) continue;
            E.push(p.second);
            node* f = current->fallback;
            while(! f->has(p.first) && f != root) f = f->fallback;
            if(f == root)
                p.second->fallback = root;
            else
                p.second->fallback = f->transitions[p.first];
        }
    }
}

node* add_pattern_helper(node* root, char* string){
    if(*string == '\0'){
        root->match = true;
    }
    else if( root->has(*string)){
        add_pattern_helper(root->transitions[*string],(string+1));
    }else{
        node* next = new node(false);
        next = add_pattern_helper(next,(string+1));

        char a = *string;
        root->transitions.insert(std::pair<char,node*>(a,next));
    }
  return root;
}

void destroy_trie(node* root){
    for(auto p : root->transitions){
        destroy_trie(p.second);
    }
    delete root;
}

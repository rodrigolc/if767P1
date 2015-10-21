// Rodrigo Lopes - rlc2
// (2015)
#include "kmp_matcher.hpp"
#include "util.hpp"
#include "cstring"

int* make_table(char* pattern);
int kmp_match(char* pattern, int* table,const char* string);

kmp_matcher::kmp_matcher(std::vector<char*> patterns){
    // Montar tabelas
    for(char* pattern : patterns){
        this->patterns.push_back(copy_string(pattern));
        this->tables.push_back(make_table(pattern));
    }
}

kmp_matcher::~kmp_matcher(){
    for(char* string : this->patterns){
        delete string;
    }
    for(int* table : this->tables){
        delete table;
    }
}

bool kmp_matcher::match(const char* string){
    int str_len = strlen(string);
    for(size_t i = 0; i < this->patterns.size();i++){
        if(kmp_match(this->patterns[i],this->tables[i],string) < str_len) return true;
    }
    return false;
}


int* make_table(char* pattern){
    int length = strlen(pattern);
    if(length == 0) return nullptr;
    int* table = new int[length];

    table[0] = -1;  // Caso especial de começo de string;
    if (length == 1) return table;
    table[1] = 0;   // Não há como ser != 0 no segundo char, pois não há
                    //sufixo proprio de um prefixo próprio de uma string de tamanho 2

    int c = 0;      // Posição da string que termina o prefixo que bate com o sufixo
                    //que termina antes na posição sendo lida.
    for (int i = 1; i < length; i++) {
        // Para cada posição, precisamos achar o tamanho do maior sufixo proprio do prefixo até essa posição
        //que seja igual a algum prefixo próprio da string
        // Mas só precisamos saber quantas posições anteriores deram match.
        table[i] = c;
        if(pattern[c] == pattern[i]){
            c++;
        }
        else{
            c = 0;
        }
    }
    return table;
}

int kmp_match(char* pattern, int* table, const char* string ){
    int pat_len = strlen(pattern); //HACK remover chamada?
    int str_len = strlen(string); //idem
    int c = 0;
    int i = 0;
    while(c+i < str_len){ //se passarmos do fim da string, nao tivemos match.
        if(pattern[i] == string[c+i]){ // Começo ou meio de possivel match
            if (i == pat_len - 1) return c; // Alcançamos o fim do padrão, tivemos match
            i++;
        }
        else if(table[i] == -1){ // Errou no começo, só precisa ir pro proximo
            c++;
        }
        else{   // Errou no meio do padrão, a proxima string candidato de match
                //está a i - table[i] de distância.
                // Isso pois precisamos avançar o mesmo que i voltar, para lermos
                //o próximo caractere.
            c += i - table[i];
            i = table[i];
        }
    }
    //não tendo match, retornamos o tamanho da string
    return str_len;
}

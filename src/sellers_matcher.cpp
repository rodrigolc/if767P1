// Rodrigo Lopes - rlc2
// (2015)
#include "sellers_matcher.hpp"
#include "util.hpp"
#include "cstring"

sellers_matcher::sellers_matcher(std::vector<char*> patterns,int distance){
    this->distance = distance;
    max_size = 0;
    for(char* pattern : patterns){
        this->patterns.push_back(copy_string(pattern));
        int size = strlen(pattern);
        this->sizes.push_back(size);
        if(size > max_size) max_size = size;
    }
}

sellers_matcher::~sellers_matcher(){
    for( char* s: patterns) delete s;
}

inline int min(int a, int b, int c){
    return a<b?(a < c? a:c):(b<c?b:c);
}

bool sellers_matcher::match(const char* string){
    int size = strlen(string);

    short * m = new short[(max_size+1)*(size+1)]; //só alocar o array uma vez.

    for(int p=0; p < patterns.size();p++){
        char* pattern = patterns[p];
        int psize = sizes[p];
        for(int i = 0; i <= size; i++){
            m[0*size+i] = 0;//linha 0 com valores 0
        }
        for(int i = 1; i <= psize; i++){
            m[i*size] = i;
            for(int j = 1; j <= size; j++){
                int d = 1;
                if( string[j-1] == pattern[i-1] ){
                    d = 0;
                }
                m[i*size+j] = min(m[(i-1) * size + j] + 1,m[i * size + j - 1] + 1,m[(i-1) * size + (j-1)] + d);
            }
        }

        for(int i = 1; i <= size; i++){
            if(m[(psize * size) + i] <= distance) {
                delete m;
                return true;
            }
        }
    }
    return false;
}

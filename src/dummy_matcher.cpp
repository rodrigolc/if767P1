// Rodrigo Lopes - rlc2
// (2015)
#include "dummy_matcher.hpp"
#include "util.hpp"
#include "cstring"

bool dumb_search(const char* pattern,const char* string){
    int string_length = strlen(string);
    int pat_length = strlen(pattern);
    for(int s = 0; s < string_length; s++){
        int c;
        for(c = 0; c < pat_length; c++){
            if( pattern[c] != string[c+s]) break;
            if(pattern[c] == '\0') return true;
            if(string[s+c] == '\0') return false;
        }
        if(pattern[c] == '\0') return true;
    }
    return false;
}

dummy_matcher::dummy_matcher(std::vector<char*> patterns){
    for(char* pattern : patterns){
        this->patterns.push_back(copy_string(pattern));
    }
}

dummy_matcher::~dummy_matcher(){
    for(char* string : this->patterns){
        delete string;
    }
}

bool dummy_matcher::match(int size,const char* string){
    for(char* pat:this->patterns){
        if ( dumb_search(pat,string) ){
            return true;
        }
    }
    return false;
}

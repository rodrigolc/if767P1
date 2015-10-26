// Rodrigo Lopes - rlc2
// (2015)
#include "wu_manber_matcher.hpp"
#include "util.hpp"
#include "cstring"

std::map<char,unsigned long> create_map(char* string,int size){
    std::map<char,unsigned long> m;
    int word_size = sizeof(unsigned long) * 8;
    for(int i = 0; i < size; i++ ){

        unsigned long bm = 0;
        char c = string[i];
        if(m.count(c)) continue;
        else{
            for(int j = 0; j < size; j++){
                bm <<= 1;
                if(c == string[j]){
                    bm += 1;
                }
            }
            bm <<= (word_size - size - 1);
            m[c] = bm;
            printf("%c %lu\n",c,bm);
        }
    }
    return m;
}

wu_manber_matcher::wu_manber_matcher(std::vector<char*> patterns,int distance){
    this->distance = distance;
    max_size = 0;
    for(char* pattern : patterns){
        this->patterns.push_back(copy_string(pattern));
        int size = strlen(pattern);
        this->sizes.push_back(size);
        if(size > max_size) max_size = size;
        this->maps.push_back(create_map(pattern,size));
    }
}

wu_manber_matcher::~wu_manber_matcher(){
    for( char* s: patterns) delete s;
}
bool wu_manber_matcher::match(const char* string){
    int size = strlen(string);
    unsigned long** R = new unsigned long*[distance+1];
    for(int i = 0; i <= distance; i++){
        R[i] = new unsigned long[size+1];
        unsigned long start = (~0) & (~((0) >> i));
        R[i][0] = start;
    }
    for(int p = 0; p < patterns.size(); p++){
        std::map<char,unsigned long>& m = maps[p];

        for(int j = 1; j <= size; j++){
            char c = string[j-1];
            unsigned long mask;
            if(m.count(c) > 0){
                mask = m[c];
            }
            else{
                mask = 0;
            }
            R[0][j] = ( ((R[0][j-1]>>1) | shift_r_correct) & mask);
        }

        for(int i = 1; i <= distance ; i++){
            // printf("a%lu\n",R[i][0]);
            for(int j = 1; j <= size; j++){
                // printf("b%d %lu\n",i,R[i][j]);
                char c = string[j-1];
                unsigned long mask;
                if(m.count(c) > 0){
                    mask = m[c];
                }
                else{
                    mask = 0;
                }
                R[i][j] = (((R[i][j-1]>>1) | shift_r_correct) & mask) | (((R[i-1][j-1] | ( R[i-1][j])) >> 1) | shift_r_correct) | R[i-1][j-1];

            }

        }
        unsigned long res_mask = shift_r_correct >> (sizes[p] - 1);
        for(int i = 0; i <= distance; i++){
            for(int j = 1; j <= size; j++){
                if(R[i][j] & res_mask){
                    // printf("b%d %lu\n",i,R[i][j]);
                    for(int i = 0; i <= distance; i++){
                        delete R[i];
                    }
                    delete R;
                    return true;
                }
            }
        }
    }


    for(int i = 0; i <= distance; i++){
        delete R[i];
    }
    delete R;

    return false;
}

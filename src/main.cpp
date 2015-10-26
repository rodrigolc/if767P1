// Rodrigo Lopes - rlc2
// (2015)

//ponto de entrada principal do programa, seleciona algoritmo, faz parsing das
//opções, executa o algoritmo.

#include <unistd.h>
#include <getopt.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "kmp_matcher.hpp"
#include "aho_corasick_matcher.hpp"
#include "sellers_matcher.hpp"
#include "util.hpp"

// contantes do programa

struct option long_options[] = { //opções por extenso para getopt_long
	{ "edit", required_argument, NULL, 'e' },
	{ "pattern", required_argument, NULL, 'p' },
	{ "help", no_argument, NULL, 'h' },
	{ 0, 0, 0, 0 }
};

void display_help();

int main( int argc, char* argv[] ){
	int edit_distance = 0;
	bool approx_matching = false;
    std::vector<char*> patterns;
    std::vector<char*> files;
	char* pattern = nullptr;
	char* pattern_file = nullptr;
	char option;

    matcher* M;

	while ( ( option = getopt_long( argc, argv, "e:p:h", long_options, NULL ) ) != -1 ){
		switch( option ){
			case 'e':
				edit_distance = atoi( optarg ); // checar por erros?
				approx_matching = true;
				break;
			case 'p':
				pattern_file = copy_string( optarg );
				break;
            case 'h':
                display_help();
                return 0;
                break;
		}
	}

    if (optind < argc) {
        pattern = copy_string(argv[optind]);
        patterns.push_back(pattern);
        optind++;
    }else{
        printf("missing pattern\n");
        exit(1);
        fflush(stdout);
    }
    if (optind < argc) {
        while( optind < argc ){
            files.push_back(copy_string(argv[optind]));
            optind++;
        }
    }else{
        printf("missing file\n");
        exit(1);
        fflush(stdout);
    }

    if( pattern_file ){
        std::ifstream pat_file( pattern_file, std::ifstream::in );

        if( !pat_file ){
            if( pattern ) delete pattern;
            if( pattern_file ) delete pattern_file;
            printf( "can't read from file\n" );
            exit( 1 );
        }

        std::string line;

        while( getline( pat_file, line ) ){
            char* pat = copy_string(line.c_str());
            if(pat[strlen(pat)-1] == '\n') pat[strlen(pat) - 1 ] = '\0';
            patterns.push_back(pat);
        }
    }

    if (approx_matching){
        M = new sellers_matcher(patterns,edit_distance);
        
    }else{
		if(patterns.size() == 1) //se há um só padrão, usa kmp
		{
			M = new kmp_matcher(patterns);
		}
		else //com mais padrões, usa aho-corasick, que procura em O(n) com varios padroes
		{
        	M = new aho_corasick_matcher(patterns);
		}
    }

    for(char* file : files){
        std::ifstream infile(file,std::ifstream::in);
        std::string line;
        while( getline( infile, line ) ){
            if (M->match(line.c_str())){
                printf("%s\n",line.c_str());
            }
        }
    }
	return 0;
}


void display_help(){
    // TODO help
    printf("TODO HELP\n");
}

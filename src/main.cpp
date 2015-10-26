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
#include "dummy_matcher.hpp"
#include "util.hpp"

// contantes do programa

struct option long_options[] = { //opções por extenso para getopt_long
	{ "algorithm", required_argument, NULL, 'a' },
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
	int max_pat_size = 0;
	char algoritmo_especifico = 0;
    matcher* M;

	while ( ( option = getopt_long( argc, argv, "e:p:ha:", long_options, NULL ) ) != -1 ){
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
			case 'a':
                algoritmo_especifico = optarg[0];
				break;
		}
	}

    if (optind < argc) {
        pattern = copy_string(argv[optind]);
        patterns.push_back(pattern);
		int size = strlen(pattern);
		if(size > max_pat_size ) max_pat_size = size;
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
			int size = strlen(pat);
            if(pat[size-1] == '\n') pat[size - 1 ] = '\0';
			if(size > max_pat_size ) max_pat_size = size;
            patterns.push_back(pat);
        }
    }
	if(algoritmo_especifico){
		if(algoritmo_especifico == 'k'){
			M = new kmp_matcher(patterns);
		}
		else if(algoritmo_especifico == 's'){
			M = new sellers_matcher(patterns,edit_distance);
		}
		else if(algoritmo_especifico == 'a'){
			M = new aho_corasick_matcher(patterns);
		}
		else if(algoritmo_especifico == 'd'){
			M = new dummy_matcher(patterns);
		}else{
			printf("Algoritmo inválido \"%c\"\n",algoritmo_especifico);
			display_help();
			exit(1);
		}
	}else{
		if (approx_matching){
			// if(max_pat_size <= sizeof(long) * 8){//tamanho da word do sistema
			// 	M = new wu_manber_matcher(patterns,edit_distance);
			// }
	        // else{
			M = new sellers_matcher(patterns,edit_distance);
			// }

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
	printf("pmt [-a {a,k,s,d}] [-e NUM] [-p ARQUIVO] PADRAO ARQUIVO [ARQUIVO2...]\n");
	printf("Busca padrões em arquivos\n\n");
	printf("Usa algoritmos:\n");
	printf("Aho-Corasick\n");
	printf("Sellers\n");
	printf("KMP\n");
	printf("Dummy(Força Bruta)\n\n");
    printf("\t--algorithm -a ALGORITMO\t\tEscolhe algoritmo\n");
	printf("\t--edit -e NUM\t\tDefine distancia de edição.\n\t\tSe usado, usará algoritmos aproximados\n\t\texceto se um algoritmo exato for informado usando \"-a\"\n");
	printf("\t--pattern -p ARQUIVO\t\tfaz a busca com os padrões em ARQUIVO, um por linha\n");
	printf("\t--help -h\t\tMostra essa ajuda\n");
}

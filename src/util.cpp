// Rodrigo Lopes - rlc2
// (2015)
#include "util.hpp"
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>

// aloca e copia uma string
char* copy_string( const char* string ){
	int size = strlen(string);
    char* ret = new char[size+1];
	strcpy( ret, string );
	return ret;
}

// REMOVIDO
// Shells já fazem expansão de wildcards.
// Expandir manualmente adiciona complexidade ao programa, adicionando pontos de falha.
// Além disso, shells diferentes lidam com wildcards diferentemente. Implementar
//manualmente a expansão pode ir de encontro com as práticas da shell do usuário.
//
// #include <glob.h>
// // lista arquivos que batem com as expressões providas
// std::vector<char*> find_files(std::vector<char*> expressions){
//     int flags = GLOB_ERR | GLOB_MARK;
//     glob_t glob_results;
//     int ret;
//     for (char* exp : expressions){
//         if ( (ret = glob(exp, flags, NULL, &glob_results)) ){
//             if (ret == GLOB_NOMATCH){
//                 globfree(&glob_results);
//                 fprintf(stderr,"Nenhum resultado para a expressão \"%s\"\n",exp);
//                 return std::vector<char*>(); //lista vazia.
//             }
//             else if (ret == GLOB_ABORTED){
//                 globfree(&glob_results);
//                 fprintf(stderr,"Erro lendo arquivos para a expressão \"%s\"\n",exp);
//                 return std::vector<char*>(); //lista vazia.
//             }
//             else {
//                 fprintf(stderr,"Erro crítico com expressão \"%s\"\n",exp);
//                 exit(2);
//             }
//         }
//
//
//
//
//         flags = GLOB_ERR | GLOB_MARK | GLOB_APPEND;
//     }
// }

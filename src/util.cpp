// Rodrigo Lopes - rlc2
// (2015)
#include <cstring>

// aloca e copia uma string
char* copy_string( const char* string ){
	int size = strlen(string);
    char* ret = new char[size+1];
	strcpy( ret, string );
	return ret;
}

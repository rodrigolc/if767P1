// Rodrigo Lopes - rlc2
// (2015)
#include <vector>

class matcher{
public:
    matcher(); //construtor padrão, nunca usado. necessario para classes derivadas
    matcher(std::vector<char*> patterns); //construtor
    virtual ~matcher(); //destrutor
    virtual bool match(const char* string) = 0; //procura a string usando o padrão
};

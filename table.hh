#ifndef TABLE_HH
#define TABLE_HH
#include <map>
#include <vector>
#include "tree.hh"

//B Códigos de retorno 
#define ERR_UNDECLARED 10 //2.2
#define ERR_DECLARED 11 //2.2
#define ERR_VARIABLE 20 //2.3
#define ERR_FUNCTION 21 //2.3

//2.1 Campos
enum class NatureType {
    LITERAL,
    IDENTIFICADOR
    FUNCAO
};

struct Symbol {
    int line_number;
    NatureType natureType;
    Type type; 
    //Node* assoc_node;
};

//typedef std::map<TokenVal, Symbol> SymbolTable;

Type type_inference (Type symbol1, Type symbol2);
int error_identifier (NatureType expected, NatureType received);
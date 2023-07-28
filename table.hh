#ifndef TABLE_HH
#define TABLE_HH
#include <vector>
#include <map>
#include "tree.hh"

using namespace std;

enum class NatType {
    LIT,
    ID,
    FUNC
};

//B Códigos de retorno 
#define ERR_UNDECLARED 10 //2.2
#define ERR_DECLARED 11 //2.2
#define ERR_VARIABLE 20 //2.3
#define ERR_FUNCTION 21 //2.3

struct Table {
    int line;
    NatType nature;
    string type;
    AstNode* data;
};


//Structure to declare whenever we push/pop tables
struct StackTable {
    vector<Table> stack_table {};

    void push_table(Table& tb);
    void pop_table(Table& tb); //Remove the table on the top of the program
    Table& return_top(); //Pick up the last table whenever needed
    int find_symbol_table(string value); //Returned the index found in the table

    bool value_declared(string value);

    Table get_symbol_table(string value);
};

TkType inference_type(TkType id_type_1, TkType id_type_2);

/*
Notas de aula
Empilha primeira tabela antes inicio do programa

Fecha apos programa
Fecha apos lista de comandos simples
FREE OPCIONAL

uso correto tipos (ou eh variavel ou eh funcao)

Achar a entrada da tabela que tem o lexema
*/
#endif  //TABLE_HH
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

//Create a pair format to save the following format:'
// type symbol
typedef map<string, Table> SymbolTablePair;

//Structure to declare whenever we push/pop tables
struct StackTable {
    vector<SymbolTablePair> stack_table {};

    void initialize_stack();
    void push_table(SymbolTablePair& tb);
    void pop_table(); //Remove the table on the top of the program
    SymbolTablePair& return_top(); //Pick up the last table whenever needed
    int find_symbol_table(string value); //Returned the index found in the table

    bool value_declared(string value);

    Table get_symbol_table(string value);

    void stack_up(string tk_value, Table symbol);
};

TkType inference_type(TkType id_type_1, TkType id_type_2);

//Function to convert one value to another
TkType implicit_conversion(TkType type, TkType new_type);

int get_bad_usage_err(TkType expected, TkType received);
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
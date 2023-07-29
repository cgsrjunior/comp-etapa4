#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include "table.hh"

using namespace std;

void StackTable::initialize_stack(){
    this->stack_table.push_back(SymbolTablePair{});
}

void StackTable::push_table(SymbolTablePair& tb) { 
    this->stack_table.push_back(tb); 
}

void StackTable::pop_table() { 
    this->stack_table.pop_back(); 
}

SymbolTablePair& StackTable::return_top(){
    this->stack_table.back();
}

//This code will find the column that the element was given
//If a element cannot be found, return -1
int StackTable::find_symbol_table(string value) {
    int i = this->stack_table.size()-1;
    for (i; i>=0; i--) {
        if (this->stack_table[i].contains(value)){
            break;
        }
    }
    return i;
}

bool StackTable::value_declared(string value){
    return find_symbol_table(value) >= 0;
}

void StackTable::stack_up(string tk_value, Table symbol){
    if (this->return_top().contains(tk_value)) {
        this->return_top().insert({tk_value, symbol});
    }
}

TkType inference_type (TkType id_type_1, TkType id_type_2) {
/*
 *  Dado dois simbolos, faz inferência e retorna o tipo.
 */

    if (id_type_1 == id_type_2) {
        return id_type_1;
    }
    else if (id_type_1 == TkType::TK_LIT_FLOAT && id_type_2 == TkType::TK_LIT_INT){
        return TkType::TK_LIT_FLOAT;
    }        
    else if (id_type_1 == TkType::TK_LIT_BOOL && id_type_2 == TkType::TK_LIT_INT){
        return TkType::TK_LIT_INT;
    }
    else if (id_type_1 == TkType::TK_LIT_BOOL && id_type_2 == TkType::TK_LIT_FLOAT){
        return TkType::TK_LIT_FLOAT;
    }
    else
         return TkType::TK_TYPE_ERROR;
}

int get_bad_usage_err(NatType expected, NatType received) {
    if (expected != received)
        switch (expected) {
            case NatType::ID:
                return ERR_VARIABLE;
            case NatType::FUNC:
                return ERR_FUNCTION;
            case NatType::LIT: // não acontece, apenas para omitir warning
                return 0;
        }
    return 0;
}


Table StackTable::get_symbol_table(string key) {
    int index = this->find_symbol_table(key);
    if (index >= 0) {
        return this->stack_table[index][key];
    }
    else exit(ERR_UNDECLARED);
}

/*
int get_incompatible_type(){

}
*/
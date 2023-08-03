#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "table.hh"

using namespace std;

//This code will find the column that the element was given
//If a element cannot be found, return -1
int StackTable::find_symbol_table(string token_value) {
    int i = 0;
    for (i = this->stack_table.size()-1; i>=0; i--) {
        if (this->stack_table[i].label.compare(token_value) == 0){
            break;
        }
    }
    return i;
}


//This function should be used to check if we launch a declared or undeclared
// variable error
bool StackTable::value_declared(string value){
    return find_symbol_table(value) >= 0;
}

void StackTable::create_variable_entry(string token_value, Symbol ast_symbol){
    //Check if variable exists before and in case of non-existant,
    //create the variable entry in the stack
    SymbolList new_data{
        token_value,
        ast_symbol
    };
        this->stack_table.push_back(new_data);
}

void StackTable::create_atribution_entry(string token_value, Symbol ast_symbol){
    //Check if variable exists before and in case of existant,
    //create the atribution symbol entry in the stack
    if(value_declared(token_value)){
        SymbolList new_data{
            token_value,
            ast_symbol
        };
        this->stack_table.push_back(new_data);
    }
    else{
        exit(ERR_UNDECLARED);
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
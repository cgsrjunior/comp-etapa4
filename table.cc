#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "table.hh"

using namespace std;

void StackTable::push_table(Table& tb) { 
    this->stack_table.push_back(tb); 
}

void StackTable::pop_table(Table& tb) { 
    this->stack_table.pop_back(); 
}

Table& StackTable::return_top(){
    this->stack_table.back();
}

//This code will find the column that the element was given
//If a element cannot be found, return -1
int StackTable::find_symbol_table(string value) {
    int i = this->stack_table.size()-1;
    for (i; i>=0; i--) {
        if (this->stack_table[i].data->lex.token_val.find(value)){
            break;
        }
    }
    return i;
}

bool StackTable::value_declared(string value){
    return find_symbol_table(value) >= 0;
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

int get_incompatible_type();
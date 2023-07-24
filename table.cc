#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "table.hh"

void StackTable::push_table(Table& tb) { 
    this->stack_table.push_back(tb); 
}

void StackTable::pop_table(Table& tb) { 
    this->stack_table.pop_back(); 
}
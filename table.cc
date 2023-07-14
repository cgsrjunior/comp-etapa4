#include "table.hh"
#include <iostream>

Type type_inference (Type symbol1, Type symbol2) {

    if (symbol1 == symbol2)
        return symbol1;

    if (symbol1 == Type::FLOAT || symbol2 == Type::FLOAT)
        return Type::FLOAT;

    if (symbol1 == Type::INTEGER || symbol2 == Type::INTEGER)
        return Type::INTEGER;

    if (symbol1 == Type::CHARACTER) {
        return symbol2;
    } else if (symbol2 == Type::CHARACTER) {
        return symbol1;
    }

    else return Type::ERROR;
}

//Início do item 2.3 Uso correto de identificadores
int error_identifier (NatureType expected, NatureType response) {
    if (expected != response)
        switch (expected) {
            case NatureType::VARIABLE:
                return ERR_VARIABLE;
            case NatureType::FUNCTION:
                return ERR_FUNCTION;
            case NatureType::LITERAL: // para omitir warning
                return 0;
        }
    return 0;
}

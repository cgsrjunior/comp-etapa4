#pragma once
#include <vector>
#include <string>
#include <memory>

using namespace std;

enum class TkType {
    TK_SP_CHAR, // char
    TK_PR, // std::string
    TK_OC, // std::string
    TK_ID, // std::string
    TK_LIT_INT, // int
    TK_LIT_FLOAT, // float
    TK_LIT_BOOL, // bool
};

const vector<char> invalid_chars {',', ';', '(', ')', '{', '}', '[', ']'};

struct LexValue {
    int line_number;
    TkType token_type;
    string token_val;
};

struct AstNode {
    public:
        LexValue lex;
        vector<shared_ptr<AstNode>> children;
        bool func_call = false;

        //Constructor - create only node without child
        AstNode(int number, TkType token_tp, string value);

        //Function to add child
        void add_child(AstNode *node);

        //Convert labels into string
        string formatstring();

        void reg_func_call(bool value);
};

//Smart pointer for the tree
typedef shared_ptr<AstNode> smart_pointer;

//Function to export the tree
void exporta(void* tree);

//Function to print the tree
void print_tree(shared_ptr<AstNode> tree);
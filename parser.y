
/* Trabalho de Compiladores - Cleiber Rodrigues e Cintia Valente */
/* Cartões: 00270139 - 00228540 */

%{
#include <iostream>
#include <memory>
#include "table.hh"
extern int get_line_number(void);
extern void *arvore;
int yylex(void);
int yyerror (const char *message);
using namespace std;
StackTable program_table{};
vector<SymbolTablePair> global_variables = {};
%}

%code requires{
      #include <memory>
      #include "tree.hh"
      #include "table.hh"
}

%union {
      AstNode* valor_lexico;
}

%define parse.error verbose

%token<valor_lexico> TK_PR_INT
%token<valor_lexico> TK_PR_FLOAT
%token<valor_lexico> TK_PR_BOOL
%token<valor_lexico> TK_PR_IF
%token<valor_lexico> TK_PR_ELSE
%token<valor_lexico> TK_PR_WHILE
%token<valor_lexico> TK_PR_RETURN
%token<valor_lexico> TK_OC_LE
%token<valor_lexico> TK_OC_GE
%token<valor_lexico> TK_OC_EQ
%token<valor_lexico> TK_OC_NE
%token<valor_lexico> TK_OC_AND
%token<valor_lexico> TK_OC_OR
%token<valor_lexico> TK_OC_MAP
%token<valor_lexico> TK_IDENTIFICADOR
%token<valor_lexico> TK_LIT_INT
%token<valor_lexico> TK_LIT_FLOAT
%token<valor_lexico> TK_LIT_FALSE
%token<valor_lexico> TK_LIT_TRUE
%token<valor_lexico> TK_ERRO
%token<valor_lexico> '-' '!' '*' '/' '%' '+' '<' '>' '&' '|' '='

%type<valor_lexico> programa
%type<valor_lexico> list_decl
%type<valor_lexico> decl
%type<valor_lexico> var
%type<valor_lexico> list_id
%type<valor_lexico> type
%type<valor_lexico> func
%type<valor_lexico> list_param
%type<valor_lexico> body
%type<valor_lexico> list_cmd
%type<valor_lexico> cmd
%type<valor_lexico> cmd_flux_ctrl
%type<valor_lexico> cmd_func_call
%type<valor_lexico> func_call_param
%type<valor_lexico> unary_operand
%type<valor_lexico> bin_sec_expr
%type<valor_lexico> bin_thr_expr
%type<valor_lexico> bin_fou_expr
%type<valor_lexico> bin_fif_expr
%type<valor_lexico> bin_six_expr
%type<valor_lexico> bin_sev_expr
%type<valor_lexico> expr
%type<valor_lexico> expr_1
%type<valor_lexico> expr_2
%type<valor_lexico> expr_3
%type<valor_lexico> expr_4
%type<valor_lexico> expr_5
%type<valor_lexico> unary_expr
%type<valor_lexico> parenthesis_prec
%type<valor_lexico> operand
%type<valor_lexico> list_arg
%type<valor_lexico> cmd_var
%type<valor_lexico> cmd_atrib
%type<valor_lexico> init_var
%type<valor_lexico> cmd_return
%type<valor_lexico> list_id_atrib
%type<valor_lexico> id_atrib
%type<valor_lexico> lit
%type<valor_lexico> id_label
%type<valor_lexico> name_func
%type<valor_lexico> id_param

%start programa

%%

programa    : {program_table.initialize_stack();} list_decl {$$ = $2; arvore = $$; program_table.pop_table();}
            ;
        
list_decl   : decl list_decl {
              if($2!=nullptr && $1!=nullptr){
                  $$ = $1;
                  $$->add_child($2);
               }
               else if($1 != nullptr){
                  $$ = $1;
               }
               else if($2 !=nullptr){
                  $$ = $2;
               }
               else
                  $$ = nullptr;
            }
            | {$$ = nullptr;}
            ;

decl        : var  {$$ = $1; global_variables.clear();}
            | func {$$ = $1;}
            ;

var         : type list_id ';' {$$ = nullptr;
                  for(auto p_key : global_variables){
                        Table& symbol = p_key.second;
                        symbol.type = $1->get_type();
                        program_table.stack_up(p_key);
                  }
                  delete $1;
            }
            ;

list_id     : list_id ',' id_label {$$ = nullptr;}
            | id_label {$$ = nullptr;}
            ;

type        : TK_PR_INT   {$$ = nullptr;}
            | TK_PR_FLOAT {$$ = nullptr;}
            | TK_PR_BOOL  {$$ = nullptr;}
            ;

func        : name_func {
               if (program_table.value_declared($1->get_type())) {
			send_error_message($1, ERR_DECLARED);
                  exit(ERR_DECLARED);
               }
               Table symbol{
                  $1->get_line_number(),
                  NatType::ID,
                  TkType::TK_TYPE_ERROR,
                  nullptr
               };
               program_table.stack_up   
            } '(' list_param ')' TK_OC_MAP type body {$$ = $1; $$->add_child($7);}
            ;


list_param  : list_param ',' id_param {$$ = nullptr;}
            | id_param {$$ = nullptr;}
            | {$$ = nullptr;}
            ;


body        : '{' list_cmd '}' {$$ = $2;}
            ;


list_cmd    :  cmd ';' list_cmd  {
               if($3 != nullptr && $1 != nullptr){
                  $$  = $1;
                  $$->add_child($3);
               }
               else if($1 != nullptr){
                  $$ = $1;
               }
               else if($3 != nullptr){
                  $$ = $3;
               }
               else
                  $$ = nullptr;
                  
            }
            |  {$$ = nullptr;}
            ;

cmd         : cmd_var         {$$ = $1; /*cout << "<=" << endl;*/}
            | cmd_atrib       {$$ = $1;}
            | cmd_func_call   {$$ = $1;}
            | cmd_return      {$$ = $1; /*cout << "return" << endl;*/}
            | cmd_flux_ctrl   {$$ = $1;}
            | body            {$$ = $1; /*cout << "body" << endl;*/}

            ;

cmd_var     : type list_id_atrib {$$ = $2; /*cout << "getting atrib rule" << endl; */}
            ;

list_id_atrib   : list_id_atrib ',' id_atrib{
                        $$ = $1;
                }
                | list_id_atrib ',' init_var{
                  if($1 != nullptr && $3 != nullptr)
                  {
                        $$ = $1;
                        $$->add_child($3);
                  }
                  else if ($1 != nullptr){
                        $$=$1;
                  }
                  else if($3 != nullptr){
                        $$=$3;
                  }
                  else
                        $$=nullptr;
                        
                }

                | init_var {$$ = $1;}
                | id_atrib {$$ = nullptr;}
                ;

init_var        : id_label TK_OC_LE lit{
                  $$ = $2;
                  $$->add_child($1);
                  $$->add_child($3);
                }
                ;

id_atrib        : id_label {$$ = nullptr;}
                ;


lit             : TK_LIT_INT   {$$ = $1;}
                | TK_LIT_FLOAT {$$ = $1;}
                | TK_LIT_TRUE  {$$ = $1;}
                | TK_LIT_FALSE {$$ = $1;}
                ;

id_label: TK_IDENTIFICADOR {
            if(program_table.value_declared($1->get_type())){
                  //TODO send error message
                  //TODO exit program
                  send_error_message($1, ERR_DECLARED);
                  exit(ERR_DECLARED);
            }
            Table symbol{
                  $1->get_line_number(),
                  NatType::ID,
                  TkType::TK_TYPE_ERROR,
                  nullptr
            };
            new_pair = make_pair($1->get_type, symbol);
            //Adding global variables to the stack
            global_variables.push_back(new_pair);
            $$=nullptr; delete $1;
        }
        ;     



cmd_flux_ctrl   : TK_PR_IF '(' expr ')' body {$$ = $1; $$->add_child($3); $$->add_child($5);}
                | TK_PR_IF '(' expr ')' body TK_PR_ELSE body {$$ = $1; $$->add_child($3); $$->add_child($5); $$->add_child($7);}
                | TK_PR_WHILE '(' expr ')' body {$$ = $1; $$->add_child($3); $$->add_child($5);}


cmd_func_call: name_func '(' list_arg ')'    {$$ = $1; $$->reg_func_call(true); $$->add_child($3);}
             ;

func_call_param : name_func '(' list_arg ')' {$$ = $1; $$->add_child($3);}
                ;


unary_operand : '-'     {$$ = $1;}
              | '!'     {$$ = $1;}
              ;

bin_sec_expr : '*'      {$$ = $1;}
             | '/'      {$$ = $1;}
             | '%'      {$$ = $1;}
             ;

bin_thr_expr : '+'      {$$ = $1;}
             | '-'      {$$ = $1;}
             ;

bin_fou_expr : '<'      {$$ = $1;}
             | '>'      {$$ = $1;}
             | TK_OC_LE {$$ = $1;}
             | TK_OC_GE {$$ = $1;}
             ;

bin_fif_expr : TK_OC_NE {$$ = $1;}
             | TK_OC_EQ {$$ = $1;}
             ;

bin_six_expr: TK_OC_AND {$$ = $1;}
             ;

bin_sev_expr: TK_OC_OR {$$ = $1;}
             ;

expr: expr_1 {$$ = $1;} 
    | expr bin_sev_expr expr_1 {$$ = $2; $$->add_child($1); $$->add_child($3);}
    | {$$ = nullptr;}
    ;

expr_1: expr_2 {$$ = $1;}
      | expr_1 bin_six_expr expr_2 {$$ = $2; $$->add_child($1); $$->add_child($3);}
      ;

expr_2: expr_3 {$$ = $1;}
      | expr_2 bin_fif_expr expr_3 {$$ = $2; $$->add_child($1); $$->add_child($3);}
      ;

expr_3: expr_4                     {$$ = $1;}
      | expr_3 bin_fou_expr expr_4 {$$ = $2; $$->add_child($1); $$->add_child($3);}
      ;

expr_4: expr_5                     {$$ = $1;}
      | expr_4 bin_thr_expr expr_5 {$$ = $2; $$->add_child($1); $$->add_child($3);}
      ;

expr_5: unary_expr                     {$$ = $1;}
      | expr_5 bin_sec_expr unary_expr {$$ = $2; $$->add_child($1); $$->add_child($3);}
      ;

unary_expr: parenthesis_prec               {$$ = $1;}
          | unary_operand parenthesis_prec {$$ = $1; $$->add_child($2); /* cout << $2 << endl; */}
          ;

parenthesis_prec    :  operand      {$$ = $1;}
                    | '(' expr ')'  {$$ = $2;}
                    ;

operand     : id_label        {$$ = $1;}
            | lit             {$$ = $1;}
            | func_call_param {$$ = $1;}
            ;


list_arg    : list_arg ',' expr {$$ = $3; $$->add_child($1);}
            | expr {$$ = $1;}
            ;


cmd_atrib   : id_label '=' expr {$$ = $2; $$->add_child($1); $$->add_child($3);}
            ;

cmd_return  : TK_PR_RETURN expr {$$ = $1; $$->add_child($2);}
            ;
 

name_func: TK_IDENTIFICADOR {$$ = $1;}
         ;     

id_param: type TK_IDENTIFICADOR {$$ = nullptr; delete $2;}
        ;

%%
int yyerror (const char *message)
{
    printf("Error line %d: %s\n", get_line_number(), message);
    return 1;
}
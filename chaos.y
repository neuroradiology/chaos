%{

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utilities/platform.h"
#include "utilities/language.h"
#include "utilities/helpers.h"
#include "symbol.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);

bool is_interactive = true;
%}

%union {
    bool bval;
    int ival;
    float fval;
    char *sval;
}

%token<bval> T_TRUE T_FALSE
%token<ival> T_INT
%token<fval> T_FLOAT
%token<sval> T_STRING T_VAR
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT T_EQUAL
%token T_LEFT_BRACKET T_RIGHT_BRACKET T_LEFT_CURLY_BRACKET T_RIGHT_CURLY_BRACKET T_COMMA T_COLON
%token T_NEWLINE T_QUIT
%token T_PRINT
%token T_VAR_BOOL T_VAR_NUMBER T_VAR_STRING T_VAR_ARRAY T_VAR_DICT
%token T_DEL
%token T_SYMBOL_TABLE
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE

%type<ival> expression
%type<fval> mixed_expression
%type<sval> variable
%type<sval> arraystart
%type<ival> array

%start parser

%%

parser:
    | parser line                                                   { is_interactive ? printf("%s ", __SHELL_INDICATOR__) : printf(""); }
;

line: T_NEWLINE
    | mixed_expression T_NEWLINE                                    { printf("%f\n", $1); }
    | expression T_NEWLINE                                          { printf("%i\n", $1); }
    | variable T_NEWLINE                                            { if ($1[0] != '\0' && is_interactive) printSymbolValueEndWithNewLine(getSymbol($1)); }
    | T_QUIT T_NEWLINE                                              { is_interactive ? printf("%s\n", __BYE_BYE__) : printf(""); exit(0); }
    | T_PRINT print T_NEWLINE                                       { }
    | T_SYMBOL_TABLE T_NEWLINE                                      { printSymbolTable(); }
;

print: T_VAR T_LEFT_BRACKET T_INT T_RIGHT_BRACKET                   { printSymbolValueEndWithNewLine(getArrayElement($1, $3)); }
;
print: T_VAR T_LEFT_BRACKET T_MINUS T_INT T_RIGHT_BRACKET           { printSymbolValueEndWithNewLine(getArrayElement($1, -$4)); }
;
print: T_VAR                                                        { printSymbolValueEndWithNewLine(getSymbol($1)); }
;
print: T_INT                                                        { printf("%i\n", $1); }
;
print: T_FLOAT                                                      { printf("%f\n", $1); }
;
print: T_STRING                                                     { printf("%s\n", $1); }
;

mixed_expression: T_FLOAT                                           { $$ = $1; }
    | mixed_expression T_PLUS mixed_expression                      { $$ = $1 + $3; }
    | mixed_expression T_MINUS mixed_expression                     { $$ = $1 - $3; }
    | mixed_expression T_MULTIPLY mixed_expression                  { $$ = $1 * $3; }
    | mixed_expression T_DIVIDE mixed_expression                    { $$ = $1 / $3; }
    | T_LEFT mixed_expression T_RIGHT                               { $$ = $2; }
    | expression T_PLUS mixed_expression                            { $$ = $1 + $3; }
    | expression T_MINUS mixed_expression                           { $$ = $1 - $3; }
    | expression T_MULTIPLY mixed_expression                        { $$ = $1 * $3; }
    | expression T_DIVIDE mixed_expression                          { $$ = $1 / $3; }
    | mixed_expression T_PLUS expression                            { $$ = $1 + $3; }
    | mixed_expression T_MINUS expression                           { $$ = $1 - $3; }
    | mixed_expression T_MULTIPLY expression                        { $$ = $1 * $3; }
    | mixed_expression T_DIVIDE expression                          { $$ = $1 / $3; }
    | expression T_DIVIDE expression                                { $$ = $1 / (float)$3; }
;

expression: T_INT                                                   { $$ = $1; }
    | expression T_PLUS expression                                  { $$ = $1 + $3; }
    | expression T_MINUS expression                                 { $$ = $1 - $3; }
    | expression T_MULTIPLY expression                              { $$ = $1 * $3; }
    | T_LEFT expression T_RIGHT                                     { $$ = $2; }
;

variable: T_VAR                                                     { $$ = $1; }
    | variable T_EQUAL T_TRUE                                       { updateSymbolBool($1, $3); $$ = ""; }
    | variable T_EQUAL T_FALSE                                      { updateSymbolBool($1, $3); $$ = ""; }
    | variable T_EQUAL T_INT                                        { updateSymbolInt($1, $3); $$ = ""; }
    | variable T_EQUAL T_FLOAT                                      { updateSymbolFloat($1, $3); $$ = ""; }
    | variable T_EQUAL T_STRING                                     { updateSymbolString($1, $3); $$ = ""; }
    | variable T_EQUAL T_VAR                                        { updateSymbolByClonning($1, $3); $$ = ""; }
    | T_DEL variable                                                { removeSymbolByName($2); $$ = ""; }
    | T_DEL variable T_LEFT_BRACKET T_INT T_RIGHT_BRACKET           { removeArrayElement($2, $4); $$ = ""; }
    | T_DEL variable T_LEFT_BRACKET T_MINUS T_INT T_RIGHT_BRACKET   { removeArrayElement($2, -$5); $$ = ""; }
    | variable T_LEFT_BRACKET T_INT T_RIGHT_BRACKET                 { if ($1[0] != '\0' && is_interactive) printSymbolValueEndWithNewLine(getArrayElement($1, $3)); $$ = ""; }
    | variable T_LEFT_BRACKET T_MINUS T_INT T_RIGHT_BRACKET         { if ($1[0] != '\0' && is_interactive) printSymbolValueEndWithNewLine(getArrayElement($1, -$4)); $$ = ""; }
    | variable T_LEFT_BRACKET T_INT T_RIGHT_BRACKET T_EQUAL T_TRUE              { updateArrayElementBool($1, $3, $6); $$ = ""; }
    | variable T_LEFT_BRACKET T_MINUS T_INT T_RIGHT_BRACKET T_EQUAL T_TRUE      { updateArrayElementBool($1, -$4, $7); $$ = ""; }
    | variable T_LEFT_BRACKET T_INT T_RIGHT_BRACKET T_EQUAL T_FALSE             { updateArrayElementBool($1, $3, $6); $$ = ""; }
    | variable T_LEFT_BRACKET T_MINUS T_INT T_RIGHT_BRACKET T_EQUAL T_FALSE     { updateArrayElementBool($1, -$4, $7); $$ = ""; }
    | variable T_LEFT_BRACKET T_INT T_RIGHT_BRACKET T_EQUAL T_INT               { updateArrayElementInt($1, $3, $6); $$ = ""; }
    | variable T_LEFT_BRACKET T_MINUS T_INT T_RIGHT_BRACKET T_EQUAL T_INT       { updateArrayElementInt($1, -$4, $7); $$ = ""; }
    | variable T_LEFT_BRACKET T_INT T_RIGHT_BRACKET T_EQUAL T_FLOAT             { updateArrayElementFloat($1, $3, $6); $$ = ""; }
    | variable T_LEFT_BRACKET T_MINUS T_INT T_RIGHT_BRACKET T_EQUAL T_FLOAT     { updateArrayElementFloat($1, -$4, $7); $$ = ""; }
    | variable T_LEFT_BRACKET T_INT T_RIGHT_BRACKET T_EQUAL T_STRING            { updateArrayElementString($1, $3, $6); $$ = ""; }
    | variable T_LEFT_BRACKET T_MINUS T_INT T_RIGHT_BRACKET T_EQUAL T_STRING    { updateArrayElementString($1, -$4, $7); $$ = ""; }
;

variable: T_VAR_BOOL                                                { }
    | T_VAR_BOOL T_VAR T_EQUAL T_TRUE                               { addSymbolBool($2, $4); $$ = ""; }
    | T_VAR_BOOL T_VAR T_EQUAL T_FALSE                              { addSymbolBool($2, $4); $$ = ""; }
    | T_VAR_BOOL T_VAR T_EQUAL T_VAR                                { createCloneFromSymbol($2, BOOL, $4, ANY); $$ = ""; }
    | T_VAR_BOOL T_VAR_ARRAY T_VAR T_EQUAL T_VAR                    { createCloneFromSymbol($3, ARRAY, $5, BOOL); $$ = ""; }
    | T_VAR_BOOL T_VAR_ARRAY T_VAR T_EQUAL typedarraystart          { finishComplexMode($3, BOOL); $$ = ""; }
    | T_VAR_BOOL T_VAR_DICT T_VAR T_EQUAL dictionarystart           { finishComplexMode($3, BOOL); $$ = ""; }
;

variable: T_VAR_NUMBER                                              { }
    | T_VAR_NUMBER T_VAR T_EQUAL T_INT                              { addSymbolInt($2, $4); $$ = ""; }
    | T_VAR_NUMBER T_VAR T_EQUAL T_FLOAT                            { addSymbolFloat($2, $4); $$ = ""; }
    | T_VAR_NUMBER T_VAR T_EQUAL T_VAR                              { createCloneFromSymbol($2, NUMBER, $4, ANY); $$ = ""; }
    | T_VAR_NUMBER T_VAR_ARRAY T_VAR T_EQUAL T_VAR                  { createCloneFromSymbol($3, ARRAY, $5, NUMBER); $$ = ""; }
    | T_VAR_NUMBER T_VAR_ARRAY T_VAR T_EQUAL typedarraystart        { finishComplexMode($3, NUMBER); $$ = ""; }
    | T_VAR_NUMBER T_VAR_DICT T_VAR T_EQUAL dictionarystart         { finishComplexMode($3, NUMBER); $$ = ""; }
;

variable: T_VAR_STRING                                              { }
    | T_VAR_STRING T_VAR T_EQUAL T_STRING                           { addSymbolString($2, $4); $$ = ""; }
    | T_VAR_STRING T_VAR T_EQUAL T_VAR                              { createCloneFromSymbol($2, STRING, $4, ANY); $$ = ""; }
    | T_VAR_STRING T_VAR_ARRAY T_VAR T_EQUAL T_VAR                  { createCloneFromSymbol($3, ARRAY, $5, STRING); $$ = ""; }
    | T_VAR_STRING T_VAR_ARRAY T_VAR T_EQUAL typedarraystart        { finishComplexMode($3, STRING); $$ = ""; }
    | T_VAR_STRING T_VAR_DICT T_VAR T_EQUAL dictionarystart         { finishComplexMode($3, STRING); $$ = ""; }
;

variable: T_VAR_ARRAY                                               { }
    | T_VAR_ARRAY T_VAR T_EQUAL T_VAR                               { createCloneFromSymbol($2, ARRAY, $4, ANY); $$ = "";}
    | T_VAR_ARRAY T_VAR T_EQUAL arraystart                          { finishComplexMode($2, ANY); $$ = ""; }
;

arraystart: T_LEFT_BRACKET                                          { addSymbolArray(NULL); }
    | arraystart array                                              { }
;

typedarraystart: T_LEFT_BRACKET                                     { addSymbolArray(NULL); }
    | typedarraystart array                                         { }
;

array: T_TRUE                                                       { addSymbolBool(NULL, $1); }
    | array T_COMMA array                                           { }
;
array: T_FALSE                                                      { addSymbolBool(NULL, $1); }
    | array T_COMMA array                                           { }
;
array: T_INT                                                        { addSymbolInt(NULL, $1); }
    | array T_COMMA array                                           { }
;
array: T_FLOAT                                                      { addSymbolFloat(NULL, $1); }
    | array T_COMMA array                                           { }
;
array: T_STRING                                                     { addSymbolString(NULL, $1); }
    | array T_COMMA array                                           { }
;
array: T_VAR                                                        { cloneSymbolToArray($1); }
    |                                                               { }
;

array: T_RIGHT_BRACKET                                              { }
;

variable: T_VAR_DICT                                                { }
    | T_VAR_DICT T_VAR T_EQUAL dictionarystart                      { finishComplexMode($2, ANY); $$ = ""; }
;

dictionarystart: T_LEFT_CURLY_BRACKET                               { addSymbolDict(NULL); }
    | dictionarystart dictionary                                    { }
;

dictionary: T_STRING T_COLON T_TRUE                                 { addSymbolBool($1, $3); }
    | dictionary T_COMMA dictionary                                 { }
;

dictionary: T_STRING T_COLON T_FALSE                                { addSymbolBool($1, $3); }
    | dictionary T_COMMA dictionary                                 { }
;

dictionary: T_STRING T_COLON T_INT                                  { addSymbolInt($1, $3); }
    | dictionary T_COMMA dictionary                                 { }
;

dictionary: T_STRING T_COLON T_FLOAT                                { addSymbolFloat($1, $3); }
    | dictionary T_COMMA dictionary                                 { }
;

dictionary: T_STRING T_COLON T_STRING                               { addSymbolString($1, $3); }
    | dictionary T_COMMA dictionary                                 { }
;

dictionary: T_RIGHT_CURLY_BRACKET                                   { }
;

%%

int main(int argc, char** argv) {
    FILE *fp = argc > 1 ? fopen (argv[1], "r") : stdin;

    is_interactive = (fp != stdin) ? false : true;

    if (is_interactive) {
        printf("%s Language %s (%s %s)\n", __LANGUAGE_NAME__, __LANGUAGE_VERSION__, __DATE__, __TIME__);
        printf("GCC version: %d.%d.%d on %s\n",__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__, __PLATFORM_NAME__);
        printf("%s\n\n", __LANGUAGE_MOTTO__);
    }

    yyin = fp;

    do {
        !is_interactive ?: printf("%s ", __SHELL_INDICATOR__);
        yyparse();
    } while(!feof(yyin));

    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}

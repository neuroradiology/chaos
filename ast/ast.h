/*
 * Description: Abstract Syntax Tree module of the Chaos Programming Language's source
 *
 * Copyright (c) 2019-2020 Chaos Language Development Authority <info@chaos-lang.org>
 *
 * License: GNU General Public License v3.0
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>
 *
 * Authors: M. Mert Yildiran <me@mertyildiran.com>
 */

#ifndef KAOS_AST_H
#define KAOS_AST_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct ASTNode ASTNode;
bool debug_enabled;

#include "../enums.h"
#include "../utilities/helpers.h"

enum ASTNodeType {
    AST_STEP,
    AST_VAR_CREATE_BOOL,
    AST_VAR_CREATE_BOOL_VAR,
    AST_VAR_CREATE_BOOL_VAR_EL,
    AST_VAR_CREATE_BOOL_FUNC_RETURN,
    AST_VAR_CREATE_NUMBER,
    AST_VAR_CREATE_NUMBER_VAR,
    AST_VAR_CREATE_NUMBER_VAR_EL,
    AST_VAR_CREATE_NUMBER_FUNC_RETURN,
    AST_VAR_CREATE_STRING,
    AST_VAR_CREATE_STRING_VAR,
    AST_VAR_CREATE_STRING_VAR_EL,
    AST_VAR_CREATE_STRING_FUNC_RETURN,
    AST_VAR_CREATE_ANY_BOOL,
    AST_VAR_CREATE_ANY_NUMBER,
    AST_VAR_CREATE_ANY_STRING,
    AST_VAR_CREATE_ANY_VAR,
    AST_VAR_CREATE_ANY_VAR_EL,
    AST_VAR_CREATE_ANY_FUNC_RETURN,
    AST_VAR_CREATE_LIST,
    AST_VAR_CREATE_LIST_VAR,
    AST_VAR_CREATE_LIST_FUNC_RETURN,
    AST_VAR_CREATE_DICT,
    AST_VAR_CREATE_DICT_VAR,
    AST_VAR_CREATE_DICT_FUNC_RETURN,
    AST_VAR_CREATE_BOOL_LIST,
    AST_VAR_CREATE_BOOL_LIST_VAR,
    AST_VAR_CREATE_BOOL_LIST_FUNC_RETURN,
    AST_VAR_CREATE_BOOL_DICT,
    AST_VAR_CREATE_BOOL_DICT_VAR,
    AST_VAR_CREATE_BOOL_DICT_FUNC_RETURN,
    AST_VAR_CREATE_NUMBER_LIST,
    AST_VAR_CREATE_NUMBER_LIST_VAR,
    AST_VAR_CREATE_NUMBER_LIST_FUNC_RETURN,
    AST_VAR_CREATE_NUMBER_DICT,
    AST_VAR_CREATE_NUMBER_DICT_VAR,
    AST_VAR_CREATE_NUMBER_DICT_FUNC_RETURN,
    AST_VAR_CREATE_STRING_LIST,
    AST_VAR_CREATE_STRING_LIST_VAR,
    AST_VAR_CREATE_STRING_LIST_FUNC_RETURN,
    AST_VAR_CREATE_STRING_DICT,
    AST_VAR_CREATE_STRING_DICT_VAR,
    AST_VAR_CREATE_STRING_DICT_FUNC_RETURN,
    AST_VAR_UPDATE_BOOL,
    AST_VAR_UPDATE_NUMBER,
    AST_VAR_UPDATE_STRING,
    AST_VAR_UPDATE_LIST,
    AST_VAR_UPDATE_DICT,
    AST_VAR_UPDATE_VAR,
    AST_VAR_UPDATE_VAR_EL,
    AST_VAR_UPDATE_FUNC_RETURN,
    AST_RETURN_VAR,
    AST_PRINT_COMPLEX_EL,
    AST_COMPLEX_EL_UPDATE_BOOL,
    AST_COMPLEX_EL_UPDATE_NUMBER,
    AST_COMPLEX_EL_UPDATE_STRING,
    AST_COMPLEX_EL_UPDATE_LIST,
    AST_COMPLEX_EL_UPDATE_DICT,
    AST_COMPLEX_EL_UPDATE_VAR,
    AST_COMPLEX_EL_UPDATE_VAR_EL,
    AST_COMPLEX_EL_UPDATE_FUNC_RETURN,
    AST_PRINT_VAR,
    AST_PRINT_VAR_EL,
    AST_PRINT_EXPRESSION,
    AST_PRINT_MIXED_EXPRESSION,
    AST_PRINT_STRING,
    AST_PRINT_INTERACTIVE_VAR,
    AST_PRINT_INTERACTIVE_EXPRESSION,
    AST_PRINT_INTERACTIVE_MIXED_EXPRESSION,
    AST_ECHO_VAR,
    AST_ECHO_VAR_EL,
    AST_ECHO_EXPRESSION,
    AST_ECHO_MIXED_EXPRESSION,
    AST_ECHO_STRING,
    AST_PRETTY_PRINT_VAR,
    AST_PRETTY_PRINT_VAR_EL,
    AST_PRETTY_ECHO_VAR,
    AST_PRETTY_ECHO_VAR_EL,
    AST_PARENTHESIS,
    AST_EXPRESSION_VALUE,
    AST_EXPRESSION_PLUS,
    AST_EXPRESSION_MINUS,
    AST_EXPRESSION_MULTIPLY,
    AST_EXPRESSION_BITWISE_AND,
    AST_EXPRESSION_BITWISE_OR,
    AST_EXPRESSION_BITWISE_XOR,
    AST_EXPRESSION_BITWISE_NOT,
    AST_EXPRESSION_BITWISE_LEFT_SHIFT,
    AST_EXPRESSION_BITWISE_RIGHT_SHIFT,
    AST_VAR_EXPRESSION_VALUE,
    AST_VAR_EXPRESSION_INCREMENT,
    AST_VAR_EXPRESSION_DECREMENT,
    AST_VAR_EXPRESSION_INCREMENT_ASSIGN,
    AST_VAR_EXPRESSION_ASSIGN_INCREMENT,
    AST_MIXED_EXPRESSION_VALUE,
    AST_MIXED_EXPRESSION_PLUS,
    AST_MIXED_EXPRESSION_MINUS,
    AST_MIXED_EXPRESSION_MULTIPLY,
    AST_MIXED_EXPRESSION_DIVIDE,
    AST_VAR_MIXED_EXPRESSION_VALUE,
    AST_BOOLEAN_EXPRESSION_VALUE,
    AST_BOOLEAN_EXPRESSION_REL_EQUAL,
    AST_BOOLEAN_EXPRESSION_REL_NOT_EQUAL,
    AST_BOOLEAN_EXPRESSION_REL_GREAT,
    AST_BOOLEAN_EXPRESSION_REL_SMALL,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EQUAL,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EQUAL,
    AST_BOOLEAN_EXPRESSION_LOGIC_AND,
    AST_BOOLEAN_EXPRESSION_LOGIC_OR,
    AST_BOOLEAN_EXPRESSION_LOGIC_NOT,
    AST_BOOLEAN_EXPRESSION_REL_EQUAL_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_NOT_EQUAL_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EQUAL_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EQUAL_MIXED,
    AST_BOOLEAN_EXPRESSION_LOGIC_AND_MIXED,
    AST_BOOLEAN_EXPRESSION_LOGIC_OR_MIXED,
    AST_BOOLEAN_EXPRESSION_LOGIC_NOT_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_EQUAL_MIXED_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_NOT_EQUAL_MIXED_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_MIXED_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_MIXED_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EQUAL_MIXED_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EQUAL_MIXED_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_LOGIC_AND_MIXED_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_LOGIC_OR_MIXED_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_EQUAL_BOOLEAN_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_NOT_EQUAL_BOOLEAN_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_BOOLEAN_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_BOOLEAN_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EQUAL_BOOLEAN_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EQUAL_BOOLEAN_MIXED,
    AST_BOOLEAN_EXPRESSION_LOGIC_AND_BOOLEAN_MIXED,
    AST_BOOLEAN_EXPRESSION_LOGIC_OR_BOOLEAN_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_EQUAL_EXP,
    AST_BOOLEAN_EXPRESSION_REL_NOT_EQUAL_EXP,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EXP,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EXP,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EQUAL_EXP,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EQUAL_EXP,
    AST_BOOLEAN_EXPRESSION_LOGIC_AND_EXP,
    AST_BOOLEAN_EXPRESSION_LOGIC_OR_EXP,
    AST_BOOLEAN_EXPRESSION_LOGIC_NOT_EXP,
    AST_BOOLEAN_EXPRESSION_REL_EQUAL_EXP_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_NOT_EQUAL_EXP_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EXP_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EXP_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EQUAL_EXP_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EQUAL_EXP_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_LOGIC_AND_EXP_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_LOGIC_OR_EXP_BOOLEAN,
    AST_BOOLEAN_EXPRESSION_REL_EQUAL_BOOLEAN_EXP,
    AST_BOOLEAN_EXPRESSION_REL_NOT_EQUAL_BOOLEAN_EXP,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_BOOLEAN_EXP,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_BOOLEAN_EXP,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EQUAL_BOOLEAN_EXP,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EQUAL_BOOLEAN_EXP,
    AST_BOOLEAN_EXPRESSION_LOGIC_AND_BOOLEAN_EXP,
    AST_BOOLEAN_EXPRESSION_LOGIC_OR_BOOLEAN_EXP,
    AST_BOOLEAN_EXPRESSION_REL_EQUAL_MIXED_EXP,
    AST_BOOLEAN_EXPRESSION_REL_NOT_EQUAL_MIXED_EXP,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_MIXED_EXP,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_MIXED_EXP,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EQUAL_MIXED_EXP,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EQUAL_MIXED_EXP,
    AST_BOOLEAN_EXPRESSION_LOGIC_AND_MIXED_EXP,
    AST_BOOLEAN_EXPRESSION_LOGIC_OR_MIXED_EXP,
    AST_BOOLEAN_EXPRESSION_REL_EQUAL_EXP_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_NOT_EQUAL_EXP_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EXP_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EXP_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_GREAT_EQUAL_EXP_MIXED,
    AST_BOOLEAN_EXPRESSION_REL_SMALL_EQUAL_EXP_MIXED,
    AST_BOOLEAN_EXPRESSION_LOGIC_AND_EXP_MIXED,
    AST_BOOLEAN_EXPRESSION_LOGIC_OR_EXP_MIXED,
    AST_VAR_BOOLEAN_EXPRESSION_VALUE,
    AST_DELETE_VAR,
    AST_DELETE_VAR_EL,
    AST_PRINT_SYMBOL_TABLE,
    AST_LIST_START,
    AST_LIST_ADD_VAR,
    AST_LIST_ADD_VAR_EL,
    AST_LIST_NESTED_FINISH,
    AST_DICT_START,
    AST_DICT_ADD_VAR,
    AST_DICT_ADD_VAR_EL,
    AST_DICT_NESTED_FINISH,
    AST_POP_NESTED_COMPLEX_STACK,
    AST_LEFT_RIGHT_BRACKET_EXPRESSION,
    AST_LEFT_RIGHT_BRACKET_MINUS_EXPRESSION,
    AST_LEFT_RIGHT_BRACKET_STRING,
    AST_LEFT_RIGHT_BRACKET_VAR,
    AST_LEFT_RIGHT_BRACKET_VAR_MINUS,
    AST_BUILD_COMPLEX_VARIABLE,
    AST_EXIT_SUCCESS,
    AST_EXIT_EXPRESSION,
    AST_EXIT_VAR,
    AST_START_TIMES_DO,
    AST_START_TIMES_DO_INFINITE,
    AST_START_TIMES_DO_VAR,
    AST_START_FOREACH,
    AST_START_FOREACH_DICT,
    AST_END,
    AST_PRINT_FUNCTION_TABLE,
    AST_FUNCTION_PARAMETERS_START,
    AST_FUNCTION_STEP,
    AST_FUNCTION_PARAMETER_BOOL,
    AST_FUNCTION_PARAMETER_NUMBER,
    AST_FUNCTION_PARAMETER_STRING,
    AST_FUNCTION_PARAMETER_LIST,
    AST_FUNCTION_PARAMETER_BOOL_LIST,
    AST_FUNCTION_PARAMETER_NUMBER_LIST,
    AST_FUNCTION_PARAMETER_STRING_LIST,
    AST_FUNCTION_PARAMETER_DICT,
    AST_FUNCTION_PARAMETER_BOOL_DICT,
    AST_FUNCTION_PARAMETER_NUMBER_DICT,
    AST_FUNCTION_PARAMETER_STRING_DICT,
    AST_OPTIONAL_FUNCTION_PARAMETER_BOOL,
    AST_OPTIONAL_FUNCTION_PARAMETER_NUMBER,
    AST_OPTIONAL_FUNCTION_PARAMETER_STRING,
    AST_OPTIONAL_FUNCTION_PARAMETER_LIST,
    AST_OPTIONAL_FUNCTION_PARAMETER_BOOL_LIST,
    AST_OPTIONAL_FUNCTION_PARAMETER_NUMBER_LIST,
    AST_OPTIONAL_FUNCTION_PARAMETER_STRING_LIST,
    AST_OPTIONAL_FUNCTION_PARAMETER_DICT,
    AST_OPTIONAL_FUNCTION_PARAMETER_BOOL_DICT,
    AST_OPTIONAL_FUNCTION_PARAMETER_NUMBER_DICT,
    AST_OPTIONAL_FUNCTION_PARAMETER_STRING_DICT,
    AST_FUNCTION_CALL_PARAMETERS_START,
    AST_FUNCTION_CALL_PARAMETER_BOOL,
    AST_FUNCTION_CALL_PARAMETER_NUMBER,
    AST_FUNCTION_CALL_PARAMETER_STRING,
    AST_FUNCTION_CALL_PARAMETER_VAR,
    AST_FUNCTION_CALL_PARAMETER_LIST,
    AST_FUNCTION_CALL_PARAMETER_DICT,
    AST_DEFINE_FUNCTION_BOOL,
    AST_DEFINE_FUNCTION_NUMBER,
    AST_DEFINE_FUNCTION_STRING,
    AST_DEFINE_FUNCTION_ANY,
    AST_DEFINE_FUNCTION_LIST,
    AST_DEFINE_FUNCTION_DICT,
    AST_DEFINE_FUNCTION_BOOL_LIST,
    AST_DEFINE_FUNCTION_BOOL_DICT,
    AST_DEFINE_FUNCTION_NUMBER_LIST,
    AST_DEFINE_FUNCTION_NUMBER_DICT,
    AST_DEFINE_FUNCTION_STRING_LIST,
    AST_DEFINE_FUNCTION_STRING_DICT,
    AST_DEFINE_FUNCTION_VOID,
    AST_PRINT_FUNCTION_RETURN,
    AST_ECHO_FUNCTION_RETURN,
    AST_PRETTY_PRINT_FUNCTION_RETURN,
    AST_PRETTY_ECHO_FUNCTION_RETURN,
    AST_FUNCTION_RETURN,
    AST_ADD_FUNCTION_NAME,
    AST_APPEND_MODULE,
    AST_PREPEND_MODULE,
    AST_MODULE_IMPORT,
    AST_MODULE_IMPORT_AS,
    AST_MODULE_IMPORT_PARTIAL,
    AST_NESTED_COMPLEX_TRANSITION,
    AST_DECISION_DEFINE,
    AST_DECISION_MAKE_BOOLEAN,
    AST_DECISION_MAKE_BOOLEAN_BREAK,
    AST_DECISION_MAKE_BOOLEAN_CONTINUE,
    AST_DECISION_MAKE_DEFAULT,
    AST_DECISION_MAKE_DEFAULT_BREAK,
    AST_DECISION_MAKE_DEFAULT_CONTINUE,
    AST_JSON_PARSER,
};

typedef struct ASTNode {
    unsigned long long id;
    enum ASTNodeType node_type;
    struct ASTNode* next;
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* child;
    struct ASTNode* depend;
    char *module;
    char *transpiled;
    bool is_transpiled;
    bool dont_transpile;
    enum ValueType value_type;
    union Value value;
    size_t strings_size;
    char *strings[];
} ASTNode;

ASTNode* ast_node_cursor;
ASTNode* ast_root_node;
unsigned long long ast_node_id_counter;
ASTNode* ast_node_cursor_backup;
ASTNode* ast_interactive_cursor;
bool enable_branch_out;
unsigned long long loops_inside_function_counter;
bool stop_ast_evaluation;

ASTNode* addASTNodeBase(enum ASTNodeType node_type, char *strings[], size_t strings_size, union Value value, enum ValueType value_type);
ASTNode* addASTNode(enum ASTNodeType node_type, char *strings[], size_t strings_size);
ASTNode* addASTNodeBool(enum ASTNodeType node_type, char *strings[], size_t strings_size, bool b, ASTNode* node);
ASTNode* addASTNodeInt(enum ASTNodeType node_type, char *strings[], size_t strings_size, long long i, ASTNode* node);
ASTNode* addASTNodeFloat(enum ASTNodeType node_type, char *strings[], size_t strings_size, long double f, ASTNode* node);
ASTNode* addASTNodeString(enum ASTNodeType node_type, char *strings[], size_t strings_size, char *s, ASTNode* node);
ASTNode* addASTNodeBranch(enum ASTNodeType node_type, ASTNode* l_node, ASTNode* r_node);
ASTNode* addASTNodeAssign(enum ASTNodeType node_type, char *strings[], size_t strings_size, ASTNode* node);
ASTNode* addASTNodeFull(enum ASTNodeType node_type, char *strings[], size_t strings_size, ASTNode* l_node, ASTNode* r_node);
void ASTNodeNext(ASTNode* ast_node);
void ASTBranchOut();
void ASTMergeBack();
ASTNode* free_node(ASTNode* ast_node);
char* getAstNodeTypeName(unsigned i);

#endif

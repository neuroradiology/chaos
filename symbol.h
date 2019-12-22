#include <stdio.h>
#include <string.h>
#include "errors.h"

enum Type { BOOL, INT, CHAR, STRING, FLOAT };

typedef struct {
    char *name;
    enum Type type;
    union Value {
        bool b;
        int i;
        char c;
        char *s;
        float f;
    } value;
    struct Symbol* previous;
    struct Symbol* next;
} Symbol;

Symbol* symbol_cursor;
Symbol* head_symbol;

bool isDefined(char *name);

void addSymbol(char *name, enum Type type, bool b) {
    isDefined(name);
    symbol_cursor = head_symbol;

    Symbol* variable;
    variable = (struct Symbol*)malloc(sizeof(Symbol));
    variable->name = name;
    variable->type = type;
    variable->value.b = b;
    if (symbol_cursor == NULL) {
        symbol_cursor = variable;
        head_symbol = variable;
    } else {
        symbol_cursor->next = variable;
        variable->previous = symbol_cursor;
    }
}

int updateSymbol(char *name, bool b) {
    symbol_cursor = head_symbol;
    while (symbol_cursor != NULL) {
        if (strcmp(symbol_cursor->name, name) == 0) {
            symbol_cursor->value.b = b;
            return 0;
        }
        symbol_cursor = symbol_cursor->next;
    }
    throw_error(3, name);
}

Symbol* getSymbol(char *name) {
    symbol_cursor = head_symbol;
    while (symbol_cursor != NULL) {
        if (strcmp(symbol_cursor->name, name) == 0) {
            Symbol* symbol = symbol_cursor;
            return symbol;
        }
        symbol_cursor = symbol_cursor->next;
    }
    throw_error(3, name);
}

void printSymbolValue(Symbol* symbol) {
    char type[2] = "\0";
    switch (symbol->type)
    {
        case BOOL:
            printf("%s", symbol->value.b ? "true" : "false");
            break;
        case INT:
            printf("%i", symbol->value.i);
            break;
        case FLOAT:
            printf("%f", symbol->value.f);
            break;
        case CHAR:
            printf("%c", symbol->value.c);
            break;
        case STRING:
            printf("%s", symbol->value.s);
            break;
        default:
            type[0] = symbol->type;
            throw_error(1, type);
            break;
    }
    printf("\n");
}

bool isDefined(char *name) {
    symbol_cursor = head_symbol;
    while (symbol_cursor != NULL) {
        if (strcmp(symbol_cursor->name, name) == 0) {
            throw_error(2, name);
            return true;
        }
        symbol_cursor = symbol_cursor->next;
    }
    return false;
}
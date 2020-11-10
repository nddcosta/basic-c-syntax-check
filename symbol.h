
#ifndef SYMBOL_H
#define SYMBOL_H

#define MAX_SYMBOLS 5000 //TODO: should be dynamic

#include "status.h"
#include "errors.h"

struct Status;
struct Errors;

struct Symbol{
	char symbol_map[128]; 
	char symbol_stack[MAX_SYMBOLS];
	int index;
};

int is_left_symbol(char);
int is_right_symbol(char);
int symbol_matches(char, struct Status*);
void update_symbol_status(char, int, int, int, struct Status*, struct Errors*);
int is_symbol(char);
void init_symbol_map(struct Status*);
void check_final_symbols(struct Status*, struct Errors*);

#endif

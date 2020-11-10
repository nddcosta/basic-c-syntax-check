
#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

struct Errors{
	int quote;
	int symbol;
};

int any_basic_syntax_errors(struct Errors*);
void print_errors(struct Errors*);

#endif

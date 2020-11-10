#include "errors.h"

int any_basic_syntax_errors(struct Errors *errors){
	return errors->symbol || errors->quote;
}

void print_errors(struct Errors *errors){
	if(errors->symbol){
		printf("Symbol ERROR\n"); 
	}else if(errors->quote){
		printf("Quote Error\n");
	}else{
		printf("No Errors\n");
	}
}

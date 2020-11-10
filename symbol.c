#include "symbol.h"

int is_left_symbol(char c){
	return (c == '(' || c == '[' || c == '{');
}

int is_right_symbol(char c){
	return (c == ')' || c == ']' || c == '}');
}

int symbol_matches(char	c, struct Status *status){
	if(status->symbol->index == 0){
		return 0;
	}
	return status->symbol->symbol_stack[(status->symbol->index)-1] == status->symbol->symbol_map[(int)c];	
}

void update_symbol_status(char c, int i, int num_bytes_read, int limit, struct Status *status, struct Errors *errors){
	if(is_left_symbol(c)){
		status->symbol->symbol_stack[(status->symbol->index)++] = c;
	}else if(is_right_symbol(c)){
		if(symbol_matches(c, status)){
			(status->symbol->index)--;
		}else{
			errors->symbol = 1;
		}
	}
}

void init_symbol_map(struct Status *status){
	status->symbol->symbol_map[')'] = '(';
	status->symbol->symbol_map['}'] = '{';
	status->symbol->symbol_map[']'] = '[';
}

int is_symbol(char c){
	return is_left_symbol(c) || is_right_symbol(c);
}

void check_final_symbols(struct Status *status, struct Errors *errors){
	if(!errors->symbol){
		errors->symbol = !(status->symbol->index == 0);
	}
}


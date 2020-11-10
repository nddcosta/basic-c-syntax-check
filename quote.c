#include "quote.h"

int is_hex_escape(char c){
	return ((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F'));
}

int is_oct_escape(char c){
	return  (c >= '0') && (c <= '7');
}


void reset_escape_status(struct Status *status){
	status->quote->in_escape = 0;
	status->quote->escape_ind = 0;
	status->quote->hex = 0;
	status->quote->single_ind = 1;
}

int single_quote_out_of_bounds(char c, struct Status *status){
	return status->quote->in_single && status->quote->escape_ind >= 3 && c != '\'';
}


int update_hex_oct_status(char c, struct Status *status, struct Errors *errors){
	if(single_quote_out_of_bounds(c, status)){
		return 1;
	}
	if(status->quote->hex){
		if(!is_hex_escape(c)){
			if(status->quote->escape_ind == 1){
				return 1;
			}
			reset_escape_status(status);
			update_quote_status(c, status, errors);
		}else{
			status->quote->escape_ind++;
		}
	}else{
		if(status->quote->escape_ind > 2 || !is_oct_escape(c)){
			reset_escape_status(status);
			update_quote_status(c, status, errors);
		}else{
			status->quote->escape_ind++;
		}
	}
	return 0;
}



int check_for_valid_escape_seq(char c, struct Status *status, struct Errors *errors){
	if(status->quote->escape_ind == 0){
		if(c == 'x' || is_oct_escape(c)){
			status->quote->hex = (c == 'x') ? 1 : 0;
			status->quote->escape_ind++;
			return 0;
		}else{
			reset_escape_status(status);
			return !(c == 't' || c == 'n' || c == 'a' 
				|| c == '\\' || c == 'b' || c == 'f' 
				|| c == 'r' || c == 'v' || c == '?' 
				|| c == '\'' || c == '\"');	
		}
	}else{
		return update_hex_oct_status(c, status, errors);
	}
}	

void update_quote_status(char c, struct Status *status, struct Errors *errors){
	if(status->quote->in_escape){
		errors->quote = check_for_valid_escape_seq(c, status, errors);
	}else{
		if(c == '\\'){
			status->quote->in_escape = 1;
		}else if(status->quote->in_double && c == '\"' ){
			status->quote->in_double = 0;
		}else if(status->quote->in_single && c == '\'' ){
			if(status->quote->single_ind == 1){
				status->quote->in_single = 0;
				status->quote->single_ind = 0;
			}else{
				errors->quote = 1;
			}
		}else if((status->quote->in_single && (c == '\"' || c == '\n')) || (status->quote->in_double && (c == '\"' || c == '\n'))){
			errors->quote = 1;
		}
	}
	status->quote->single_ind = status->quote->in_single ? status->quote->single_ind+1 : 0;
}

void update_quote_type(char c, struct Status *status){
	if(c == '\''){
		status->quote->in_single = 1;
	}else if(c == '\"'){
		status->quote->in_double = 1;
	}
}

int in_quote(struct Status *status){
	return status->quote->in_single || status->quote->in_double;
}

int is_quote_or_newline(char c){
	return c == '\'' || c == '\"' || c == '\n';
}



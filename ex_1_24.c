#include "symbol.h"
#include "errors.h"
#include "status.h"
#include "quote.h"
#include "comment.h"

#define BUFFER_SIZE 4096

struct Comment comment;
struct Quote quote;
struct Symbol symbol;
struct Status status;
struct Errors errors;

/*
	Finds basic syntatx errors in a c file
	Checks for symbol matching
	Checks for correct usage of single and double quotes, considers correct escape sequences
	Comments are handled properly, i.e. symbol matching and quote rules don't apply in comments
*/

int process_file(FILE*, char [], struct Status*, struct Errors*);
void scan_for_errors(FILE*, char[], struct Status*, struct Errors*);

int process_file(FILE* fp, char buffer[], struct Status* status, struct Errors* errors){
	size_t num_bytes_read = fread(buffer, 1, BUFFER_SIZE, fp);
	for(int i = 0; i < num_bytes_read; i++){
		if(any_basic_syntax_errors(errors)){
			return -1;
		}else if(in_comment(status)){
			update_comment_status(buffer[i], status);
		}else if(in_quote(status)){
			update_quote_status(buffer[i], status, errors);
		}else{
			if(is_quote_or_newline(buffer[i])){
				update_quote_type(buffer[i], status);
			}else if(is_comment_char(buffer[i])){
				update_comment_type(buffer[i], status);
			}else if(is_symbol(buffer[i])){
				update_symbol_status(buffer[i], i, num_bytes_read, BUFFER_SIZE, status, errors);
			}
		}
	}
	return num_bytes_read == BUFFER_SIZE ? num_bytes_read : -1;
}


void scan_for_errors(FILE* fp, char buffer[], struct Status *status, struct Errors* errors){
	while((process_file(fp, buffer, status, errors) > -1)){
		;
	}
	check_final_symbols(status, errors);
}


int main(int argc, char *argv[]){
	FILE* fp;
	char buffer[BUFFER_SIZE];
	struct Status status;
	struct Comment comment = {};
	struct Symbol symbol = {};
	struct Quote quote = {};
	status.comment = &comment;
	status.quote = &quote;
	status.symbol = &symbol;
	struct Errors errors = {};
	
	if(argc > 2){
		printf("Too many arguments\n");
	}
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("Couldn't open file\n");
	}

	init_symbol_map(&status);
	scan_for_errors(fp, buffer, &status, &errors);
	print_errors(&errors);
	fclose(fp);
	return 0;	
}

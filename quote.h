
#ifndef QUOTE_H
#define QUOTE_H

#include "status.h"
#include "errors.h"


struct Quote{
	int in_single;
	int in_double;
	int in_escape;
	int hex;
	int escape_ind;
	int single_ind;
};

void update_quote_status(char, struct Status*, struct Errors*);
int in_quote(struct Status*);
int check_for_valid_escape_char(char);
int is_quote_or_newline(char);
void update_quote_type(char, struct Status*);
int is_oct_escape(char);
void reset_escape_status(struct Status *);
int single_quote_out_of_bounds(char, struct Status *);
int update_hex_oct_status(char, struct Status *, struct Errors *);
int is_hex_escape(char);

#endif

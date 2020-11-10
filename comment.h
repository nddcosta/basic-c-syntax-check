
#ifndef COMMENT_H
#define COMMENT_H

#include "status.h"

struct Status;

struct Comment{
	int in_multi_line;
	int in_single_line;	
	int checking_for_comment_start;
	int checking_for_comment_end;
};

void update_single_line_comment(char, struct Status*);
void update_multi_line_comment(char, struct Status*);
void update_comment_status(char, struct Status*);
void check_for_comment(char, struct Status*);
int in_comment(struct Status*);
void update_comment_type(char, struct Status*);
int is_comment_char(char c);

#endif
